//----------------------------------------------
// ファイル名 ：Fish.cpp
// 概要　　　 ：魚の処理
// 作者　　　 ：21Cu0207 海北憲吾
// 更新内容   ：3/9 魚の表示、横移動
// 　　　　　 ：
// 　　　　　 ：
//           ：
//------------------------------------------------


#include "CActionGameApp.h"
#include "GameResource.h"

//魚の移動処理
void CActionGameApp::procPlayMain_moveFish()     
{
	//魚を移動させる
	if (FishLanding == true)
	{
		if (Movewhich == true)
		{
			g_pFish->setPos(g_pFish->getPos().x - 3.0, g_pFish->getPos().y);
			g_pFish->setAngle(0.0, 180.0f, 0.0f);
		}
		else
		{
			g_pFish->setPos(g_pFish->getPos().x + 3.0, g_pFish->getPos().y);
			g_pFish->setAngle(0.0, 0.0f, 0.0f);
		}
			
	}
	
	

	//魚が画面端に行ったら反転させる
	//左端に行ったとき
	if (g_pFish->getPos().x < -480.0f)
		Movewhich = false;

	//左端に行ったとき
	else if (g_pFish->getPos().x > 480.0f)
		Movewhich = true;

	for (int i = 0; i < 2; i++)
	{
		if (AimPlayer == 1 || AimPlayer == 2)
		{
			//魚が上に行き過ぎない様に制御する
			if (g_pFish->getPos().y < -340.0f)
			{
				//プレイヤーを追うようにする
				//魚よりプレイヤーが左にいる場合
				if (g_pPlayer[i]->getPos().x > g_pFish->getPos().x)
				{
					g_pFish->setPos(g_pFish->getPos().x + 4.0f, g_pFish->getPos().y + 3.0f);
				}
				else if (g_pPlayer[i]->getPos().x < g_pFish->getPos().x)
				{
					g_pFish->setPos(g_pFish->getPos().x - 4.0f, g_pFish->getPos().y + 3.0f);
				}
			}
		}
	}
	for (int i = 0; i < ENEMY_OBJECT_COUNT; i++)
	{
		if (AimEnemy == i + 1 && g_enemyObjs[i].obj != NULL)
		{
			//魚が上に行き過ぎない様に制御する
			if (g_pFish->getPos().y < -340.0f)
			{
				//プレイヤーを追うようにする
				//魚よりプレイヤーが左にいる場合
				if (g_enemyObjs[i].obj->getPos().x > g_pFish->getPos().x)
				{
					g_pFish->setPos(g_pFish->getPos().x + 4.0f, g_pFish->getPos().y + 3.0f);
				}
				else if (g_enemyObjs[i].obj->getPos().x < g_pFish->getPos().x)
				{
					g_pFish->setPos(g_pFish->getPos().x - 4.0f, g_pFish->getPos().y + 3.0f);
				}
			}
		}
	}
	
	FishAnim();
	
}

//魚のアルゴリズム
void CActionGameApp::procPlayMain_AlgorithmFish()
{
	//プレイヤーが地面より下にいる　かつ　プレイヤーのX座標と魚のX座標が同じになった時に捕食体制になる
	for (int i = 0; i < 2; ++i)
	{
		if ((g_pPlayer[i]->getPos().y - 64.0f < -(WINDOW_HEIGHT / 2.0f - 140.0f) && 
			g_pPlayer[i]->getPos().x - 32.0f > WINDOW_LEFT + (64.0f * 4.0f) &&
			g_pPlayer[i]->getPos().x + 32.0f < WINDOW_RIGHT - (64.0f * 4.0f) &&
			PlayerLanding == false && g_pPlayer[i]->getPos().x + ActiveArea_Num >= g_pFish->getPos().x - ActiveArea_Num && g_pPlayer[i]->getPos().x - ActiveArea_Num <= g_pFish->getPos().x + ActiveArea_Num
			) || DeathFishFlag == true)
		{
			if (!g_pSFish && FishLanding == true)
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pSFish = createSound(SFish, false);
			}
			//プレイヤーと横軸の当たり判定を設定する
			/*if (g_pPlayer[i]->getPos().x + ActiveArea_Num >= g_pFish->getPos().x - ActiveArea_Num && g_pPlayer[i]->getPos().x - ActiveArea_Num <= g_pFish->getPos().x + ActiveArea_Num)*/
				AimPlayer = i + 1;
				FishLanding = false;
		}

		//魚が捕食をやめた時に徐々に元の座標に戻るようにする
		else if (AimPlayer == 0 && AimEnemy == 0)
		{
			if (g_pFish->getPos().y > -450.0f)
			{
				FishPos = g_pFish->getPos().x;
				g_pFish->setPos(FishPos, g_pFish->getPos().y - 2.0f);
			}
			else
			{
				FishPos = g_pFish->getPos().x;
				g_pFish->setPos(FishPos, -450.0f);
			}
		}
		else
		{
			AimPlayer = 0;
		}
	}

	//敵が地面より下にいる　かつ　敵のX座標と魚のX座標が同じになった時に捕食体制になる
	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
	{
		if (g_enemyObjs[i].enemyVer == 0 && g_enemyObjs[i].obj != NULL)
		{
			if ((g_enemyObjs[i].obj->getPos().y - 64.0f < -(WINDOW_HEIGHT / 2.0f - 140.0f) &&
				g_enemyObjs[i].obj->getPos().x - 32.0f > WINDOW_LEFT + (64.0f * 4.0f) &&
				g_enemyObjs[i].obj->getPos().x + 32.0f < WINDOW_RIGHT - (64.0f * 4.0f) &&
				g_enemyObjs[i].obj->getPos().x + ActiveArea_Num >= g_pFish->getPos().x - ActiveArea_Num &&
				g_enemyObjs[i].obj->getPos().x - ActiveArea_Num <= g_pFish->getPos().x + ActiveArea_Num) ||
				EnemyDeathFishFlag == true)
			{
				if (!g_pSFish && FishLanding == true)
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pSFish = createSound(SFish, false);
				}
				//プレイヤーと横軸の当たり判定を設定する
				/*if (g_pPlayer[i]->getPos().x + ActiveArea_Num >= g_pFish->getPos().x - ActiveArea_Num && g_pPlayer[i]->getPos().x - ActiveArea_Num <= g_pFish->getPos().x + ActiveArea_Num)*/
				AimEnemy = i+1;
				FishLanding = false;
			}

			//魚が捕食をやめた時に徐々に元の座標に戻るようにする
			else if (AimPlayer == 0 && AimEnemy == 0)
			{
				if (g_pFish->getPos().y > -450.0f)
				{
					FishPos = g_pFish->getPos().x;
					g_pFish->setPos(FishPos, g_pFish->getPos().y - 2.0f);
				}
				else
				{
					FishPos = g_pFish->getPos().x;
					g_pFish->setPos(FishPos, -450.0f);
				}
			}
			else if(AimEnemy == i+1)
			{
				AimEnemy = 0;
			}
		}
		else if (AimEnemy == i + 1)
		{
			AimEnemy = 0;
		}
	}

	if (g_pFish->getPos().y <= -450.0f)
	{
		FishLanding = true;
	}
	
	//プレイヤーと魚の当たり判定を書く
	//魚がプレイヤーの半分までX軸が上になったらプレイヤーは死ぬ
	for (int i = 0; i < 2; i++)
	{
		if (g_pFish->getPos().y + 80.0f > g_pPlayer[i]->getPos().y && g_pFish->getPos().y > WINDOW_BOTTOM + (140.0f - 20.0f))
		{
			if (g_pPlayer[0]->getPos().y - 48.0f <= g_pFish->getPos().y && g_pPlayer[0]->getPos().x - KillArea_Num <= g_pFish->getPos().x + KillArea_Num)
			{
				DeathFishFlag = true;
				if (!g_pSFishDeath)
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pSFishDeath = createSound(SFishDeath, false);
				}
			}
			
		}
	}
	//敵
	for (int i = 0; i < ENEMY_OBJECT_COUNT; i++)
	{
		if (g_enemyObjs[i].obj != NULL)
		{
			if (g_pFish->getPos().y + 80.0f > g_enemyObjs[i].obj->getPos().y && g_pFish->getPos().y > WINDOW_BOTTOM + (140.0f - 20.0f))
			{
				if (g_enemyObjs[i].obj->getPos().y - 48.0f <= g_pFish->getPos().y && g_enemyObjs[i].obj->getPos().x - KillArea_Num <= g_pFish->getPos().x + KillArea_Num)
				{
					if (!g_pSFishDeath)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pSFishDeath = createSound(SFishDeath, false);
					}
					EnemyDeathFishLvel = g_enemyObjs[i].EnemyLevel;
					EnemyDeathFishFlag = true;
					disposeSprite(g_enemyObjs[i].obj);
					g_enemyObjs[i].obj = NULL;

					disposeSprite(g_enemyObjs[i + 1].obj);
					g_enemyObjs[i + 1].obj = NULL;
				}
			}
		}
	}
}