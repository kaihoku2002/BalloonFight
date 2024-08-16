//----------------------------------------------
// ファイル名 ：ObjSet.cpp
// 概要　　　 ：オブジェクトの生成・配置・描画・破棄の処理
// 作者　　　 ：21Cu0312 河合 奏
// 更新内容   ：2022/03/02 21CU0312 河合 奏 作成
// 　　　　　 ：2022/03/02 21CU0312 河合 奏 ObjCreate()、Objrender()、ObjDispose()を追加
// 　　　　　 ：2022/03/03 21CU0312 河合 奏 ObjSetPos()を追加
//            ：2022/03/07 21CU0312 河合 奏 Backrender()を追加
//------------------------------------------------


#include "CActionGameApp.h"
#include "GameResource.h"



void CActionGameApp::PlayerAnim()
{
	//感電アニメーション
	if (DeathThunderFlag == true)
	{
		++AnimCount[AnimCntThunderDeath];
		if (AnimCount[AnimCntThunderDeath] %  71 != 0)
		{
			if (AnimCount[AnimCntThunderDeath] % 10 == 0)
			{
				g_pPlayer[0]->setAnimation(28);
				g_pPlayer[1]->setAnimation(28);
				if (!g_pThunderDeath)
				{
					DeathThunderFlag = false;
					DeathFallFlag = true;
					DeathFlag = true;
				}
			}
			else if (AnimCount[AnimCntThunderDeath] % 10 < 2)
			{
				g_pPlayer[0]->setAnimation(26);
				g_pPlayer[1]->setAnimation(26);
			}
			else if (AnimCount[AnimCntThunderDeath] % 10 < 4)
			{
				g_pPlayer[0]->setAnimation(29);
				g_pPlayer[1]->setAnimation(29);
			}
			else if (AnimCount[AnimCntThunderDeath] % 10 < 6)
			{
				g_pPlayer[0]->setAnimation(26);
				g_pPlayer[1]->setAnimation(26);
			}
			else
			{
				g_pPlayer[0]->setAnimation(29);
				g_pPlayer[1]->setAnimation(29);
			}
		}
		else
		{
			AnimCount[AnimCntThunderDeath] = 0;
		}
	}
	//死亡アニメーション
	else if (DeathFlag == true)
	{
		++AnimCount[AnimCntPlayerDeath];
		if (AnimCount[AnimCntPlayerDeath] % 13 != 0)
		{
			if (AnimCount[AnimCntPlayerDeath] < 5)
			{
				g_pPlayer[0]->setAnimation(26);
				g_pPlayer[1]->setAnimation(26);
			}
			else if (AnimCount[AnimCntPlayerDeath] < 7)
			{
				g_pPlayer[0]->setAnimation(27);
				g_pPlayer[1]->setAnimation(27);
			}
			else if (AnimCount[AnimCntPlayerDeath] < 11)
			{
				g_pPlayer[0]->setAnimation(26);
				g_pPlayer[1]->setAnimation(26);
			}
			else if (AnimCount[AnimCntPlayerDeath] < 13)
			{
				g_pPlayer[0]->setAnimation(28);
				g_pPlayer[1]->setAnimation(28);
			}
		}
		else
		{
			AnimCount[AnimCntPlayerDeath] = 0;
		}
	}
	//風船割れるアニメーション
	else if (BalloonCount < 2 && BreakBalloon == false)
	{
		if (PlayerLanding == true)
		{
			++AnimCount[0];
			if (AnimCount[0] % 4 != 0)
			{
				if (AnimCount[0] < 4)
				{
					g_pPlayer[0]->setAnimation(7);
					g_pPlayer[1]->setAnimation(7);
					if (AnimCount[0] == 3)
					{
						BreakBalloon = true;
					}
				}
			}
			else
			{
				AnimCount[0] = 0;
			}
		}
		else
		{
			++AnimCount[0];
			if (AnimCount[0] % 4 != 0)
			{
				if (AnimCount[0] < 4)
				{
					g_pPlayer[0]->setAnimation(20);
					g_pPlayer[1]->setAnimation(20);
					if (AnimCount[0] == 3)
					{
						BreakBalloon = true;
					}
				}
			}
			else
			{
				AnimCount[0] = 0;
			}
		}
	}
	else
	{
		//歩行アニメーション
		if (PlayerLanding == true)
		{
			//移動時
			if (MoveAnim == true &&
				((WidthSwitch == true && g_playerMoveSpeed > 0.0f) ||
					(WidthSwitch != true && g_playerMoveSpeed < 0.0f)))
			{
				++AnimCount[0];
				if (AnimCount[0] % 19 != 0)
				{
					if (AnimCount[0] < 7)
					{
						g_pPlayer[0]->setAnimation(4 + (8 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(4 + (8 * -(BalloonCount - 2)));
					}
					else if (AnimCount[0] < 10)
					{
						g_pPlayer[0]->setAnimation(3 + (8 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(3 + (8 * -(BalloonCount - 2)));
					}
					else if (AnimCount[0] < 16)
					{
						g_pPlayer[0]->setAnimation(4 + (8 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(4 + (8 * -(BalloonCount - 2)));
					}
					else if (AnimCount[0] < 19)
					{
						g_pPlayer[0]->setAnimation(5 + (8 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(5 + (8 * -(BalloonCount - 2)));
					}
				}
				else
				{
					//歩行
					// 作成されていなければ、作成
					if (!(g_pStep))
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pStep = createSound(Step, false);
					}
					AnimCount[0] = 0;
				}
			}
			//ブレーキ
			else if (g_playerMoveSpeed != 0.0f)
			{
				g_pPlayer[0]->setAnimation(6 + (8 * -(BalloonCount - 2)));
				g_pPlayer[1]->setAnimation(6 + (8 * -(BalloonCount - 2)));
				if ((WidthSwitch == true && g_playerMoveSpeed < 0.0f) ||
					(WidthSwitch != true && g_playerMoveSpeed > 0.0f))
				{
					NowBrake = true;
				}
			}
			//待機
			else
			{
				++AnimCount[0];
				if (AnimCount[0] % 161 != 0)
				{
					if (AnimCount[0] < 41)
					{
						g_pPlayer[0]->setAnimation(0 + (8 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(0 + (8 * -(BalloonCount - 2)));
					}
					else if (AnimCount[0] < 81)
					{
						g_pPlayer[0]->setAnimation(1 + (8 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(1 + (8 * -(BalloonCount - 2)));
					}
					else if (AnimCount[0] < 121)
					{
						g_pPlayer[0]->setAnimation(0 + (8 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(0 + (8 * -(BalloonCount - 2)));
					}
					else if (AnimCount[0] < 161)
					{
						g_pPlayer[0]->setAnimation(2 + (8 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(2 + (8 * -(BalloonCount - 2)));
					}
				}
				else
				{
					AnimCount[0] = 0;
				}
			}
		}
		//飛行アニメーション
		else
		{
			//羽ばたき
			if (JumpCount > 0)
			{
				++AnimCount[0];
				if (AnimCount[0] % 13 != 0)
				{
					if (AnimCount[0] < 10)
					{
						g_pPlayer[0]->setAnimation(18 + (6 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(18 + (6 * -(BalloonCount - 2)));
					}
					else if (AnimCount[0] < 13)
					{
						g_pPlayer[0]->setAnimation(19 + (6 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(19 + (6 * -(BalloonCount - 2)));
					}
				}
				else
				{
					//ジャンプ
					// 作成されていなければ、作成
					if (g_pJump)
					{
						disposeSound(g_pJump);
						g_pJump = NULL;
					}
					if (!(g_pJump) && (JumpCount % 2 == 0))
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pJump = createSound(Jump, false);
					}
					AnimCount[0] = 0;
					--JumpCount;
				}
			}
			//待機
			else
			{
				++AnimCount[0];
				if (AnimCount[0] % 161 != 0)
				{
					if (AnimCount[0] < 41)
					{
						g_pPlayer[0]->setAnimation(16 + (6 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(16 + (6 * -(BalloonCount - 2)));
					}
					else if (AnimCount[0] < 81)
					{
						g_pPlayer[0]->setAnimation(15 + (6 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(15 + (6 * -(BalloonCount - 2)));
					}
					else if (AnimCount[0] < 121)
					{
						g_pPlayer[0]->setAnimation(17 + (6 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(17 + (6 * -(BalloonCount - 2)));
					}
					else if (AnimCount[0] < 161)
					{
						g_pPlayer[0]->setAnimation(15 + (6 * -(BalloonCount - 2)));
						g_pPlayer[1]->setAnimation(15 + (6 * -(BalloonCount - 2)));
					}
				}
				else
				{
					AnimCount[0] = 0;
				}
			}
		}
	}


	//方向反映
	//ブレーキ中以外
	if (NowBrake != true)
	{
		//左
		if (WidthSwitch != true)
		{
			g_pPlayer[0]->setAngle(0.0f, 180.0f, 0.0f);
			g_pPlayer[1]->setAngle(0.0f, 180.0f, 0.0f);
		}
		//右
		else
		{
			g_pPlayer[0]->setAngle(0.0f, 0.0f, 0.0f);
			g_pPlayer[1]->setAngle(0.0f, 0.0f, 0.0f);
		}
	}
	//ブレーキ中
	else
	{
		NowBrake = false;
	}
}

//入水アニメーション作成
void CActionGameApp::EnteringWaterCreate(CPicture* g_pPicture)
{
	for (int i = 0; i < WaterCount; ++i)
	{
		if (EnteringWater[i] == NULL)
		{
			EnteringWater[i] = createSprite(Tex_EnteringWater, 64.0f, 64.0f);
			EnteringWater[i]->setPos(g_pPicture->getPos().x, g_pGround[0]->getPos().y + 32.0f); 
			
			pEnteringWaterFlag = true;
			break;
		}
	}
}

//入水時のアニメーション
void CActionGameApp::EnteringWaterAnim()
{
	for (int i = 0; i < WaterCount; ++i)
	{
		if (EnteringWater[i] != NULL)
		{
			++AnimCount[AnimCountWater+i];
			if (AnimCount[AnimCountWater + i] % 11 != 0)
			{
				if (AnimCount[AnimCountWater + i] < 3)
				{
					EnteringWater[i]->setAnimation(0);
				}
				else if (AnimCount[AnimCountWater + i] < 7)
				{
					EnteringWater[i]->setAnimation(1);
				}
				else if (AnimCount[AnimCountWater + i] < 11)
				{
					EnteringWater[i]->setAnimation(2);
					if (AnimCount[AnimCountWater + i] == 10)
					{
						disposeSprite(EnteringWater[i]);
						EnteringWater[i] = NULL;
					}
				}
			}
			else
			{
				AnimCount[AnimCountWater + i] = 0;
			}
		}
	}
}

//泡の画像作成
void CActionGameApp::BubbleCreate(CPicture* g_pPicture)
{
	for (int i = 0; i < BubbleCount; ++i)
	{
		if (g_pBubble[i] == NULL)
		{
			g_pBubble[i] = createSprite(Tex_Bubble, 64.0f, 64.0f);
			g_pBubble[i]->setPos(g_pPicture->getPos().x, g_pGround[0]->getPos().y - 32.0f);

			break;
		}
		if (!g_pBuble)
		{
			// 第2引数：ループ設定
			// ループしないので、falseを設定
			g_pBuble = createSound(Buble, false);
		}
	}
}

//泡のアニメーション
void CActionGameApp::BubbleAnim()
{
	for (int i = 0; i < BubbleCount; ++i)
	{
		if (g_pBubble[i] != NULL && g_pBubble[i+1] != NULL && (AnimCountBubble + i) % 2 != 0)
		{
			//泡に触れていない
			if (AnimCount[AnimCountBubble + i] >= 0)
			{
				++AnimCount[AnimCountBubble + i];
				if (AnimCount[AnimCountBubble + i] % 121 != 0)
				{
					if (AnimCount[AnimCountBubble + i] < 31)
					{
						g_pBubble[i]->setAnimation(1);
						g_pBubble[i]->setScale(1.0f, 1.0f);
						g_pBubble[i+1]->setAnimation(1);
						g_pBubble[i+1]->setScale(1.0f, 1.0f);
					}
					else if (AnimCount[AnimCountBubble + i] < 61)
					{
						g_pBubble[i]->setAnimation(1);
						g_pBubble[i]->setScale(56.0f / 64.0f, 1.0f);
						g_pBubble[i+1]->setAnimation(1);
						g_pBubble[i+1]->setScale(56.0f / 64.0f, 1.0f);
					}
					else if (AnimCount[AnimCountBubble + i] < 91)
					{
						g_pBubble[i]->setAnimation(1);
						g_pBubble[i]->setScale(1.0f, 1.0f);
						g_pBubble[i+1]->setAnimation(1);
						g_pBubble[i+1]->setScale(1.0f, 1.0f);
					}
					else
					{
						g_pBubble[i]->setAnimation(1);
						g_pBubble[i]->setScale(1.0f, 56.0f / 64.0f);
						g_pBubble[i+1]->setAnimation(1);
						g_pBubble[i+1]->setScale(1.0f, 56.0f / 64.0f);
					}
				}
				else
				{
					AnimCount[AnimCountBubble + i] = 0;
				}

				if (BubbleMove_xFlag[i] == true)
				{
					BubbleMove_x[i] += 0.2f;
					if (BubbleMove_x[i] >= 4.0f)
					{
						BubbleMove_xFlag[i] = false;
					}
				}
				else
				{
					BubbleMove_x[i] -= 0.2f;
					if (BubbleMove_x[i] <= -4.0f)
					{
						BubbleMove_xFlag[i] = true;
					}
				}
				g_pBubble[i]->setPos(g_pBubble[i]->getPos().x + BubbleMove_x[i],
					g_pBubble[i]->getPos().y + 1.0f);
				g_pBubble[i + 1]->setPos(g_pBubble[i]->getPos().x,
					g_pBubble[i]->getPos().y);

				//プレイヤーに当たった時の処理
				if (g_pPlayer[0]->collisionOffset(g_pBubble[i], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size) &&
					DeathFlag != true && DeathThunderFlag != true &&
					CollisionFlag == true && g_pPlayer[0]->getActive() == true)
				{
					if (g_pBubleBoom)
					{
						disposeSound(g_pBubleBoom);
						g_pBubleBoom = NULL;
					}
					if (!g_pBubleBoom)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pBubleBoom = createSound(BubleBoom, false);
					}
					
					//スコア加算
					ScoreSet(0);
					AddScoreSet(g_pPlayer[0], 0);

					g_pBubble[i]->setAnimation(2);
					g_pBubble[i]->setScale(1.0f, 1.0f);
					g_pBubble[i+1]->setAnimation(2);
					g_pBubble[i+1]->setScale(1.0f, 1.0f);

					AnimCount[AnimCountBubble + i] = -1;
				}
				if (g_pBubble[i]->getPos().y > WINDOW_TOP + 32.0f)
				{
					disposeSprite(g_pBubble[i]);
					g_pBubble[i] = NULL;
					disposeSprite(g_pBubble[i + 1]);
					g_pBubble[i + 1] = NULL;

					AnimCount[AnimCountBubble + i] = 0;
				}
			}
			else if (AnimCount[AnimCountBubble + i] <= -5)
			{
				disposeSprite(g_pBubble[i]);
				g_pBubble[i] = NULL;
				disposeSprite(g_pBubble[i + 1]);
				g_pBubble[i + 1] = NULL;

				AnimCount[AnimCountBubble + i] = 0;
			}
			else if (AnimCount[AnimCountBubble + i] < 0)
			{
				--AnimCount[AnimCountBubble + i];
			}
		}
	}
}

//魚のアニメーション
void CActionGameApp::FishAnim()
{
	//捕食（プレイヤー）
	if (DeathFishFlag == true)
	{
		++AnimCount[AnimCountFish];
		if (AnimCount[AnimCountFish] % 31 != 0)
		{
			if (AnimCount[AnimCountFish] < 5)
			{
				g_pFish->setAnimation(3);
			}
			else if (AnimCount[AnimCountFish] < 9)
			{
				g_pFish->setAnimation(4);
			}
			else if (AnimCount[AnimCountFish] < 13)
			{
				g_pFish->setAnimation(5);
			}
			else if (AnimCount[AnimCountFish] < 19)
			{
				g_pFish->setAnimation(6);
			}
			else if (AnimCount[AnimCountFish] < 25)
			{
				g_pFish->setAnimation(7);
			}
			else if (AnimCount[AnimCountFish] < 31)
			{
				g_pFish->setAnimation(8);
				if (AnimCount[AnimCountFish] == 30)
				{
					g_pFish->setPos(g_pFish->getPos().x - 64.0f, -450.0f);
					DeathStatusSet();
				}
			}
		}
		//通常時
		else
		{
			AnimCount[AnimCountFish] = 0;
		}
	}
	//捕食（敵）
	else if (EnemyDeathFishFlag == true)
	{
		++AnimCount[AnimCountFish];
		if (AnimCount[AnimCountFish] % 31 != 0)
		{
			if (AnimCount[AnimCountFish] < 5)
			{
				g_pFish->setAnimation(9 + (EnemyDeathFishLvel * 2));
			}
			else if (AnimCount[AnimCountFish] < 9)
			{
				g_pFish->setAnimation(10 + (EnemyDeathFishLvel * 2));
			}
			else if (AnimCount[AnimCountFish] < 13)
			{
				g_pFish->setAnimation(9 + (EnemyDeathFishLvel * 2));
			}
			else if (AnimCount[AnimCountFish] < 19)
			{
				g_pFish->setAnimation(6);
			}
			else if (AnimCount[AnimCountFish] < 25)
			{
				g_pFish->setAnimation(7);
			}
			else if (AnimCount[AnimCountFish] < 31)
			{
				g_pFish->setAnimation(8);
				if (AnimCount[AnimCountFish] == 30)
				{
					g_pFish->setPos(g_pFish->getPos().x - 64.0f, -450.0f);
					EnemyDeathFishFlag = false;
				}
			}
		}
		//通常時
		else
		{
			AnimCount[AnimCountFish] = 0;
		}
	}
	else
	{
		if (g_pFish->getPos().y > WINDOW_BOTTOM + (132.0f - 20.0f))
		{
			g_pFish->setAnimation(2);
		}
		else if (g_pFish->getPos().y > WINDOW_BOTTOM + (116.0f - 20.0f))
		{
			g_pFish->setAnimation(1);
		}
		else
		{
			g_pFish->setAnimation(0);
		}
	}
}


//雷のアニメーション
void CActionGameApp::ThunderAnim()
{
	//雷
	if (g_ThunderObj.obj != NULL && (g_ThunderObj.flag & 0b0010 || g_ThunderObj.flag & 0b0001))
	{
		++AnimCount[AnimCountThunder];
		if (AnimCount[AnimCountThunder] == 0)
		{
			g_ThunderObj.obj->setAnimation(0);
		}
		else
		{
			if (AnimCount[AnimCountThunder] < 5)
			{
				if (AnimCount[AnimCountThunder] % 2 == 0)
				{
					g_ThunderObj.obj->setAnimation(0);
					if (!g_pSThunder)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pSThunder = createSound(SThunder, false);
					}
				}
				else
				{
					g_ThunderObj.obj->setAnimation(1);
				}
			}
			else
			{
				if (AnimCount[AnimCountThunder] % 2 == 0)
				{
					g_ThunderObj.obj->setAnimation(2);
				}
				else
				{
					g_ThunderObj.obj->setAnimation(3);
				}
			}
		}
		ThunderAnimFlag = false;
	}
	else
	{
		AnimCount[AnimCountThunder] = 0;
	}

	//雷の球
	for (int i = 0; i < ThunderBallCnt; ++i)
	{
		if (g_ThunderBallObj[i].obj != NULL)
		{
			++AnimCount[AnimCountThunderBall1 + i];
			if (AnimCount[AnimCountThunderBall1 + i] == 0)
			{
				g_ThunderBallObj[i].obj->setAnimation(0);
			}
			else if (AnimCount[AnimCountThunderBall1 + i] % 10 < 6)
			{
				g_ThunderBallObj[i].obj->stepAnimation();
			}
			else if (AnimCount[AnimCountThunderBall1 + i] % 10 < 7)
			{
				g_ThunderBallObj[i].obj->setAnimation(3);
			}
			else if (AnimCount[AnimCountThunderBall1 + i] % 10 < 8)
			{
				g_ThunderBallObj[i].obj->setAnimation(2);
			}
			else if (AnimCount[AnimCountThunderBall1 + i] % 10 < 9)
			{
				g_ThunderBallObj[i].obj->setAnimation(1);
				AnimCount[AnimCountThunderBall1 + i] = 0;
			}
		}
		else
		{
			AnimCount[AnimCountThunderBall1 + i] = 0;
		}
	}

	//雲
	for (int i = 0; i < Cloud.Count; ++i)
	{
		if (g_pCloud[i] != NULL && g_ThunderObj.AnimFlag == true)
		{
			switch (PhaseNum)
			{
			case 1:
				if (AnimCount[AnimCountCloud] == 0)
				{
					++AnimCount[AnimCountCloud + i];
					g_pCloud[i]->setAnimation(0);
				}
				else
				{
					g_pCloud[i]->stepAnimation();
				}
				break;
			default:
				if (CloudThunderRand == 0)
				{
					g_pCloud[0]->stepAnimation();
				}
				else
				{
					g_pCloud[1]->stepAnimation();
				}
				break;
			}

		}
		else
		{
			AnimCount[AnimCountCloud + i] = 0;
			g_pCloud[i]->setAnimation(0);
		}
	}
}

//敵
void CActionGameApp::EnemyAnim()
{
	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
	{
		if (g_enemyObjs[i].obj != NULL && g_enemyObjs[i].enemyVer == 0)
		{
			//飛行アニメーション
			if (g_enemyObjs[i].EnemyStatus == 0)
			{
				++AnimCount[AnimCountEnemy + i];
				if (g_enemyObjs[i].g_pEnemyFlySpeed_Y < 0.0f)
				{
					//エネミーの羽音
					if (g_enemyObjs[i].enemyVer == 0)
					{
						if (g_pEnemyJump[i / 2])
						{
							StopSourceSound(g_pEnemyJump[i / 2]);
							disposeSound(g_pEnemyJump[i / 2]);
							g_pEnemyJump[i / 2] = NULL;
						}
					}
					if (AnimCount[AnimCountEnemy + i] % 81 != 0)
					{
						if (AnimCount[AnimCountEnemy + i] < 21)
						{
							g_enemyObjs[i].obj->setAnimation(8 + (g_enemyObjs[i].EnemyLevel * 18));
							g_enemyObjs[i + 1].obj->setAnimation(8 + (g_enemyObjs[i].EnemyLevel * 18));
						}
						else if (AnimCount[AnimCountEnemy + i] < 41)
						{
							g_enemyObjs[i].obj->setAnimation(9 + (g_enemyObjs[i].EnemyLevel * 18));
							g_enemyObjs[i + 1].obj->setAnimation(9 + (g_enemyObjs[i].EnemyLevel * 18));
						}
						else if (AnimCount[AnimCountEnemy + i] < 61)
						{
							g_enemyObjs[i].obj->setAnimation(8 + (g_enemyObjs[i].EnemyLevel * 18));
							g_enemyObjs[i + 1].obj->setAnimation(8 + (g_enemyObjs[i].EnemyLevel * 18));
						}
						else if (AnimCount[AnimCountEnemy + i] < 81)
						{
							g_enemyObjs[i].obj->setAnimation(10 + (g_enemyObjs[i].EnemyLevel * 18));
							g_enemyObjs[i + 1].obj->setAnimation(10 + (g_enemyObjs[i].EnemyLevel * 18));
						}
					}
					else
					{
						AnimCount[AnimCountEnemy + i] = 0;
					}
				}
				else
				{
					// 作成されていなければ、作成
					if (g_enemyObjs[i].enemyVer == 0)
					{
						if (!g_pEnemyJump[i / 2])
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pEnemyJump[i / 2] = createSound(EnemyJump, true);
							g_pEnemyJump[i / 2]->ChangeVolume(25);
						}
					}
					if (AnimCount[AnimCountEnemy + i] % 9 != 0)
					{
						if (AnimCount[AnimCountEnemy + i] < 7)
						{
							g_enemyObjs[i].obj->setAnimation(11 + (g_enemyObjs[i].EnemyLevel * 18));
							g_enemyObjs[i + 1].obj->setAnimation(11 + (g_enemyObjs[i].EnemyLevel * 18));
						}
						else if (AnimCount[AnimCountEnemy + i] < 9)
						{
							g_enemyObjs[i].obj->setAnimation(12 + (g_enemyObjs[i].EnemyLevel * 18));
							g_enemyObjs[i + 1].obj->setAnimation(12 + (g_enemyObjs[i].EnemyLevel * 18));
						}
					}
					else
					{
						AnimCount[AnimCountEnemy + i] = 0;
					}
				}
			}
			//落下アニメーション
			else if (g_enemyObjs[i].EnemyStatus == 1)
			{
				//エネミーの羽音
				if (g_enemyObjs[i].enemyVer == 0)
				{
					if (g_pEnemyJump[i / 2])
					{
						StopSourceSound(g_pEnemyJump[i / 2]);
						disposeSound(g_pEnemyJump[i / 2]);
						g_pEnemyJump[i / 2] = NULL;
					}
				}
				++AnimCount[AnimCountEnemy + i];
				if (AnimCount[AnimCountEnemy + i] % 7 != 0 && EnemyFallAnimFlag[i] == true)
				{
					if (AnimCount[AnimCountEnemy + i] < 2)
					{
						g_enemyObjs[i].obj->setAnimation(15 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(15 + (g_enemyObjs[i].EnemyLevel * 18));
					}
					else if (AnimCount[AnimCountEnemy + i] < 4)
					{
						g_enemyObjs[i].obj->setAnimation(16 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(16 + (g_enemyObjs[i].EnemyLevel * 18));
					}
					else if (AnimCount[AnimCountEnemy + i] < 7)
					{
						g_enemyObjs[i].obj->setAnimation(17 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(17 + (g_enemyObjs[i].EnemyLevel * 18));
						if (AnimCount[AnimCountEnemy + i] == 6)
						{
							EnemyFallAnimFlag[i] = false;
						}
					}
				}
				else
				{
					AnimCount[AnimCountEnemy + i] = 0;
				}
			}
			//風船膨らませアニメーション
			else if (g_enemyObjs[i].EnemyStatus == 2 && BalloonReloadFlag[i] == true)
			{
				++AnimCount[AnimCountEnemy + i];
				g_enemyObjs[i].obj->setAnimationRange(0 + (g_enemyObjs[i].EnemyLevel * 18), 7 + (g_enemyObjs[i].EnemyLevel * 18));
				g_enemyObjs[i + 1].obj->setAnimationRange(0 + (g_enemyObjs[i].EnemyLevel * 18), 7 + (g_enemyObjs[i].EnemyLevel * 18));

				if (AnimCount[AnimCountEnemy + i] % 81 != 0)
				{
					if (AnimCount[AnimCountEnemy + i] % 10 == 0)
					{
						g_enemyObjs[i].obj->stepAnimation();
						g_enemyObjs[i + 1].obj->stepAnimation();
						if (AnimCount[AnimCountEnemy + i] % 80 == 0)
						{
							BalloonReloadFlag[i] = false;
							g_enemyObjs[i].EnemyStatus = 0;
							if (g_enemyObjs[i].EnemyLevel < 2)
							{
								++g_enemyObjs[i].EnemyLevel;
							}
							
							//復活したので値をリセット
							g_enemyObjs[i].EnemyReturn_Num = 0.0;
						}
					}
				}
				else
				{
					AnimCount[AnimCountEnemy + i] = 0;
				}
			}
			//風船膨らませアニメーション
			else if (g_enemyObjs[i].EnemyStatus == 3)
			{
				++AnimCount[AnimCountEnemy + i];
				if (AnimCount[AnimCountEnemy + i] % 121 != 0)
				{
					if (AnimCount[AnimCountEnemy + i] == 8 || AnimCount[AnimCountEnemy + i] == 24)
					{
						g_enemyObjs[i].obj->setAnimation(0 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(0 + (g_enemyObjs[i].EnemyLevel * 18));
					}
					else if (AnimCount[AnimCountEnemy + i] == 16 || AnimCount[AnimCountEnemy + i] == 32)
					{
						g_enemyObjs[i].obj->setAnimation(1 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(1 + (g_enemyObjs[i].EnemyLevel * 18));
					}
					else if (AnimCount[AnimCountEnemy + i] == 40 || AnimCount[AnimCountEnemy + i] == 56)
					{
						g_enemyObjs[i].obj->setAnimation(2 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(2 + (g_enemyObjs[i].EnemyLevel * 18));
					}
					else if (AnimCount[AnimCountEnemy + i] == 48 || AnimCount[AnimCountEnemy + i] == 64)
					{
						g_enemyObjs[i].obj->setAnimation(3 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(3 + (g_enemyObjs[i].EnemyLevel * 18));
					}
					else if (AnimCount[AnimCountEnemy + i] == 72 || AnimCount[AnimCountEnemy + i] == 88)
					{
						g_enemyObjs[i].obj->setAnimation(4 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(4 + (g_enemyObjs[i].EnemyLevel * 18));
					}
					else if (AnimCount[AnimCountEnemy + i] == 80 || AnimCount[AnimCountEnemy + i] == 96)
					{
						g_enemyObjs[i].obj->setAnimation(5 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(5 + (g_enemyObjs[i].EnemyLevel * 18));
					}
					else if (AnimCount[AnimCountEnemy + i] == 104)
					{
						g_enemyObjs[i].obj->setAnimation(6 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(6 + (g_enemyObjs[i].EnemyLevel * 18));
					}
					else if (AnimCount[AnimCountEnemy + i] == 112)
					{
						g_enemyObjs[i].obj->setAnimation(7 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(7 + (g_enemyObjs[i].EnemyLevel * 18));
					}
					else if (AnimCount[AnimCountEnemy + i] == 120)
					{
						g_enemyObjs[i].obj->setAnimation(8 + (g_enemyObjs[i].EnemyLevel * 18));
						g_enemyObjs[i + 1].obj->setAnimation(8 + (g_enemyObjs[i].EnemyLevel * 18));
						BalloonReloadFlag[i] = false;
					}
				}
				else
				{
					AnimCount[AnimCountEnemy + i] = 0;
				}
			}

			//向いている方向
			if (g_enemyObjs[i].EnemyStatus != 1)
			{
				if (g_enemyObjs[i].g_pEnemyMaxSpeed_X <= 0.0f)
				{
					g_enemyObjs[i].obj->setAngle(0.0f, 0.0f, 0.0f);
					g_enemyObjs[i + 1].obj->setAngle(0.0f, 0.0f, 0.0f);
				}
				else
				{
					g_enemyObjs[i].obj->setAngle(0.0f, 180.0f, 0.0f);
					g_enemyObjs[i + 1].obj->setAngle(0.0f, 180.0f, 0.0f);
				}
			}
		}
	}
}

void CActionGameApp::DeathCoolTimeAnim()
{
	if (g_pPlayer[0]->getActive() == false)
	{
		++AnimCount[AnimCntDeathCoolTime];
		if (AnimCount[AnimCntDeathCoolTime] >= 60)
		{
			g_pPlayer[0]->setActive(true);
			g_pPlayer[1]->setActive(true);
			DeathCoolFlag = true;
			AnimCount[AnimCntDeathCoolTime] = 0;
			g_pPlayer[0]->setAnimation(0);
			g_pPlayer[1]->setAnimation(0);

			//復活
			// 作成されていなければ、作成
			if (!(g_pRespawn) && NowRemainCount < 2 && NowRemainCount > -1 && AnimCount[AnimCntDeathCoolTime] == 0)
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pRespawn = createSound(Respawn, false);
			}
		}
	}
	//復活後のクールタイム
	else if (DeathCoolFlag == true)
	{
		++AnimCount[AnimCntDeathCoolTime];
		if (AnimCount[AnimCntDeathCoolTime] % 10 >= 5)
		{
			renderSprite(g_pPlayer[0], XMFLOAT4(10.0f, 0.0f, 0.0f, 0.3f));
			renderSprite(g_pPlayer[1], XMFLOAT4(10.0f, 0.0f, 0.0f, 0.3f));
		}
		else if (AnimCount[AnimCntDeathCoolTime] % 10 < 5)
		{
			renderSprite(g_pPlayer[0]);
			renderSprite(g_pPlayer[1]);
		}
		if (AnimCount[AnimCntDeathCoolTime] >= 540)
		{
			DeathCoolFlag = false;
			AnimCount[AnimCntDeathCoolTime] = 0;
		}
	}
	else
	{
		AnimCount[AnimCntDeathCoolTime] = 0;
	}
	
}

void CActionGameApp::BalloonAnim()
{
	if (g_pTitleBalloon != NULL)
	{
		++AnimCount[AnimCountBalloon];
		if (AnimCount[AnimCountBalloon] % 61 != 0)
		{
			if (AnimCount[AnimCountBalloon] < 11)
			{
				g_pTitleBalloon->setAnimation(3);
			}
			else if (AnimCount[AnimCountBalloon] < 21)
			{
				g_pTitleBalloon->setAnimation(2);
			}
			else if (AnimCount[AnimCountBalloon] < 31)
			{
				g_pTitleBalloon->setAnimation(1);
			}
			else if (AnimCount[AnimCountBalloon] < 41)
			{
				g_pTitleBalloon->setAnimation(0);
			}
			else if (AnimCount[AnimCountBalloon] < 51)
			{
				g_pTitleBalloon->setAnimation(1);
			}
			else if (AnimCount[AnimCountBalloon] < 61)
			{
				g_pTitleBalloon->setAnimation(2);
			}
		}
		else
		{
			AnimCount[AnimCountBalloon] = 0;
		}
	}
	for (int i = 0; i < 20; ++i)
	{
		if (g_pBalloon[i].Obj != NULL)
		{
			++AnimCount[AnimCountBalloon + i];
			if (g_pBalloon[i].HIt == false)
			{
				if (AnimCount[AnimCountBalloon + i] % 61 != 0)
				{
					if (AnimCount[AnimCountBalloon + i] < 11)
					{
						g_pBalloon[i].Obj->setAnimation(3);
					}
					else if (AnimCount[AnimCountBalloon + i] < 21)
					{
						g_pBalloon[i].Obj->setAnimation(2);
					}
					else if (AnimCount[AnimCountBalloon + i] < 31)
					{
						g_pBalloon[i].Obj->setAnimation(1);
					}
					else if (AnimCount[AnimCountBalloon + i] < 41)
					{
						g_pBalloon[i].Obj->setAnimation(0);
					}
					else if (AnimCount[AnimCountBalloon + i] < 51)
					{
						g_pBalloon[i].Obj->setAnimation(1);
					}
					else if (AnimCount[AnimCountBalloon + i] < 61)
					{
						g_pBalloon[i].Obj->setAnimation(2);
					}
				}
				else
				{
					AnimCount[AnimCountBalloon + i] = 0;
				}
			}
			else
			{
				if (AnimCount[AnimCountBalloon + i] % 2 != 0)
				{
					g_pBalloon[i].Obj->setAnimation(4);
				}
				else
				{
					//風船が割れた音
					// 作成されていなければ、作成
					if (g_pBalloonBom)
					{
						disposeSound(g_pBalloonBom);
						g_pBalloonBom = NULL;
					}
					if (!g_pBalloonBom)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pBalloonBom = createSound(BalloonBom, false);
					}
					disposeSprite(g_pBalloon[i].Obj);
					g_pBalloon[i].Obj = NULL;
					g_pBalloon[i].HIt = false;
				}
			}
			
		}
	}
	
}

void CActionGameApp::DeathStatusSet()
{
	//リスポーン地点にセット
	g_pPlayer[0]->setPos(-(WINDOW_WIDTH / 2.0f) + 152.0f, -300.0f);
	g_pPlayer[1]->setPos(-(WINDOW_WIDTH / 2.0f) + 152.0f, -300.0f);
	g_pPlayer[0]->setActive(false);
	g_pPlayer[1]->setActive(false);

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
	DeathCoolFlag = true;

	//残機・風船の数の調整
	RemainSet();
	BalloonCount = 2;
	FlameCnt = 0;
	g_playerMoveSpeed = 0.0f;
	g_pPlayerFlySpeed = 0.0f;
	g_pJumpRise = 0.0f;
	g_pJumpPower = 0.0f;
	Gravity = 0.0f;

	//雷の値調整
	//フェーズを戻す
	g_ThunderObj.Phase = 0;


}