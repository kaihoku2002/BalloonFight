//#include "CActionGameApp.h"
//
///*
// * ゲーム本編の処理を行う部分
// */
//void CActionGameApp::procGame()
//{
//}


#include "CActionGameApp.h"
#include "GameResource.h"
#include "Player.h"
#include "time.h"

//変数宣言--------------------------------------
//ゲーム画面のフェーズを管理する変数
ePhase g_GamePhase = eBegin;
//背景の画像を管理する変数
CPicture* g_pBackground = NULL;
//ゲーム画面から次へ進むときのフローを管理する変数
eGameStatus g_NextStatusFromGame = eNone;




////敵の情報をまとめた構造体
//struct Enemy
//{
//	CPicture* obj;			//画像管理用
//	XMFLOAT2 beginPos;		//初期座標
//};
//
////敵の数
//const int ENEMY_OBJECT_COUNT = 5;
////敵の表示サイズ
//const float ENEMY_SIZE_X = 32.0f;
//const float ENEMY_SIZE_Y = 32.0f;
//
////敵の情報を管理する変数
//Enemy g_enemyObjs[ENEMY_OBJECT_COUNT] =
//{
//	{NULL,XMFLOAT2(-100.0f + (48.0f * 0.0f), 100.0f)},		//0
//	{NULL,XMFLOAT2(-100.0f + (48.0f * 1.0f), 100.0f)},		//1
//	{NULL,XMFLOAT2(-100.0f + (48.0f * 2.0f), 100.0f)},		//2
//	{NULL,XMFLOAT2(-100.0f + (48.0f * 3.0f), 100.0f)},		//3
//	{NULL,XMFLOAT2(-100.0f + (48.0f * 4.0f), 100.0f)},		//4
//
//};
////敵の移動速度
//float g_enemyMoveSpeed = 1.0f;

/*
 * ゲーム本編の処理を行う部分
 */
void CActionGameApp::procGame()
{
	//フェーズの進行状態によって処理を切り替える
	switch (g_GamePhase)
	{
		//開始時
		case eBegin:
		{
			//ゲーム画面の開始処理
			procPlayBegin();
			//進行状態をメインに切り替える
			g_GamePhase = eMain;
		}
			break;

			//メイン
		case eMain:
		{
			//ゲームロード
			IsLoad = IsLoad & 0b1101;
			//ゲーム画面のメイン処理
			procPlayMain();
		}
		break;

		//終了時
		case eEnd:
		{
			//ゲーム画面の終了処理
			//procPlayEnd();
			//再度ゲーム画面に来た時に開始から処理を行うためにフェーズを戻しておく
			g_GamePhase = eBegin;
			//次のステータスを設定する
			SetNextGameStatus(g_NextStatusFromGame);
		}
		break;
	}
}

//関数名		:procTitleBegin()
//処理内容		:ゲーム画面の開始時に行う処理
//引数			:なし
//戻り値		:なし

void CActionGameApp::procPlayBegin()
{
	if (BonusON == true)
	{
		if (!g_pBonusBgm)
		{
			// 第2引数：ループ設定
			// ループしないので、falseを設定
			g_pBonusBgm = createSound(BonusBgm, false);
			BGMCreateTimeCnt = timeGetTime();
		}
		DeathCoolFlag = false;
		//UIの生成・配置
		UIcreate();
		UIsetPos();

		//g_pPlayer が NULLの時のみ画像を作成する
		for (int i = 0; i < 2; ++i)
		{
			if (g_pPlayer[i] == NULL)
			{
				//プレイヤーの画像を作成・配置する

				//プレイヤーの画像は最初は0だけ作成、表示する
				g_pPlayer[i] = createSprite(Tex_Player, PLAYER_SIZE_X, PLAYER_SIZE_Y);
				g_pPlayer[0]->setPos(-(WINDOW_WIDTH / 2.0f) + 152.0f, -300.0f);
				WidthSwitch = true;
				/*g_pPlayer[1]->setPos(100.0f, -100.0f);*/
			}
		}

		//オブジェクト作成
		BObjCreate();
		//オブジェクト設置
		BObjSetPos();
	}
	else if (BonusON != true)
	{
		//g_pBackground　が　NULLの時のみ画像を作成する
		if (g_pBackground == NULL)
		{
			//背景の画像を作成する
			g_pBackground = createSprite(Tex_BackBack);
		}
		if (g_pBackAnim == NULL)
		{
			//背景の画像を作成する
			g_pBackAnim = createSprite(Tex_BackAnim);
			g_pBackAnim->setPos(g_pBackAnim->getPos().x + 2.0f, g_pBackAnim->getPos().y - 2.0f);
		}

		//UIの生成・配置
		UIcreate();
		UIsetPos();

		//敵の画像の作成
		procPlayMain_EnemyCreate();

		g_pFish = createSprite(Tex_Fish, 80.0f, 128.0f);
		g_pFish->setPos(0.0f, -450);

		//g_pPlayer が NULLの時のみ画像を作成する
		for (int i = 0; i < 2; ++i)
		{
			if (g_pPlayer[i] == NULL)
			{
				//プレイヤーの画像を作成・配置する

				//プレイヤーの画像は最初は0だけ作成、表示する
				g_pPlayer[i] = createSprite(Tex_Player, PLAYER_SIZE_X, PLAYER_SIZE_Y);
				g_pPlayer[0]->setPos(-(WINDOW_WIDTH / 2.0f) + 152.0f, WINDOW_BOTTOM + Ground.Size_Y + Wave.Size_Y - 8.0f);
				WidthSwitch = true;
				/*g_pPlayer[1]->setPos(100.0f, -100.0f);*/
			}
		}

		//オブジェクト生成・配置
		ObjCreate();
		ObjSetPos();
		ThunderCreate();

		//if (PhaseNum < 4)
		//{
		//	//オブジェクト生成・配置
		//	ObjCreate();
		//	ObjSetPos();
		//	ThunderCreate();
		//}
		//if (PhaseNum == 4)
		//{
		//	BonusStage();
		//}


		////敵の画像を作成する
		//for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
		//{
		//	//それぞれの　obj　が　NULLの時のみ画像を作成する
		//	if (g_enemyObjs[i].obj == NULL)
		//	{
		//		//敵の画像を作成・配置する
		//		/*g_enemyObjs[i].obj = createSprite(Tex_Enemy, ENEMY_SIZE_X, ENEMY_SIZE_Y);*/
		//		g_enemyObjs[i].obj->setPos(g_enemyObjs[i].beginPos);
		//	}
		//}
	}

}

//関数名		:procPlayMain()
//処理内容		:タイトル画面のメイン処理
//引数			:なし
//戻り値		:なし

void CActionGameApp::procPlayMain()
{
	//乱数の種の取得
	srand((unsigned)time(NULL));
	if (BonusON == true)
	{
		BonusStage();
		BGMNowTimeCnt = timeGetTime();
		if (((BGMNowTimeCnt - BGMCreateTimeCnt) / 1000.0) > 32.4)
		{
			IsLoad = IsLoad | 0b1000;
			g_NextStatusFromGame = eBonusClear;
			g_GamePhase = eEnd;
		}
	}
	else if (BonusON != true)
	{
		//残機がなくなったらゲームオーバー画面に移行
		if (NowRemainCount < 0 && g_pPlayer[0]->getActive() == true)
		{
			IsLoad = IsLoad | 0b0100;
			g_NextStatusFromGame = eGameOver;
			g_GamePhase = eEnd;

			//ステージオーバーSEを作成
			// 作成されていなければ、作成
			if (!g_pGameOver)
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pGameOver = createSound(SGameOver, false);
			}
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
		}

		//敵がいなくなったらゲームクリア
		EnemyCount = 0;
		for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
		{
			if (g_enemyObjs[i].obj != NULL && g_enemyObjs[i].EnemyStatus != 4 &&
				g_enemyObjs[i].enemyVer == 0)
			{
				++EnemyCount;
			}
		}
		if (EnemyCount <= 0)
		{
			IsLoad = IsLoad | 0b1000;
			g_NextStatusFromGame = eGameClear;
			g_GamePhase = eEnd;
			//ステージクリアSEを作成
			// 作成されていなければ、作成
			if (!g_pPhaseCler)
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pPhaseCler = createSound(PhaseCler, false);
			}
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
			//魚死
			if (g_pSFishDeath)
			{
				StopSourceSound(g_pSFishDeath);
				disposeSound(g_pSFishDeath);
				g_pSFishDeath = NULL;
			}
		}

		//-----------------------------------------------------------------------------------------
		//デバッグ用
		//最初の30秒スキップ
		if (m_pDirectInput->isPressedOnce(DIK_S) && g_ThunderObj.Phase == 0)
		{
			g_ThunderObj.ThunderTime = 28 * 60;
		}
		//２発目以降の10秒スキップ
		else if (m_pDirectInput->isPressedOnce(DIK_S) && g_ThunderObj.Phase >= 1)
		{
			g_ThunderObj.ThunderTime = 8 * 60;
		}
		//画面上の弾削除
		for (int i = 0; i < ThunderBallCnt; ++i)
		{
			if (m_pDirectInput->isPressedOnce(DIK_D))
			{
				disposeSprite(g_ThunderBallObj[i].obj);
				g_ThunderBallObj[i].obj = NULL;
				//個数カウントを減らす
				--g_ThunderObj.Cnt;
				//補正
				if (g_ThunderObj.Cnt < 0)
				{
					g_ThunderObj.Cnt = 0;
				}
			}
		}
		//押されたキーによってステータスを変更する、Xが入力された時はクリア画面に移行
		if (getInput()->isPressedOnce(DIK_X))
		{
			CollisionFlag = !CollisionFlag;
		}

		/*デバッグ確認
		if (m_pDirectInput->isPressedOnce(DIK_V))
		{
			IsLoad = IsLoad | 0b1000;
			g_NextStatusFromGame = eBonusClear;
			g_GamePhase = eEnd;
		}*/

		//Zが入力された時はゲームオーバー画面に移行
		else if (m_pDirectInput->isPressedOnce(DIK_Z))
		{
			NowRemainCount = 0;
			DeathStatusSet();
			//ステージオーバーSEを作成
			// 作成されていなければ、作成
			if (!g_pGameOver)
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pGameOver = createSound(SGameOver, false);
			}
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
		}
		//Cが入力された時はゲームクリア画面に移行
		else if (m_pDirectInput->isPressedOnce(DIK_C))
		{
			IsLoad = IsLoad | 0b1000;
			g_NextStatusFromGame = eGameClear;
			g_GamePhase = eEnd;
			//ステージクリアSEを作成
			// 作成されていなければ、作成
			if (!g_pPhaseCler)
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pPhaseCler = createSound(PhaseCler, false);
			}
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
			//ゲームスタート
			if (g_pPhaseStart)
			{
				StopSourceSound(g_pPhaseStart);
				disposeSound(g_pPhaseStart);
				g_pPhaseStart = NULL;
			}
			//魚死
			if (g_pSFishDeath)
			{
				StopSourceSound(g_pSFishDeath);
				disposeSound(g_pSFishDeath);
				g_pSFishDeath = NULL;
			}
		}
		//-----------------------------------------------------------------------------------------

		for (int i = 0; i < 2; i++)
		{
			//プレイヤーの操作
			if (g_pPlayer[i] != NULL && DeathFishFlag == false &&
				g_pPlayer[i]->getActive() == true)
			{
				//プレイヤーの移動速度
				procPlayMain_movePlayer();
			}
		}

		//画面端の処理
		procPlayMain_BothEnds();

		//背景の描画
		Backrender();
		if (g_pBackAnim != NULL)
		{
			++AnimCount[AnimCountBack];
			if (AnimCount[AnimCountBack] % 30 == 0)
			{
				g_pBackAnim->stepAnimation();
				AnimCount[AnimCountBack] = 0;
			}
			renderSprite(g_pBackAnim);
		}

		//UIの描画
		UIrender();
		//加算スコアの描画
		for (int i = 0; i < AddScoreIndex; ++i)
		{
			if (g_pAddScore[i] != NULL)
			{
				++AddScoreCnt[i];
				renderFont(g_pAddScore[i], AddScore[i]);
				if (AddScoreCnt[i] % 60 == 0)
				{
					disposeFont(g_pAddScore[i]);
					g_pAddScore[i] = NULL;
					AddScoreCnt[i] = 0;
				}
			}
		}

		////敵の操作
		//procPlayMain_procEnemy();
		////敵の処理
		//for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
		//{
		//	//敵画像が作成されていたら描画する
		//	if (g_enemyObjs[i].obj != NULL)
		//	{
		//		renderSprite(g_enemyObjs[i].obj);
		//	}
		//}
		procPlayMain_procEnemy();

		procPlayMain_moveFish();
		procPlayMain_AlgorithmFish();

		//プレイヤー画像が作成されていたら描画する
		//プレイヤーの画像は最初は0だけ作成、表示する
		if (DeathFlag != true && DeathFishFlag != true && DeathCoolFlag != true)
		{
			for (int i = 0; i < 2; i++)
			{
				if (g_pPlayer[i] != NULL)
				{
					renderSprite(g_pPlayer[i]);
				}
			}
		}

		//魚の描画
		renderSprite(g_pFish);

		//オブジェクトの描画
		ThunderRender();
		Objrender();


		if (getInput()->isPressedOnce(DIK_0))
		{
			NowRemainCount = RemainCount;
		}

		//雷処理
		Thunder();
		ThunderBall();

		//泡の処理
		BubbleAnim();

		//水しぶきの描画
		EnteringWaterAnim();
		for (int i = 0; i < WaterCount; ++i)
		{
			if (EnteringWater[i] != NULL)
			{
				renderSprite(EnteringWater[i]);
			}
		}


		DeathCoolTimeAnim();
	}

	//サウンド関連
	// 作成
	SoundCreate();
	//再生
	SoundPlay();
	//破棄
	SoundDispose();
}



//関数名		:procPlayMain_procEnemy()
//処理内容		:敵の処理
//引数			:なし
//戻り値		:なし
//void CActionGameApp::procPlayMain_procEnemy()
//{
//	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
//	{
//		//敵画像が作成されていた時のみ以下の処理を行う
//		if (g_enemyObjs[i].obj != NULL)
//		{
//			//移動する
//			XMFLOAT4 enemyPos = g_enemyObjs[i].obj->getPos();
//			enemyPos.y -= g_enemyMoveSpeed;
//			g_enemyObjs[i].obj->setPos(enemyPos);
//
//			//描画する
//			renderSprite(g_enemyObjs[i].obj);
//		}
//	}
//}

//関数名		:procPlayEnd()
//処理内容		:ゲーム画面の終了時に行う処理
//引数			:なし
//戻り値		:なし

void CActionGameApp::procPlayEnd()
{
	if (BonusON == true)
	{
		BObjDispose();
	}
	else
	{

		////敵画像を破棄する
		//for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
		//{
		//	//それぞれの obj が作成されている場合のみ破棄する
		//	if (g_enemyObjs[i].obj != NULL)
		//	{
		//		disposeSprite(g_enemyObjs[i].obj);
		//		g_enemyObjs[i].obj = NULL;
		//	}
		//}

		//g_pPlayer が作成されている時のみ破棄する
		for (int i = 0; i < 2; i++)
		{
			if (g_pPlayer[i] != NULL)
			{
				disposeSprite(g_pPlayer[i]);
				g_pPlayer[i] = NULL;
			}
		}

		//敵の破棄
		procPlayMain_EnemyDispose();
		disposeSprite(g_pFish);

		//g_pBackground が作成されている時のみ破棄する
		if (g_pBackground != NULL)
		{
			//タイトル画面の画像を破棄する
			disposeSprite(g_pBackground);
			g_pBackground = NULL;
		}
		if (g_pBackAnim != NULL)
		{
			//タイトル画面の画像を破棄する
			disposeSprite(g_pBackAnim);
			g_pBackAnim = NULL;
		}

		//UIの破棄
		UIdispose();

		//オブジェクトの破棄
		ThunderDispose();
		ObjDispose();
	}
	//プレイヤーの横移動処理関連-------------------------------
		//プレイヤーの移動速度
	g_playerMoveSpeed = 0.0f;
	g_pRunSpeed = 0.0f;
	//プレイヤーの空中移動速度
	g_pPlayerFlySpeed = 0.0f;
}