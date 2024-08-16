//----------------------------------------------
// ファイル名 ：ObjSet.cpp
// 概要　　　 ：オブジェクトの生成・配置・描画・破棄の処理
// 作者　　　 ：21Cu0312 河合 奏
// 更新内容   ：2022/03/28 21CU0312 河合 奏 作成
//------------------------------------------------


#include "CActionGameApp.h"
#include "GameResource.h"
void CActionGameApp::SoundCreate()
{
	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
	{

		//敵画像が作成されていたら処理を行う
		if (g_enemyObjs[i].obj != NULL)
		{
			//エネミー降下
			// 作成されていなければ、作成
			if (!g_pEnemyDown && g_enemyObjs[i].EnemyStatus == 1)
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pEnemyDown = createSound(EnemyDown, true);
			}
		}
	}
}

void CActionGameApp::SoundPlay()
{
	//魚死
	if (g_pSFishDeath)
	{
		//ゲームスタート
		if (g_pPhaseStart)
		{
			StopSourceSound(g_pPhaseStart);
			disposeSound(g_pPhaseStart);
			g_pPhaseStart = NULL;
		}
		PlaySourceSound(g_pSFishDeath);
	}
	//プレイヤー落下
	if (g_pFall)
	{
		//ゲームスタート
		if (g_pPhaseStart)
		{
			StopSourceSound(g_pPhaseStart);
			disposeSound(g_pPhaseStart);
			g_pPhaseStart = NULL;
		}
		PlaySourceSound(g_pFall);
	}
	//エネミー死亡時
	if (g_pEnemyDeath)
	{
		//ゲームスタート
		if (g_pPhaseStart)
		{
			StopSourceSound(g_pPhaseStart);
			disposeSound(g_pPhaseStart);
			g_pPhaseStart = NULL;
		}
		PlaySourceSound(g_pEnemyDeath);
	}
	// 作成されていたら再生
	//ゲームスタート
	if (g_pPhaseStart)
	{
		PlaySourceSound(g_pPhaseStart);

		//エネミー降下
		if (g_pEnemyDown)
		{
			g_pEnemyDown->ChangeVolume(0);
		}
		//プレイヤージャンプ
		if (g_pJump)
		{
			g_pJump->ChangeVolume(0);
		}
		//プレイヤー歩行
		if (g_pStep)
		{
			g_pStep->ChangeVolume(0);
		}
		//プレイヤーの復活
		if (g_pRespawn)
		{
			g_pRespawn->ChangeVolume(0);
		}
		//ぶつかった音
		if (g_pHit)
		{
			g_pHit->ChangeVolume(0);
		}
		//風船が割れた音
		if (g_pBalloonBom)
		{
			g_pBalloonBom->ChangeVolume(0);
		}
		//エネミーの羽音
		for (int i = 0; i < 5; ++i)
		{
			if (g_pEnemyJump[i])
			{
				g_pEnemyJump[i]->ChangeVolume(0);
			}
		}
		//泡発生
		if (g_pBuble)
		{
			g_pBuble->ChangeVolume(0);
		}
		if (g_pBubleBoom)
		{
			g_pBubleBoom->ChangeVolume(0);
		}
		//入水
		if (g_pWater)
		{
			g_pWater->ChangeVolume(0);
		}
		//魚出現
		if (g_pSFish)
		{
			g_pSFish->ChangeVolume(0);
		}
		//エネミーの着陸
		if (g_pSEnemyLanding)
		{
			g_pSEnemyLanding->ChangeVolume(0);
		}
	}
	//フェーズクリア
	else if (g_pPhaseCler)
	{
		PlaySourceSound(g_pPhaseCler);

		//エネミー降下
		if (g_pEnemyDown)
		{
			g_pEnemyDown->ChangeVolume(0);
		}
		//プレイヤージャンプ
		if (g_pJump)
		{
			g_pJump->ChangeVolume(0);
		}
		//プレイヤー歩行
		if (g_pStep)
		{
			g_pStep->ChangeVolume(0);
		}
		//プレイヤーの復活
		if (g_pRespawn)
		{
			g_pRespawn->ChangeVolume(0);
		}
		//ぶつかった音
		if (g_pHit)
		{
			g_pHit->ChangeVolume(0);
		}
		//風船が割れた音
		if (g_pBalloonBom)
		{
			g_pBalloonBom->ChangeVolume(0);
		}
		//エネミーの羽音
		for (int i = 0; i < 5; ++i)
		{
			if (g_pEnemyJump[i])
			{
				g_pEnemyJump[i]->ChangeVolume(0);
			}
		}
		//泡発生
		if (g_pBuble)
		{
			g_pBuble->ChangeVolume(0);
		}
		if (g_pBubleBoom)
		{
			g_pBubleBoom->ChangeVolume(0);
		}
		//入水
		if (g_pWater)
		{
			g_pWater->ChangeVolume(0);
		}
		//魚出現
		if (g_pSFish)
		{
			g_pSFish->ChangeVolume(0);
		}
		//エネミーの着陸
		if (g_pSEnemyLanding)
		{
			g_pSEnemyLanding->ChangeVolume(0);
		}
	}
	else if (g_pGameOver)
	{
		PlaySourceSound(g_pGameOver);

		//エネミー降下
		if (g_pEnemyDown)
		{
			g_pEnemyDown->ChangeVolume(0);
		}
		//プレイヤージャンプ
		if (g_pJump)
		{
			g_pJump->ChangeVolume(0);
		}
		//プレイヤー歩行
		if (g_pStep)
		{
			g_pStep->ChangeVolume(0);
		}
		//プレイヤーの復活
		if (g_pRespawn)
		{
			g_pRespawn->ChangeVolume(0);
		}
		//ぶつかった音
		if (g_pHit)
		{
			g_pHit->ChangeVolume(0);
		}
		//風船が割れた音
		if (g_pBalloonBom)
		{
			g_pBalloonBom->ChangeVolume(0);
		}
		//エネミーの羽音
		for (int i = 0; i < 5; ++i)
		{
			if (g_pEnemyJump[i])
			{
				g_pEnemyJump[i]->ChangeVolume(0);
			}
		}
		//泡発生
		if (g_pBuble)
		{
			g_pBuble->ChangeVolume(0);
		}
		//泡取得
		if (g_pBubleBoom)
		{
			g_pBubleBoom->ChangeVolume(0);
		}
		//入水
		if (g_pWater)
		{
			g_pWater->ChangeVolume(0);
		}
		//魚出現
		if (g_pSFish)
		{
			g_pSFish->ChangeVolume(0);
		}
		//エネミーの着陸
		if (g_pSEnemyLanding)
		{
			g_pSEnemyLanding->ChangeVolume(0);
		}
	}
	else
	{
		//エネミー降下
		if (g_pEnemyDown)
		{
			g_pEnemyDown->ChangeVolume(100);
		}
		//プレイヤージャンプ
		if (g_pJump)
		{
			g_pJump->ChangeVolume(100);
		}
		//プレイヤー歩行
		if (g_pStep)
		{
			g_pStep->ChangeVolume(100);
		}
		//プレイヤーの復活
		if (g_pRespawn)
		{
			g_pRespawn->ChangeVolume(100);
		}
		//ぶつかった音
		if (g_pHit)
		{
			g_pHit->ChangeVolume(100);
		}
		//風船が割れた音
		if (g_pBalloonBom)
		{
			g_pBalloonBom->ChangeVolume(100);
		}
		//エネミーの羽音
		for (int i = 0; i < 5; ++i)
		{
			if (g_pEnemyJump[i])
			{
				g_pEnemyJump[i]->ChangeVolume(25);
			}
		}
		//泡発生
		if (g_pBuble)
		{
			g_pBuble->ChangeVolume(100);
		}
		//泡取得
		if (g_pBubleBoom)
		{
			g_pBubleBoom->ChangeVolume(100);
		}
		//入水
		if (g_pWater)
		{
			g_pWater->ChangeVolume(100);
		}
		//魚出現
		if (g_pSFish)
		{
			g_pSFish->ChangeVolume(100);
		}
		//エネミーの着陸
		if (g_pSEnemyLanding)
		{
			g_pSEnemyLanding->ChangeVolume(100);
		}
	}
	//エネミー降下
	if (g_pEnemyDown)
	{
		PlaySourceSound(g_pEnemyDown);
	}
	//プレイヤージャンプ
	if (g_pJump)
	{
		PlaySourceSound(g_pJump);
	}
	//プレイヤー歩行
	if (g_pStep)
	{
		PlaySourceSound(g_pStep);
	}
	//プレイヤーの復活
	if (g_pRespawn)
	{
		PlaySourceSound(g_pRespawn);
	}
	//ぶつかった音
	if (g_pHit)
	{
		PlaySourceSound(g_pHit);
	}
	//風船が割れた音
	if (g_pBalloonBom)
	{
		PlaySourceSound(g_pBalloonBom);
	}
	//エネミーの羽音
	for (int i = 0; i < 5; ++i)
	{
		if (g_pEnemyJump[i])
		{
			PlaySourceSound(g_pEnemyJump[i]);
		}
	}
	//泡発生
	if (g_pBuble)
	{
		PlaySourceSound(g_pBuble);
	}
	//泡取得
	if (g_pBubleBoom)
	{
		PlaySourceSound(g_pBubleBoom);
	}
	//入水
	if (g_pWater)
	{
		PlaySourceSound(g_pWater);
	}
	//感電死
	if (g_pThunderDeath)
	{
		PlaySourceSound(g_pThunderDeath);
	}
	//魚出現
	if (g_pSFish)
	{
		PlaySourceSound(g_pSFish);
	}
	//雷出現
	if (g_pSThunder)
	{
		PlaySourceSound(g_pSThunder);
	}
	//雷反射
	if (g_pThunderHit)
	{
		PlaySourceSound(g_pThunderHit);
	}
	//エネミーの着陸
	if (g_pSEnemyLanding)
	{
		PlaySourceSound(g_pSEnemyLanding);
	}
	//ボーナスステージBGM
	if (g_pBonusBgm)
	{
		PlaySourceSound(g_pBonusBgm);
	}
	//ボーナスポイント
	if (g_pPoint)
	{
		PlaySourceSound(g_pPoint);
	}
	//ボーナスパーフェクト
	if (g_pPerfect)

	{
		PlaySourceSound(g_pPerfect);
	}
}

void CActionGameApp::SoundDispose()
{
	// 再生し終わったら削除
	//（ループ設定trueの場合は入らない）
	//ゲームスタート
	if (g_pPhaseStart && (g_pPhaseStart->isPlayed() == false))
	{
		disposeSound(g_pPhaseStart);
		g_pPhaseStart = NULL;
	}
	//フェーズクリア
	if (g_pPhaseCler && (g_pPhaseCler->isPlayed() == false))
	{
		disposeSound(g_pPhaseCler);
		g_pPhaseCler = NULL;
	}
	//エネミー降下
	EnemyCount = 0;
	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
	{
		if (g_enemyObjs[i].obj != NULL && g_enemyObjs[i].EnemyStatus == 1 &&
			g_enemyObjs[i].enemyVer == 0)
		{
			++EnemyCount;
		}
	}
	if (g_pEnemyDown && EnemyCount <= 0)
	{
		disposeSound(g_pEnemyDown);
		g_pEnemyDown = NULL;
	}
	//エネミー死亡時
	if (g_pEnemyDeath && (g_pEnemyDeath->isPlayed() == false))
	{
		disposeSound(g_pEnemyDeath);
		g_pEnemyDeath = NULL;
	}
	//プレイヤージャンプ
	if (g_pJump && (g_pJump->isPlayed() == false))
	{
		disposeSound(g_pJump);
		g_pJump = NULL;
	}
	//プレイヤー歩行
	if (g_pStep && (g_pStep->isPlayed() == false))
	{
		disposeSound(g_pStep);
		g_pStep = NULL;
	}
	//プレイヤーの復活
	if (g_pRespawn && (g_pRespawn->isPlayed() == false))
	{
		disposeSound(g_pRespawn);
		g_pRespawn = NULL;
	}
	//ぶつかった音
	if (g_pHit && (g_pHit->isPlayed() == false))
	{
		disposeSound(g_pHit);
		g_pHit = NULL;
	}
	//風船が割れた音
	if (g_pBalloonBom && (g_pBalloonBom->isPlayed() == false))
	{
		disposeSound(g_pBalloonBom);
		g_pBalloonBom = NULL;
	}
	//泡発生
	if (g_pBuble && (g_pBuble->isPlayed() == false))
	{
		disposeSound(g_pBuble);
		g_pBuble = NULL;
	}
	//泡取得
	if (g_pBubleBoom && (g_pBubleBoom->isPlayed() == false))
	{
		disposeSound(g_pBubleBoom);
		g_pBubleBoom = NULL;
	}
	//ゲームオーバー
	if (g_pGameOver && (g_pGameOver->isPlayed() == false))
	{
		disposeSound(g_pGameOver);
		g_pGameOver = NULL;
	}
	//入水
	if (g_pWater && (g_pWater->isPlayed() == false))
	{
		disposeSound(g_pWater);
		g_pWater = NULL;
	}
	//プレイヤー落下
	if (g_pFall && (g_pFall->isPlayed() == false))
	{
		disposeSound(g_pFall);
		g_pFall = NULL;
	}
	//感電死
	if (g_pThunderDeath && (g_pThunderDeath->isPlayed() == false))
	{
		disposeSound(g_pThunderDeath);
		g_pThunderDeath = NULL;
	}
	//魚出現
	if (g_pSFish && (g_pSFish->isPlayed() == false))
	{
		disposeSound(g_pSFish);
		g_pSFish = NULL;
	}
	//魚死
	if (g_pSFishDeath && (g_pSFishDeath->isPlayed() == false))
	{
		disposeSound(g_pSFishDeath);
		g_pSFishDeath = NULL;
	}
	//雷出現
	if (g_pSThunder && (g_pSThunder->isPlayed() == false))
	{
		disposeSound(g_pSThunder);
		g_pSThunder = NULL;
	}
	//雷反射
	if (g_pThunderHit && (g_pThunderHit->isPlayed() == false))
	{
		disposeSound(g_pThunderHit);
		g_pThunderHit = NULL;
	}
	//エネミーの着陸
	if (g_pSEnemyLanding && (g_pSEnemyLanding->isPlayed() == false))
	{
		disposeSound(g_pSEnemyLanding);
		g_pSEnemyLanding = NULL;
	}
	//ボーナスステージBGM
	if (g_pBonusBgm && (g_pBonusBgm->isPlayed() == false))
	{
		disposeSound(g_pBonusBgm);
		g_pBonusBgm = NULL;
	}
	//ボーナスポイント
	if (g_pPoint && (g_pPoint->isPlayed() == false))
	{
		disposeSound(g_pPoint);
		g_pPoint = NULL;
	}
	//ボーナスパーフェクト
	if (g_pPerfect && (g_pPerfect->isPlayed() == false))
	{
		disposeSound(g_pPerfect);
		g_pPerfect = NULL;
	}
}
