//----------------------------------------------------------
// ファイル名		：GameOver.cpp
// 概要				：ゲームオーバーの処理の関数の定義
// 作成者			：21CU0136 松本賢太
// 更新内容			：2022/03/11 21CU0136松本　作成
//					  2022/03/14 21CU0136松本　ビット値変更
//----------------------------------------------------------
#include "CActionGameApp.h"
#include "GameResource.h"
#include<fstream>
using namespace std;

/*
 * ゲームオーバー画面の処理を行う部分
 */
void CActionGameApp::procGameOver()
{
	//フェーズの進行状態によって処理を切り替える
	switch (g_GameOver.g_GameOverPhase)
	{
		//開始時
	case eBegin:
	{
		//ゲームオーバー画面の開始処理
		procOverBegin();
		//進行状態をメインに切り替える
		g_GameOver.g_GameOverPhase = eMain;
	}
	break;
	//メイン
	case eMain:
	{

		IsLoad = IsLoad & 0b1011;

		//--------------------------------------
		// playの画面をもう一度描画する
		//------------------------------------
		//背景の描画
		Backrender();

		//UIの描画
		UIrender();
		//加算スコアの描画
		for (int i = 0; i < AddScoreIndex; ++i)
		{
			if (g_pAddScore[i] != NULL)
			{
				renderFont(g_pAddScore[i], AddScore[i]);
			}
		}

		//ゲームオーバー画面のメイン処理
		procOverMain();

		////敵の処理
		for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
		{
			//敵画像が作成されていたら描画する
			if (g_enemyObjs[i].obj != NULL)
			{
				renderSprite(g_enemyObjs[i].obj);
			}
		}

		////プレイヤーの画像は最初は0だけ作成、表示する
		//for (int i = 0; i < 2; i++)
		//{
		//	if (g_pPlayer[i] != NULL)
		//	{
		//		renderSprite(g_pPlayer[i]);
		//	}
		//}

		//オブジェクトの描画
		ThunderRender();
		Objrender();
		//----------------------------------------------------------------------------------

		
	}
	break;
	//終了時
	case eEnd:
	{
		IsLoad = IsLoad | 0b0001;
		//procPlayEnd();
		//ゲームオーバー画面の終了処理
		procOverEnd();
		//再度クリア画面に来た時に開始から処理を行うためフェーズを戻しておく
		g_GameOver.g_GameOverPhase = eBegin;
		//次のステータスを設定する
		SetNextGameStatus(g_GameOver.g_NextStatusFromGameOver);
	}
	break;
	}
}

/*
* 関数名	：procOverBegin
* 処理内容	：ゲームオーバー画面の開始時に行う処理
* 引数		：なし
* 戻り値	：なし
*/
void CActionGameApp::procOverBegin()
{
	//g_pGameOverがNULLの時のみ画像を作成する
	if (g_GameOver.g_pGameOver == NULL)
	{
		//ゲームオーバー画面の画像を作成する
		g_GameOver.g_pGameOver = createSprite(Tex_Over, g_GameOver.Text_SIZE_X, g_GameOver.Text_SIXE_Y);
		g_GameOver.g_pGameOver->setPos(0.0f, WINDOW_TOP - 448.0f - (g_GameOver.Text_SIXE_Y / 2.0f));
	}
}

/*
* 関数名	：procOverMain
* 処理内容	：ゲームオーバー画面のメイン処理
* 引数		：なし
* 戻り値	：なし
*/
void CActionGameApp::procOverMain()
{
	//サウンド破棄
	if (g_pEnemyDeath)
	{
		disposeSound(g_pEnemyDeath);
		g_pEnemyDeath = NULL;
	}
	//エネミーの羽音
	for (int i = 0; i < 5; ++i)
	{
		if (g_pEnemyJump[i])
		{
			StopSourceSound(g_pEnemyJump[i]);
			disposeSound(g_pEnemyJump[i]);
			g_pEnemyJump[i] = NULL;
		}
	}
	//カウントをスタートする
	++g_GameOver.Cnt;
	//Xキー(スタートボタン)が入力されたときはタイトルに移行
	if (getInput()->isPressedOnce(DIK_X))
	{
		//タイトルにステータスを移行する準備をする
		g_GameOver.g_GameOverPhase = eEnd;
		g_GameOver.g_NextStatusFromGameOver = eOpening;
	}
	else if (g_GameOver.Cnt > 4 * 60)
	{
		//タイトルにステータスを移行する準備をする
		g_GameOver.g_GameOverPhase = eEnd;
		g_GameOver.g_NextStatusFromGameOver = eOpening;
	}
	//ゲームオーバー画面の画像が作成されていたら描画する
	if (g_GameOver.g_pGameOver != NULL)
	{
		renderSprite(g_GameOver.g_pGameOver);
	}

}

/*
* 関数名	：procOverEnd()
* 処理内容	：ゲームオーバー画面の終了時に行う処理
* 引数		：なし
* 戻り値	：なし
*/
void CActionGameApp::procOverEnd()
{
	//g_pGameOverが作成されている場合のみ破棄する
	if (g_GameOver.g_pGameOver != NULL)
	{
		//ゲームオーバーの画像を破棄する
		disposeSprite(g_GameOver.g_pGameOver);
		g_GameOver.g_pGameOver = NULL;
	}

	//カウントリセット
	g_GameOver.Cnt = 0;

	//残機リセット
	NowRemainCount = 2;

	//敵の各種変数リセット
	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
	{
		g_enemyObjs[i].EnemyStatus = 3;
		BalloonReloadFlag[i] = true;
		EnemyFallAnimFlag[i] = false;
		BalloonReloadFlag[i] = true;
		EnemyDeathFlag[i] = false;
		EnemyDeathFallFlag[i] = false;
		EnemyDeathFallSpeed[i] = 3.0f;
		g_enemyObjs[i].EnemyLevel = 0;
		g_enemyObjs[i].g_pEnemyFlySpeed_X = -1.5f;
		g_enemyObjs[i].g_pEnemyFlySpeed_Y = 1.5f;
		g_enemyObjs[i].g_pEnemyMaxSpeed_X = 0.0f;
		g_enemyObjs[i].g_pEnemyMaxSpeed_Y = 0.0f;
		g_enemyObjs[i].SpeedMagnification = 1.0;
	}
	for (int i = 0; i < 25; ++i)
	{
		AnimCount[i] = 0;
	}

	//泡
	for (int i = 0; i < BubbleCount; ++i)
	{
		if (g_pBubble[i] != NULL && (AnimCountBubble + i) % 2 != 0)
		{
			disposeSprite(g_pBubble[i]);
			g_pBubble[i] = NULL;
			disposeSprite(g_pBubble[i + 1]);
			g_pBubble[i + 1] = NULL;

			AnimCount[AnimCountBubble + i] = 0;
		}
	}

	//水しぶき
	for (int i = 0; i < WaterCount; ++i)
	{
		if (EnteringWater[i] != NULL)
		{
			disposeSprite(EnteringWater[i]);
			EnteringWater[i] = NULL;
		}
	}

	//UI
	PhaseRenderCnt = 0;
	if (TopScore.Score < PlayerScore.Score)
	{
		TopScore.Score = PlayerScore.Score;
		//テキストファイルにトップスコアを書き込み
		ofstream outputFile;
		outputFile.open("TopScore.txt", ios::out);

		if (!(outputFile.fail()))
		{
			outputFile << TopScore.Score;

			outputFile.close();
		}
	}
	for (int i = 0; i < AddScoreIndex; ++i)
	{
		if (g_pAddScore[i] != NULL)
		{
			disposeFont(g_pAddScore[i]);
			g_pAddScore[i] = NULL;
			AddScoreCnt[i] = 0;
		}
	}
	PhaseNum = 1;
	PlayerScore.Score = 0;

	ThunderDispose();

	//破棄
	procPlayMain_EnemyDispose(); //Enemy
	ObjDispose();                //Obj
}
