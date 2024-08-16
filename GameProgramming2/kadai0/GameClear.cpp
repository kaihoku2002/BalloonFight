//----------------------------------------------------------
// ファイル名		：GameClear.cpp
// 概要				：ゲームクリアの処理の関数の定義
// 作成者			：21CU0136 松本賢太
// 更新内容			：2022/03/22 21CU0136松本　作成
//----------------------------------------------------------
#include "CActionGameApp.h"
#include "GameResource.h"

/*
 * ゲームクリア画面の処理を行う部分
 */
void CActionGameApp::procClear()
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
			StopSourceSound(g_pEnemyJump[i / 2]);
			disposeSound(g_pEnemyJump[i / 2]);
			g_pEnemyJump[i] = NULL;
		}
	}

	//フェーズの進行状態によって処理をい切り替える
	switch (g_GameClear.g_GameClearPhase)
	{
	case eBegin:
	{
		//タイトル画面の開始時の処理を行う
		procClearBegin();
		//進行状態をメインに切り替える
		g_GameClear.g_GameClearPhase = eMain;
	}
	break;

	//メイン
	case eMain:
	{
		IsLoad = IsLoad & 0b0111;
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

		//プレイヤーの画像は最初は0だけ作成、表示する
		for (int i = 0; i < 2; i++)
		{
			if (g_pPlayer[i] != NULL)
			{
				renderSprite(g_pPlayer[i]);
			}
		}


		////敵の処理
		for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
		{
			//敵画像が作成されていたら描画する
			if (g_enemyObjs[i].obj != NULL)
			{
				renderSprite(g_enemyObjs[i].obj);
			}
		}

		//魚の描画
		renderSprite(g_pFish);

		//オブジェクトの描画
		ThunderRender();
		Objrender();
		//----------------------------------------------------------------------------------;
		//タイトル画面のメイン処理を行う
		procClearMain();
	}
	break;

	//終了時
	case eEnd:
	{
		IsLoad = IsLoad | 0b0010;
		//タイトル画面の終了処理を行う
		procClearEnd();
		//再度タイトル画面に来た時に開始から処理を行うためにフェーズを戻しておく
		g_GameClear.g_GameClearPhase = eBegin;
		//次のステータスを設定する
		SetNextGameStatus(g_GameClear.g_NextStatusFromGameClear);
	}
	break;
	}
}
/*
* 関数名	：procClearBegin
* 処理内容	：ゲームクリア画面の開始時に行う処理
* 引数		：なし
* 戻り値	：なし
*/
void CActionGameApp::procClearBegin()
{
}

/*
* 関数名	：procClearMain
* 処理内容	：ゲームクリア画面のメイン処理
* 引数		：なし
* 戻り値	：なし
*/
void CActionGameApp::procClearMain()
{
	++g_GameClear.Cnt;
	////Xキー(スタートボタン)が入力されたときはタイトルに移行
	//if (getInput()->isPressedOnce(DIK_X))
	//{
	//	//タイトルにステータスを移行する準備をする
	//	g_GameClear.g_GameClearPhase = eEnd;
	//	g_GameClear.g_NextStatusFromGameClear = ePlaying;
	//	if(PhaseNum < 3)
	//	{
	//		++PhaseNum;
	//	}
	//	else
	//	{
	//		PhaseNum = 1;
	//		BalloonCount = 2;
	//	}
	//	Block.Count = BlockPos[PhaseNum - 1].ConnectCount[0] + BlockPos[PhaseNum - 1].ConnectCount[1] + BlockPos[PhaseNum - 1].ConnectCount[2] + BlockPos[PhaseNum - 1].ConnectCount[3] + BlockPos[PhaseNum - 1].ConnectCount[4];
	//	RightBlock.Count = BlockPos[PhaseNum - 1].Count;
	//	LeftBlock.Count = BlockPos[PhaseNum - 1].Count;
	//	Cloud.Count = CloudPos[PhaseNum - 1].Count;
	//}
	if (g_pPhaseCler && (g_pPhaseCler->isPlayed() == false))
	{
		//タイトルにステータスを移行する準備をする
		g_GameClear.g_GameClearPhase = eEnd;
		g_GameClear.g_NextStatusFromGameClear = ePlaying;
		if (PhaseNum == 3)
		{
			BonusON = true;
		}
		if (PhaseNum < 3)
		{
			++PhaseNum;
		}
		else
		{
			PhaseNum = 1;
			BalloonCount = 2;
		}
		Block.Count = BlockPos[PhaseNum - 1].ConnectCount[0] + BlockPos[PhaseNum - 1].ConnectCount[1] + BlockPos[PhaseNum - 1].ConnectCount[2] + BlockPos[PhaseNum - 1].ConnectCount[3] + BlockPos[PhaseNum - 1].ConnectCount[4];
		RightBlock.Count = BlockPos[PhaseNum - 1].Count;
		LeftBlock.Count = BlockPos[PhaseNum - 1].Count;
		Cloud.Count = CloudPos[PhaseNum - 1].Count;
	}
	SoundPlay();
}
/*
* 関数名	：procClearEnd
* 処理内容	：ゲームクリア画面の終了時に行う処理
* 引数		：なし
* 戻り値	：なし
*/
void CActionGameApp::procClearEnd()
{
	g_GameClear.Cnt = 0;

	//プレイヤー
	//リスポーン地点にセット
	g_pPlayer[0]->setPos(-(WINDOW_WIDTH / 2.0f) + 152.0f, -300.0f);
	g_pPlayer[1]->setPos(-(WINDOW_WIDTH / 2.0f) + 152.0f, -300.0f);

	//各種フラグの初期化
	JumpCount = 0;
	MoveAnim = false;
	NowBrake = false;
	BreakBalloon = false;
	ThunderAnimFlag = false;
	DeathFlag = false;
	DeathFishFlag = false;
	DeathFallFlag = false;
	DeathThunderFlag = false;
	pEnteringWaterFlag = false;

	//残機・風船の数の調整
	FlameCnt = 0;
	g_playerMoveSpeed = 0.0f;
	g_pPlayerFlySpeed = 0.0f;
	g_pJumpRise = 0.0f;
	g_pJumpPower = 0.0f;
	Gravity = 0.0f;

	//敵
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
	for (int i = 0; i < AddScoreIndex; ++i)
	{
		if (g_pAddScore[i] != NULL)
		{
			disposeFont(g_pAddScore[i]);
			g_pAddScore[i] = NULL;
			AddScoreCnt[i] = 0;
		}
	}

	EnemyDeathFishFlag = false;
	AnimCount[AnimCountFish] = 0;
	g_pFish->setAnimation(0);
	if (g_pFish != NULL)
	{
		disposeSprite(g_pFish);
	}
	
	ThunderDispose();

	//破棄
	procPlayMain_EnemyDispose(); //Enemy
	ObjDispose();                //OBj
	SoundDispose();              //音声
}