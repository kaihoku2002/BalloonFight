#include "CActionGameApp.h"
#include "GameResource.h"
#include<fstream>
using namespace std;


/*
 * タイトルの処理を行う部分
 */
void CActionGameApp::procTitle()
{
	//フェーズの進行状態によって処理をい切り替える
	switch (g_TitlePhase)
	{
	case eBegin:
	{
		//タイトル画面の開始時の処理を行う
		procTitleBegin();
		//進行状態をメインに切り替える
		g_TitlePhase = eMain;
	}
	break;

	//メイン
	case eMain:
	{
		IsLoad = IsLoad & 0b1110;
		//タイトル画面のメイン処理を行う
		procTitleMain();
	}
	break;

	//終了時
	case eEnd:
	{
		IsLoad = IsLoad | 0b0010;
		//タイトル画面の終了処理を行う
		procTitleEnd();
		//再度タイトル画面に来た時に開始から処理を行うためにフェーズを戻しておく
		g_TitlePhase = eBegin;
		//次のステータスを設定する
		SetNextGameStatus(g_NextStatusFromTitle);
	}
	break;
	}

#if 1
	// ---------------------------------------------------
	// サウンド再生テストコード	
	// 必要に応じて活用してください。

	//// 1が押されたら生成
	//if (m_pDirectInput->isKeyPressed(DIK_1))
	//{
	//	// 作成されていなければ、作成
	//	if (!g_pPhaseStart)
	//	{
	//		// 第2引数：ループ設定
	//		// ループしないので、falseを設定
	//		g_pPhaseStart = createSound(PhaseStart, false);
	//	}
	//}

	// 作成されていたら再生
	if (g_pPhaseStart)
	{
		PlaySourceSound(g_pPhaseStart);
	}

	//// ボリューム変更（0～100）
	////if (g_pSound)
	////{
	////	g_pSound->ChangeVolume(50);
	////}

	//// 2が押されたら再生しなおす
	//if (m_pDirectInput->isKeyPressed(DIK_2))
	//{
	//	// 作成されていなければ、作成
	//	if (g_pPhaseStart)
	//	{			
	//		g_pPhaseStart->ReLoadSource();
	//	}
	//}

	//// 0が押されたら強制終了
	//if (m_pDirectInput->isKeyPressed(DIK_0))
	//{
	//	// 作成されていたら、削除
	//	if (g_pPhaseStart)
	//	{
	//		disposeSound(g_pPhaseStart);
	//		g_pPhaseStart = NULL;
	//	}
	//}

	// 再生し終わったら削除
	//（ループ設定trueの場合は入らない）
	if (g_pPhaseStart && (g_pPhaseStart->isPlayed() == false))
	{
		disposeSound(g_pPhaseStart);
		g_pPhaseStart = NULL;
	}
	// ---------------------------------------------------
#endif
}

//関数名		:procTitleBegin()
//処理内容		:タイトル画面の開始時に行う処理
//引数			:なし
//戻り値		:なし

void CActionGameApp::procTitleBegin()
{
	//スコア用テキストファイル読み込み
	if (PlayerScore.Score <= 0)
	{
		ifstream inputFile;
		inputFile.open("TopScore.txt", ios::in);

		if (!(inputFile.fail()))
		{
			inputFile >> TopScore.Score;

			inputFile.close();
		}
	}
	//g_pTitle　が　NULLの時のみ画像を作成する
	if (g_pTitle == NULL)
	{
		//タイトルの画像を作成する
		g_pTitle = createSprite(Tex_Title);
	}
	//g_ptitleBalloonがNULLの時のみ画像を作成する
	if (g_pTitleBalloon == NULL)
	{
		//タイトルバルーンの画像を作成する
		g_pTitleBalloon = createSprite(Tex_titleballoon, 48.0f, 64.0f);
	}
}

//関数名		:procTitleMain()
//処理内容		:タイトル画面のメイン処理
//引数			:なし
//戻り値		:なし

void CActionGameApp::procTitleMain()
{
	//Xキーを押されたらフェーズを終了に変更し、ゲーム本編にステータスを移行する準備をする
	if (getInput()->isPressedOnce(DIK_X) && TitleSelect == 0)
	{
		g_TitlePhase = eEnd;
		g_NextStatusFromTitle = ePlaying;
		if (g_pGameOver)
		{
			StopSourceSound(g_pGameOver);
			disposeSound(g_pGameOver);
			g_pGameOver = NULL;
		}
		// 作成されていなければ、作成
		if (!g_pPhaseStart)
		{
			// 第2引数：ループ設定
			// ループしないので、falseを設定
			g_pPhaseStart = createSound(PhaseStart, false);
		}
	}
	//タイトルセレクトの処理
	procTitleSelect();
	//画像が作成されていたら描画する
	if (g_pTitle != NULL)
	{
		renderSprite(g_pTitle);
	}
	if (g_pTitleBalloon != NULL)
	{
		BalloonAnim();
		renderSprite(g_pTitleBalloon);
	}

	PhaseNum = 1;
	Block.Count = BlockPos[PhaseNum - 1].ConnectCount[0] + BlockPos[PhaseNum - 1].ConnectCount[1] + BlockPos[PhaseNum - 1].ConnectCount[2] + BlockPos[PhaseNum - 1].ConnectCount[3] + BlockPos[PhaseNum - 1].ConnectCount[4];
	RightBlock.Count = BlockPos[PhaseNum - 1].Count;
	LeftBlock.Count = BlockPos[PhaseNum - 1].Count;
	Cloud.Count = CloudPos[PhaseNum - 1].Count;
}


//関数名		:procTitleEnd()
//処理内容		:タイトル画面の終了時に行う処理
//引数			:なし
//戻り値		:なし
void CActionGameApp::procTitleEnd()
{
	//g_pTitle が作成されている時のみ破棄する
	if (g_pTitle != NULL)
	{
		//タイトル画面の画像を破棄する
		disposeSprite(g_pTitle);
		g_pTitle = NULL;
	}

	if (g_pTitleBalloon != NULL)
	{
		//タイトルバルーンの画像を破棄する
		disposeSprite(g_pTitleBalloon);
		g_pTitleBalloon = NULL;
	}
}

//関数名		:procTitleSelect()
//処理内容		:タイトル画面のセレクト処理
//引数			:なし
//戻り値		:なし
void CActionGameApp::procTitleSelect()
{
	//アローキーで選択
	if (m_pDirectInput->isPressedOnce(DIK_DOWNARROW))
	{
		//インデックスを加算
		++TitleSelect;
	}
	else if (m_pDirectInput->isPressedOnce(DIK_UPARROW))
	{
		//インデックスを減算
		--TitleSelect;
	}
	//セレクトの補正
	if (TitleSelect > 2)
	{
		TitleSelect = 2;
	}
	else if (TitleSelect < 0)
	{
		TitleSelect = 0;
	}
	//画像のセット
	if (g_pTitleBalloon != NULL)
	{
		for (int j = 0; j < 3; ++j)
		{
			//タイトルセレクトと座標のインデックスを同期
			if (TitleSelect == j)
			{
				g_pTitleBalloon->setPos(g_titleballoonPos[j].PosX, g_titleballoonPos[j].PosY);
			}
		}
	}
}