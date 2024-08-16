//----------------------------------------------
// ファイル名 ：Collision.cpp
// 概要　　　 ：当たり判定の処理
// 作者　　　 ：21Cu0312 河合 奏
// 更新内容   ：2022/03/04 21CU0312 河合 奏 作成
// 　　　　　 ：2022/03/04 21CU0312 河合 奏 UnderCollision()を追加
//            ：2022/03/07 21CU0312 河合 奏 UnderCollision()のすり抜けバグを修正
// 　　　　　 ：2022/03/07 21CU0312 河合 奏 SideCollision()、OverCollision()を追加
//            ：2022/03/08 21CU0312 河合 奏 OverCollision()のすり抜けバグを修正
//------------------------------------------------

#include "CActionGameApp.h"
#include "GameResource.h"

//当たり判定（上）
void CActionGameApp::UnderCollision(CPicture* Getg_pPicture, XMFLOAT4 GetBeforePos,int i)
{
	if(GetBeforePos.y >= Getg_pPicture->getPos().y)
	{
		//地面
		//中央
		for (int j = 0; j < Ground.Count; ++j)
		{
			if (Getg_pPicture->getPos().y > (g_pGround[j]->getPos().y + (Ground.Size_Y / 2.0f) + (100.0f / 2.0f))
				&& Getg_pPicture->collisionOffset(g_pGround[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size))
			{
				//位置を当たり判定の外側にずらす
				Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pGround[j]->getPos().y + (Ground.Size_Y / 2.0f) + PLAYER_SIZE_Y / 2.0f);
				if(Getg_pPicture == g_pPlayer[0] || Getg_pPicture == g_pPlayer[1])
				{
					//着陸状態にする
					PlayerLanding = true;
				}
				else if (Getg_pPicture == g_enemyObjs[i].obj && g_enemyObjs[i].EnemyStatus == 1)
				{
					if (g_pSEnemyLanding)
					{
						disposeSound(g_pSEnemyLanding);
						g_pSEnemyLanding = NULL;
					}
					// 作成されていなければ、作成
					if (!g_pSEnemyLanding)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pSEnemyLanding = createSound(SEnemyLanding, false);
					}
					
					//着陸状態にする
					g_enemyObjs[i].EnemyStatus = 2;
				}
				break;
			}
		}
		//右端
		if (Getg_pPicture->getPos().y > (g_pRightGround->getPos().y + (RightGround.Size_Y / 2.0f) + (100.0f / 2.0f) + 4.0f)
			&& Getg_pPicture->collisionOffset(g_pRightGround, EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size))
		{
			//位置を当たり判定の外側にずらす
			Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pRightGround->getPos().y + (RightGround.Size_Y / 2.0f) + PLAYER_SIZE_Y / 2.0f);
			if (Getg_pPicture == g_pPlayer[0] || Getg_pPicture == g_pPlayer[1])
			{
				//着陸状態にする
				PlayerLanding = true;
			}
			else if (Getg_pPicture == g_enemyObjs[i].obj && g_enemyObjs[i].EnemyStatus == 1)
			{
				if (g_pSEnemyLanding)
				{
					disposeSound(g_pSEnemyLanding);
					g_pSEnemyLanding = NULL;
				}
				// 作成されていなければ、作成
				if (!g_pSEnemyLanding)
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pSEnemyLanding = createSound(SEnemyLanding, false);
				}
				//着陸状態にする
				g_enemyObjs[i].EnemyStatus = 2;
			}
		}
		//左端
		if (Getg_pPicture->getPos().y > (g_pLeftGround->getPos().y + (LeftGround.Size_Y / 2.0f) + (100.0f / 2.0f))
			&& Getg_pPicture->collisionOffset(g_pLeftGround, EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size))
		{
			//位置を当たり判定の外側にずらす
			Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pLeftGround->getPos().y + (LeftGround.Size_Y / 2.0f) + PLAYER_SIZE_Y / 2.0f);
			if (Getg_pPicture == g_pPlayer[0] || Getg_pPicture == g_pPlayer[1])
			{
				//着陸状態にする
				PlayerLanding = true;
			}
			else if (Getg_pPicture == g_enemyObjs[i].obj && g_enemyObjs[i].EnemyStatus == 1)
			{
				if (g_pSEnemyLanding)
				{
					disposeSound(g_pSEnemyLanding);
					g_pSEnemyLanding = NULL;
				}
				// 作成されていなければ、作成
				if (!g_pSEnemyLanding)
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pSEnemyLanding = createSound(SEnemyLanding, false);
				}
				//着陸状態にする
				g_enemyObjs[i].EnemyStatus = 2;
			}
		}

		//浮島
		//中央
		for (int j = 0; j < Block.Count; ++j)
		{
			if (Getg_pPicture->getPos().y > (g_pBlock[j]->getPos().y + (Block.Size_Y / 2.0f) + (100.0f / 2.0f))
				&& Getg_pPicture->collisionOffset(g_pBlock[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
				&& g_pBlock[j] != NULL)
			{
				//位置を当たり判定の外側にずらす
				Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pBlock[j]->getPos().y + (Block.Size_Y / 2.0f) + PLAYER_SIZE_Y / 2.0f);
				if (Getg_pPicture == g_pPlayer[0] || Getg_pPicture == g_pPlayer[1])
				{
					//着陸状態にする
					PlayerLanding = true;
				}
				else if (Getg_pPicture == g_enemyObjs[i].obj && g_enemyObjs[i].EnemyStatus == 1)
				{
					if (g_pSEnemyLanding)
					{
						disposeSound(g_pSEnemyLanding);
						g_pSEnemyLanding = NULL;
					}
					// 作成されていなければ、作成
					if (!g_pSEnemyLanding)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pSEnemyLanding = createSound(SEnemyLanding, false);
					}
					//着陸状態にする
					g_enemyObjs[i].EnemyStatus = 2;
				}
				break;
			}
		}
		//右端
		for (int j = 0; j < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++j)
		{
			if (Getg_pPicture->getPos().y > (g_pRightBlock[j]->getPos().y + (RightBlock.Size_Y / 2.0f) + (100.0f / 2.0f))
				&& Getg_pPicture->collisionOffset(g_pRightBlock[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
				&& g_pRightBlock[j] != NULL)
			{
				//位置を当たり判定の外側にずらす
				Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pRightBlock[j]->getPos().y + (RightBlock.Size_Y / 2.0f) + PLAYER_SIZE_Y / 2.0f);
				if (Getg_pPicture == g_pPlayer[0] || Getg_pPicture == g_pPlayer[1])
				{
					//着陸状態にする
					PlayerLanding = true;
				}
				else if (Getg_pPicture == g_enemyObjs[i].obj && g_enemyObjs[i].EnemyStatus == 1)
				{
					if (g_pSEnemyLanding)
					{
						disposeSound(g_pSEnemyLanding);
						g_pSEnemyLanding = NULL;
					}
					// 作成されていなければ、作成
					if (!g_pSEnemyLanding)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pSEnemyLanding = createSound(SEnemyLanding, false);
					}
					//着陸状態にする
					g_enemyObjs[i].EnemyStatus = 2;
				}
				break;
			}
		}
		//左端
		for (int j = 0; j < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++j)
		{
			if (Getg_pPicture->getPos().y > (g_pLeftBlock[j]->getPos().y + (LeftBlock.Size_Y / 2.0f) + (100.0f / 2.0f))
				&& Getg_pPicture->collisionOffset(g_pLeftBlock[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
				&& g_pLeftBlock[j] != NULL)
			{
				//位置を当たり判定の外側にずらす
				Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pLeftBlock[j]->getPos().y + (LeftBlock.Size_Y / 2.0f) + PLAYER_SIZE_Y / 2.0f);
				if (Getg_pPicture == g_pPlayer[0] || Getg_pPicture == g_pPlayer[1])
				{
					//着陸状態にする
					PlayerLanding = true;
				}
				else if (Getg_pPicture == g_enemyObjs[i].obj && g_enemyObjs[i].EnemyStatus == 1)
				{
					if (g_pSEnemyLanding)
					{
						disposeSound(g_pSEnemyLanding);
						g_pSEnemyLanding = NULL;
					}
					// 作成されていなければ、作成
					if (!g_pSEnemyLanding)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pSEnemyLanding = createSound(SEnemyLanding, false);
					}
					//着陸状態にする
					g_enemyObjs[i].EnemyStatus = 2;
				}
				break;
			}
		}
		//浮島(柱)
		//頂点
		for (int j = 0; j < (BlockBerPos[PhaseNum - 1].ConnectCount[0] + BlockBerPos[PhaseNum - 1].ConnectCount[1] + BlockBerPos[PhaseNum - 1].ConnectCount[2] + BlockBerPos[PhaseNum - 1].ConnectCount[3] + BlockBerPos[PhaseNum - 1].ConnectCount[4]); ++j)
		{
			if (Getg_pPicture->getPos().y > (g_pBlockBer[j]->getPos().y + (BlockBer.Size_Y / 2.0f) + (100.0f / 2.0f))
				&& Getg_pPicture->collisionOffset(g_pBlockBer[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
				&& g_pBlockBer[j] != NULL)
			{
				//位置を当たり判定の外側にずらす
				Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pBlockBer[j]->getPos().y + (BlockBer.Size_Y / 2.0f) + PLAYER_SIZE_Y / 2.0f);
				if (Getg_pPicture == g_pPlayer[0] || Getg_pPicture == g_pPlayer[1])
				{
					//着陸状態にする
					PlayerLanding = true;
				}
				else if (Getg_pPicture == g_enemyObjs[i].obj && g_enemyObjs[i].EnemyStatus == 1)
				{
					if (g_pSEnemyLanding)
					{
						disposeSound(g_pSEnemyLanding);
						g_pSEnemyLanding = NULL;
					}
					// 作成されていなければ、作成
					if (!g_pSEnemyLanding)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pSEnemyLanding = createSound(SEnemyLanding, false);
					}
					//着陸状態にする
					g_enemyObjs[i].EnemyStatus = 2;
				}
				break;
			}
		}

		//重力を初期化
		if (PlayerLanding == true)
		{
			Gravity = 0.0f;
			//着陸した瞬間の横移動速度を維持
			if (g_pPlayerFlySpeed != 0.0f)
			{
				g_playerMoveSpeed = g_pPlayerFlySpeed;
				if (g_playerMoveSpeed > 0.0f)
				{
					WidthSwitch = true;
				}
				else if (g_playerMoveSpeed < 0.0f)
				{
					WidthSwitch = false;
				}
				g_pPlayerFlySpeed = 0.0f;
			}
		}
	}
}

//当たり判定（側面）
void CActionGameApp::SideCollision(CPicture* Getg_pPicture, int i)
{
	//地面
	//右端
	if (Getg_pPicture->getPos().y < (g_pRightGround->getPos().y + (RightGround.Size_Y / 2.0f) + (100.0f / 2.0f))
		&& Getg_pPicture->getPos().x >= (g_pRightGround->getPos().x + (RightGround.Size_X / 2.0f))
		&& Getg_pPicture->collisionOffset(g_pRightGround, EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size))
	{
		//位置を当たり判定の外側にずらす
		Getg_pPicture->setPos(g_pRightGround->getPos().x + (RightGround.Size_X / 2.0f) + (40.0f / 2.0f), Getg_pPicture->getPos().y);
		//プレイヤーの移動方向を反転
		if (Getg_pPicture == g_pPlayer[0])
		{
			//ぶつかった音
			// 作成されていなければ、作成
			if (!(g_pHit))
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pHit = createSound(Hit, false);
			}
			g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
			if (g_pPlayerFlySpeed > 1.0f)
			{
				g_pPlayerFlySpeed -= 0.5f;
			}
			else
			{
				g_pPlayerFlySpeed = 0.5f;
			}
		}
		if (Getg_pPicture == g_enemyObjs[i].obj)
		{
			//死亡時の落下中
			if (g_enemyObjs[i].EnemyStatus == 1)
			{
				//１の場合は２に
				if (g_enemyObjs[i].EnemyCourse == 1)
				{
					g_enemyObjs[i].EnemyCourse = 2;
					//落下時間をリセット
					g_enemyObjs[i].EnemyFall = 0;
					g_enemyObjs[i].EnemyFallSpeed = 0;
					g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					g_enemyObjs[i+1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
				}
				//２の場合は１に
				else if (g_enemyObjs[i].EnemyCourse == 2)
				{
					g_enemyObjs[i].EnemyCourse = 1;
					//落下時間をリセット
					g_enemyObjs[i].EnemyFall = 0;
					g_enemyObjs[i].EnemyFallSpeed = 0;
					g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
				}
			}
			else
			{
				g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
				g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
				if (g_enemyObjs[i].g_pEnemyFlySpeed_X > 1.0f)
				{
					g_enemyObjs[i].g_pEnemyFlySpeed_X -= 0.5f;
				}
				else
				{
					g_enemyObjs[i].g_pEnemyFlySpeed_X = 0.5f;
				}
			}
		}
	}
	//左端
	if (Getg_pPicture->getPos().y < (g_pLeftGround->getPos().y + (LeftGround.Size_Y / 2.0f) + (100.0f / 2.0f))
		&& Getg_pPicture->getPos().x <= (g_pLeftGround->getPos().x - (LeftGround.Size_X / 2.0f))
		&& Getg_pPicture->collisionOffset(g_pLeftGround, EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size))
	{
		//位置を当たり判定の外側にずらす
		Getg_pPicture->setPos(g_pLeftGround->getPos().x - (LeftGround.Size_X / 2.0f) - (40.0f / 2.0f), Getg_pPicture->getPos().y);
		//プレイヤーの移動方向を反転
		if (Getg_pPicture == g_pPlayer[0])
		{
			//ぶつかった音
			// 作成されていなければ、作成
			if (!(g_pHit))
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pHit = createSound(Hit, false);
			}
			g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
			if (g_pPlayerFlySpeed < -1.0f)
			{
				g_pPlayerFlySpeed += 0.5f;
			}
			else
			{
				g_pPlayerFlySpeed = -0.5f;
			}
		}
		if (Getg_pPicture == g_enemyObjs[i].obj)
		{
			//死亡時の落下中
			if (g_enemyObjs[i].EnemyStatus == 1)
			{
				//１の場合は２に
				if (g_enemyObjs[i].EnemyCourse == 1)
				{
					g_enemyObjs[i].EnemyCourse = 2;
					//落下時間をリセット
					g_enemyObjs[i].EnemyFall = 0;
					g_enemyObjs[i].EnemyFallSpeed = 0;
					g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
				}
				//２の場合は１に
				else if (g_enemyObjs[i].EnemyCourse == 2)
				{
					g_enemyObjs[i].EnemyCourse = 1;
					//落下時間をリセット
					g_enemyObjs[i].EnemyFall = 0;
					g_enemyObjs[i].EnemyFallSpeed = 0;
					g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
				}
			}
			else
			{
				g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
				g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
				if (g_enemyObjs[i].g_pEnemyFlySpeed_X < 1.0f)
				{
					g_enemyObjs[i].g_pEnemyFlySpeed_X += 0.5f;
				}
				else
				{
					g_enemyObjs[i].g_pEnemyFlySpeed_X = -0.5f;
				}
			}
		}
	}

	//浮き島
	//右端
	for (int j = 0; j < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++j)
	{
		//位置を当たり判定の外側にずらす
		if (Getg_pPicture->getPos().y - 16.0f > (g_pRightBlock[j]->getPos().y - (RightBlock.Size_Y / 2.0f) - (96.0f / 2.0f))
			&& Getg_pPicture->getPos().y < (g_pRightBlock[j]->getPos().y + (RightBlock.Size_Y / 2.0f) + (100.0f / 2.0f))
			&& Getg_pPicture->getPos().x >= (g_pRightBlock[j]->getPos().x + (RightBlock.Size_X / 2.0f))
			&& Getg_pPicture->collisionOffset(g_pRightBlock[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
			&& g_pRightBlock[j] != NULL)
		{
			//位置を当たり判定の外側にずらす
			Getg_pPicture->setPos(g_pRightBlock[j]->getPos().x + (RightBlock.Size_X / 2.0f) + (40.0f / 2.0f), Getg_pPicture->getPos().y);
			//プレイヤーの移動方向を反転
			if (Getg_pPicture == g_pPlayer[0])
			{
				//ぶつかった音
			// 作成されていなければ、作成
				if (!(g_pHit))
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pHit = createSound(Hit, false);
				}
				g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
				if (g_pPlayerFlySpeed > 1.0f)
				{
					g_pPlayerFlySpeed -= 0.5f;
				}
				else
				{
					g_pPlayerFlySpeed = 0.5f;
				}
			}
			if (Getg_pPicture == g_enemyObjs[i].obj)
			{
				//死亡時の落下中
				if (g_enemyObjs[i].EnemyStatus == 1)
				{
					//１の場合は２に
					if (g_enemyObjs[i].EnemyCourse == 1)
					{
						g_enemyObjs[i].EnemyCourse = 2;
						//落下時間をリセット
						g_enemyObjs[i].EnemyFall = 0;
						g_enemyObjs[i].EnemyFallSpeed = 0;
						g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					}
					//２の場合は１に
					else if (g_enemyObjs[i].EnemyCourse == 2)
					{
						g_enemyObjs[i].EnemyCourse = 1;
						//落下時間をリセット
						g_enemyObjs[i].EnemyFall = 0;
						g_enemyObjs[i].EnemyFallSpeed = 0;
						g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					}
				}
				else
				{
					g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
					g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
					if (g_enemyObjs[i].g_pEnemyFlySpeed_X > 1.0f)
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_X -= 0.5f;
					}
					else
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_X = 0.5f;
					}
				}
			}
			break;
		}
	}
	//左端
	for (int j = 0; j < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++j)
	{
		//位置を当たり判定の外側にずらす
		if (Getg_pPicture->getPos().y - 16.0f > (g_pLeftBlock[j]->getPos().y - (LeftBlock.Size_Y / 2.0f) - (96.0f / 2.0f))
			&& Getg_pPicture->getPos().y < (g_pLeftBlock[j]->getPos().y + (LeftBlock.Size_Y / 2.0f) + (100.0f / 2.0f))
			&& Getg_pPicture->getPos().x <= (g_pLeftBlock[j]->getPos().x - (LeftBlock.Size_X / 2.0f))
			&& Getg_pPicture->collisionOffset(g_pLeftBlock[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
			&& g_pLeftBlock[j] != NULL)
		{
			Getg_pPicture->setPos(g_pLeftBlock[j]->getPos().x - (LeftBlock.Size_X / 2.0f) - (40.0f / 2.0f), Getg_pPicture->getPos().y);
			//プレイヤーの移動方向を反転
			if (Getg_pPicture == g_pPlayer[0])
			{
				//ぶつかった音
			// 作成されていなければ、作成
				if (!(g_pHit))
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pHit = createSound(Hit, false);
				}
				g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
				if (g_pPlayerFlySpeed < -1.0f)
				{
					g_pPlayerFlySpeed += 0.5f;
				}
				else
				{
					g_pPlayerFlySpeed = -0.5f;
				}
			}
			if (Getg_pPicture == g_enemyObjs[i].obj)
			{
				//死亡時の落下中
				if (g_enemyObjs[i].EnemyStatus == 1)
				{
					//１の場合は２に
					if (g_enemyObjs[i].EnemyCourse == 1)
					{
						g_enemyObjs[i].EnemyCourse = 2;
						//落下時間をリセット
						g_enemyObjs[i].EnemyFall = 0;
						g_enemyObjs[i].EnemyFallSpeed = 0;
						g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					}
					//２の場合は１に
					else if (g_enemyObjs[i].EnemyCourse == 2)
					{
						g_enemyObjs[i].EnemyCourse = 1;
						//落下時間をリセット
						g_enemyObjs[i].EnemyFall = 0;
						g_enemyObjs[i].EnemyFallSpeed = 0;
						g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					}
				}
				else
				{
					g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
					g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
					if (g_enemyObjs[i].g_pEnemyFlySpeed_X < 1.0f)
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_X += 0.5f;
					}
					else
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_X = -0.5f;
					}
				}
			}
			break;
		}
	}
	//柱(右)
	for (int j = 0; j < (BlockBerPos[PhaseNum - 1].ConnectCount[0] + BlockBerPos[PhaseNum - 1].ConnectCount[1] + BlockBerPos[PhaseNum - 1].ConnectCount[2] + BlockBerPos[PhaseNum - 1].ConnectCount[3] + BlockBerPos[PhaseNum - 1].ConnectCount[4]); ++j)
	{
		//位置を当たり判定の外側にずらす
		if (Getg_pPicture->getPos().y - 16.0f > (g_pBlockBer[j]->getPos().y - (BlockBer.Size_Y / 2.0f) - (96.0f / 2.0f))
			&& Getg_pPicture->getPos().y < (g_pBlockBer[j]->getPos().y + (BlockBer.Size_Y / 2.0f) + (100.0f / 2.0f))
			&& Getg_pPicture->getPos().x >= (g_pBlockBer[j]->getPos().x + (BlockBer.Size_X / 2.0f))
			&& Getg_pPicture->collisionOffset(g_pBlockBer[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
			&& g_pBlockBer[j] != NULL)
		{
			//位置を当たり判定の外側にずらす
			Getg_pPicture->setPos(g_pBlockBer[j]->getPos().x + (BlockBer.Size_X / 2.0f) + (40.0f / 2.0f), Getg_pPicture->getPos().y);
			//プレイヤーの移動方向を反転
			if (Getg_pPicture == g_pPlayer[0])
			{
				//ぶつかった音
				// 作成されていなければ、作成
				if (!(g_pHit))
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pHit = createSound(Hit, false);
				}
				g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
				if (g_pPlayerFlySpeed > 1.0f)
				{
					g_pPlayerFlySpeed -= 0.5f;
				}
				else
				{
					g_pPlayerFlySpeed = 0.5f;
				}
			}
			if (Getg_pPicture == g_enemyObjs[i].obj)
			{
				//死亡時の落下中
				if (g_enemyObjs[i].EnemyStatus == 1)
				{
					//１の場合は２に
					if (g_enemyObjs[i].EnemyCourse == 1)
					{
						g_enemyObjs[i].EnemyCourse = 2;
						//落下時間をリセット
						g_enemyObjs[i].EnemyFall = 0;
						g_enemyObjs[i].EnemyFallSpeed = 0;
						g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					}
					//２の場合は１に
					else if (g_enemyObjs[i].EnemyCourse == 2)
					{
						g_enemyObjs[i].EnemyCourse = 1;
						//落下時間をリセット
						g_enemyObjs[i].EnemyFall = 0;
						g_enemyObjs[i].EnemyFallSpeed = 0;
						g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					}
				}
				else
				{
					g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
					g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
					if (g_enemyObjs[i].g_pEnemyFlySpeed_X > 1.0f)
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_X -= 0.5f;
					}
					else
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_X = 0.5f;
					}
				}
			}
			break;
		}
	}
	//柱(左)
	for (int j = 0; j < (BlockBerPos[PhaseNum - 1].ConnectCount[0] + BlockBerPos[PhaseNum - 1].ConnectCount[1] + BlockBerPos[PhaseNum - 1].ConnectCount[2] + BlockBerPos[PhaseNum - 1].ConnectCount[3] + BlockBerPos[PhaseNum - 1].ConnectCount[4]); ++j)
	{
		//位置を当たり判定の外側にずらす
		if (Getg_pPicture->getPos().y - 16.0f > (g_pBlockBer[j]->getPos().y - (BlockBer.Size_Y / 2.0f) - (96.0f / 2.0f))
			&& Getg_pPicture->getPos().y < (g_pBlockBer[j]->getPos().y + (BlockBer.Size_Y / 2.0f) + (100.0f / 2.0f))
			&& Getg_pPicture->getPos().x <= (g_pBlockBer[j]->getPos().x - (BlockBer.Size_X / 2.0f))
			&& Getg_pPicture->collisionOffset(g_pBlockBer[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
			&& g_pBlockBer[j] != NULL)
		{
			Getg_pPicture->setPos(g_pBlockBer[j]->getPos().x - (BlockBer.Size_X / 2.0f) - (40.0f / 2.0f), Getg_pPicture->getPos().y);
			//プレイヤーの移動方向を反転
			if (Getg_pPicture == g_pPlayer[0])
			{
				//ぶつかった音
				// 作成されていなければ、作成
				if (!(g_pHit))
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pHit = createSound(Hit, false);
				}
				g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
				if (g_pPlayerFlySpeed < -1.0f)
				{
					g_pPlayerFlySpeed += 0.5f;
				}
				else
				{
					g_pPlayerFlySpeed = -0.5f;
				}
			}
			if (Getg_pPicture == g_enemyObjs[i].obj)
			{
				//死亡時の落下中
				if (g_enemyObjs[i].EnemyStatus == 1)
				{
					//１の場合は２に
					if (g_enemyObjs[i].EnemyCourse == 1)
					{
						g_enemyObjs[i].EnemyCourse = 2;
						//落下時間をリセット
						g_enemyObjs[i].EnemyFall = 0;
						g_enemyObjs[i].EnemyFallSpeed = 0;
						g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					}
					//２の場合は１に
					else if (g_enemyObjs[i].EnemyCourse == 2)
					{
						g_enemyObjs[i].EnemyCourse = 1;
						//落下時間をリセット
						g_enemyObjs[i].EnemyFall = 0;
						g_enemyObjs[i].EnemyFallSpeed = 0;
						g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					}
				}
				else
				{
					g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
					g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
					if (g_enemyObjs[i].g_pEnemyFlySpeed_X < 1.0f)
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_X += 0.5f;
					}
					else
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_X = -0.5f;
					}
				}
			}
			break;
		}
	}

	//波(両端)
	//右端
	if (Getg_pPicture->getPos().y < (g_pEndWave[1]->getPos().y + (EndWave.Size_Y / 2.0f) + (100.0f / 2.0f))
		&& Getg_pPicture->getPos().x >= (g_pEndWave[1]->getPos().x + (EndWave.Size_X / 2.0f))
		&& Getg_pPicture->collisionOffset(g_pEndWave[1], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
		&& g_pEndWave[1] != NULL)
	{
		//位置を当たり判定の外側にずらす
		Getg_pPicture->setPos(g_pEndWave[1]->getPos().x + (EndWave.Size_X / 2.0f) + (40.0f / 2.0f), Getg_pPicture->getPos().y);
		//プレイヤーの移動方向を反転
		if (Getg_pPicture == g_pPlayer[0])
		{
			//ぶつかった音
			// 作成されていなければ、作成
			if (!(g_pHit))
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pHit = createSound(Hit, false);
			}
			g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
			if (g_pPlayerFlySpeed > 1.0f)
			{
				g_pPlayerFlySpeed -= 0.5f;
			}
			else
			{
				g_pPlayerFlySpeed = 0.5f;
			}
		}
		if (Getg_pPicture == g_enemyObjs[i].obj)
		{
			//死亡時の落下中
			if (g_enemyObjs[i].EnemyStatus == 1)
			{
				//１の場合は２に
				if (g_enemyObjs[i].EnemyCourse == 1)
				{
					g_enemyObjs[i].EnemyCourse = 2;
					//落下時間をリセット
					g_enemyObjs[i].EnemyFall = 0;
					g_enemyObjs[i].EnemyFallSpeed = 0;
					g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
				}
				//２の場合は１に
				else if (g_enemyObjs[i].EnemyCourse == 2)
				{
					g_enemyObjs[i].EnemyCourse = 1;
					//落下時間をリセット
					g_enemyObjs[i].EnemyFall = 0;
					g_enemyObjs[i].EnemyFallSpeed = 0;
					g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
				}
			}
			else
			{
				g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
				g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
				if (g_enemyObjs[i].g_pEnemyFlySpeed_X > 1.0f)
				{
					g_enemyObjs[i].g_pEnemyFlySpeed_X -= 0.5f;
				}
				else
				{
					g_enemyObjs[i].g_pEnemyFlySpeed_X = 0.5f;
				}
			}
		}
	}
	//左端
	if (Getg_pPicture->getPos().y < (g_pEndWave[2]->getPos().y + (EndWave.Size_Y / 2.0f) + (100.0f / 2.0f))
		&& Getg_pPicture->getPos().x <= (g_pEndWave[3]->getPos().x - (EndWave.Size_X / 2.0f))
		&& Getg_pPicture->collisionOffset(g_pEndWave[3], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
		&& g_pEndWave[3] != NULL)
	{
		//位置を当たり判定の外側にずらす
		Getg_pPicture->setPos(g_pEndWave[3]->getPos().x - (EndWave.Size_X / 2.0f) - (40.0f / 2.0f), Getg_pPicture->getPos().y);
		//プレイヤーの移動方向を反転
		if (Getg_pPicture == g_pPlayer[0])
		{
			//ぶつかった音
			// 作成されていなければ、作成
			if (!(g_pHit))
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pHit = createSound(Hit, false);
			}
			g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
			if (g_pPlayerFlySpeed < -1.0f)
			{
				g_pPlayerFlySpeed += 0.5f;
			}
			else
			{
				g_pPlayerFlySpeed = -0.5f;
			}
		}
		if (Getg_pPicture == g_enemyObjs[i].obj)
		{
			//死亡時の落下中
			if (g_enemyObjs[i].EnemyStatus == 1)
			{
				//１の場合は２に
				if (g_enemyObjs[i].EnemyCourse == 1)
				{
					g_enemyObjs[i].EnemyCourse = 2;
					//落下時間をリセット
					g_enemyObjs[i].EnemyFall = 0;
					g_enemyObjs[i].EnemyFallSpeed = 0;
					g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
				}
				//２の場合は１に
				else if (g_enemyObjs[i].EnemyCourse == 2)
				{
					g_enemyObjs[i].EnemyCourse = 1;
					//落下時間をリセット
					g_enemyObjs[i].EnemyFall = 0;
					g_enemyObjs[i].EnemyFallSpeed = 0;
					g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
					g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
				}
			}
			else
			{
				g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
				g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
				if (g_enemyObjs[i].g_pEnemyFlySpeed_X < 1.0f)
				{
					g_enemyObjs[i].g_pEnemyFlySpeed_X += 0.5f;
				}
				else
				{
					g_enemyObjs[i].g_pEnemyFlySpeed_X = -0.5f;
				}
			}
		}

	}
}

//当たり判定（上）
void CActionGameApp::OverCollision(CPicture* Getg_pPicture, int i)
{
	//浮島
	//中央
 	for (int j = 0; j < Block.Count; ++j)
	{

		if (Getg_pPicture->getPos().y - 16.0f < (g_pBlock[j]->getPos().y - (Block.Size_Y / 2.0f) - (100.0f / 2.0f) + 16.0f)
			&& Getg_pPicture->collisionOffset(g_pBlock[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
			&& g_pBlock[j] != NULL)
		{
			//位置を当たり判定の外側にずらす
			Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pBlock[j]->getPos().y - (Block.Size_Y / 2.0f) - (100.0f / 2.0f) + 16.0);
			//プレイヤーの移動方向を反転
			if (Getg_pPicture == g_pPlayer[0] && Gravity < 0.0f)
			{
				//ぶつかった音
				// 作成されていなければ、作成
				if (!(g_pHit))
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pHit = createSound(Hit, false);
				}
				Gravity = -(Gravity);
			}
			if (Getg_pPicture == g_enemyObjs[i].obj)
			{
				g_enemyObjs[i].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
				g_enemyObjs[i].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
			}
			break;
		}
	}
	//左端
	for (int j = 0; j < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++j)
	{
		if (Getg_pPicture->getPos().y - 16.0f < (g_pLeftBlock[j]->getPos().y - (LeftBlock.Size_Y / 2.0f) - (100.0f / 2.0f) + 16.0f)
			&& Getg_pPicture->collisionOffset(g_pLeftBlock[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
			&& g_pLeftBlock[j] != NULL)
		{
			//位置を当たり判定の外側にずらす
			Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pLeftBlock[j]->getPos().y - (LeftBlock.Size_Y / 2.0f) - (100.0f / 2.0f) + 16.0);
			//プレイヤーの移動方向を反転
			if (Getg_pPicture == g_pPlayer[0] && Gravity < 0.0f)
			{
				//ぶつかった音
				// 作成されていなければ、作成
				if (!(g_pHit))
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pHit = createSound(Hit, false);
				}
				Gravity = -(Gravity);
			}
			if (Getg_pPicture == g_enemyObjs[i].obj)
			{
				g_enemyObjs[i].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
				g_enemyObjs[i].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
			}
			break;
		}
	}
	//右端
	for (int j = 0; j < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++j)
	{
		if (Getg_pPicture->getPos().y - 16.0f < (g_pRightBlock[j]->getPos().y - (RightBlock.Size_Y / 2.0f) - (100.0f / 2.0f) + 16.0f)
			&& Getg_pPicture->collisionOffset(g_pRightBlock[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
			&& g_pBlock[j] != NULL)
		{
			//位置を当たり判定の外側にずらす
			Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pRightBlock[j]->getPos().y - (RightBlock.Size_Y / 2.0f) - (100.0f / 2.0f) + 16.0);
			//プレイヤーの移動方向を反転
			if (Getg_pPicture == g_pPlayer[0] && Gravity < 0.0f)
			{
				//ぶつかった音
				// 作成されていなければ、作成
				if (!(g_pHit))
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pHit = createSound(Hit, false);
				}
				Gravity = -(Gravity);
			}
			if (Getg_pPicture == g_enemyObjs[i].obj)
			{
				g_enemyObjs[i].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
				g_enemyObjs[i].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
			}
			break;
		}
	}

	//浮島
	//中央
	for (int j = 0; j < (BlockBerPos[PhaseNum - 1].ConnectCount[0] + BlockBerPos[PhaseNum - 1].ConnectCount[1] + BlockBerPos[PhaseNum - 1].ConnectCount[2] + BlockBerPos[PhaseNum - 1].ConnectCount[3] + BlockBerPos[PhaseNum - 1].ConnectCount[4]); ++j)
	{

		if (Getg_pPicture->getPos().y - 16.0f < (g_pBlockBer[j]->getPos().y - (Block.Size_Y / 2.0f) - (100.0f / 2.0f) + 16.0f)
			&& Getg_pPicture->collisionOffset(g_pBlockBer[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size)
			&& g_pBlockBer[j] != NULL)
		{
			//位置を当たり判定の外側にずらす
			Getg_pPicture->setPos(Getg_pPicture->getPos().x, g_pBlockBer[j]->getPos().y - (BlockBer.Size_Y / 2.0f) - (100.0f / 2.0f) + 16.0);
			//プレイヤーの移動方向を反転
			if (Getg_pPicture == g_pPlayer[0] && Gravity < 0.0f)
			{
				//ぶつかった音
				// 作成されていなければ、作成
				if (!(g_pHit))
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pHit = createSound(Hit, false);
				}
				Gravity = -(Gravity);
			}
			if (Getg_pPicture == g_enemyObjs[i].obj)
			{
				g_enemyObjs[i].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
				g_enemyObjs[i].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
			}
			break;
		}
	}

	//画面の上端
	if (Getg_pPicture->getPos().y - 16.0f >= WINDOW_TOP - (84.0f / 2.0f) - 16.0f)
	{
		//位置を当たり判定の外側にずらす
		Getg_pPicture->setPos(Getg_pPicture->getPos().x, WINDOW_TOP - (52.0f / 2.0f) - 16.0f);
		//プレイヤーの移動方向を反転
		if (Getg_pPicture == g_pPlayer[0] && Gravity < 0.0f)
		{
			//ぶつかった音
			// 作成されていなければ、作成
			if (!(g_pHit))
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pHit = createSound(Hit, false);
			}
			Gravity = -(Gravity);
		}
		if (Getg_pPicture == g_enemyObjs[i].obj)
		{
			g_enemyObjs[i].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
			g_enemyObjs[i].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
		}
	}
}

//エンティティ同士の当たり判定
void CActionGameApp::EntityCplision(CPicture* My, CPicture* Target,int i,int j)
{
	if (My->collisionOffset(Target, EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size) &&
		Target->collisionOffset(My, EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size))
	{
		//当たった相手がプレイヤーだった場合
		if (Target == g_pPlayer[j] )
		{
			//風船の当たり判定
			//主
			if (My->getPos().y - 6.0f < Target->getPos().y - 26.0f &&
				g_enemyObjs[i].EnemyStatus != 2 && g_enemyObjs[i].EnemyStatus != 3)
			{
				if (g_enemyObjs[i].EnemyStatus == 1)
				{
					//スコア加算
					ScoreSet(1 + (g_enemyObjs[i].EnemyLevel * 3));
					AddScoreSet(g_enemyObjs[i].obj, 1 + (g_enemyObjs[i].EnemyLevel * 3));

					g_enemyObjs[i].EnemyStatus = 4;
					g_pPlayer[j]->setPos(Target->getPos().x, Target->getPos().y + 4.0f);
					Gravity = -(Gravity / 1.5f);
					g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
					//エネミー死亡時
					// 作成されていなければ、作成
					if (g_pEnemyDeath)
					{
						disposeSound(g_pEnemyDeath);
						g_pEnemyDeath = NULL;
					}
					if (!g_pEnemyDeath)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pEnemyDeath = createSound(EnemyDeath, false);
					}
				}
				else
				{
					//スコア加算
					ScoreSet(0 + (g_enemyObjs[i].EnemyLevel * 3));
					AddScoreSet(g_enemyObjs[i].obj, 0 + (g_enemyObjs[i].EnemyLevel * 3));

					g_enemyObjs[i].EnemyStatus = 1;
					EnemyFallAnimFlag[i] = true;
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
				}
			}
			
			//相手（プレイヤー）
			if (Target->getPos().y - 6.0f < My->getPos().y - 26.0f &&
				g_enemyObjs[i].EnemyStatus == 0)
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
				if (BalloonCount > 1)
				{
					--BalloonCount;
				}
				else
				{
					DeathFlag = true;
				}
			}

			//上側の当たり判定
			if (My->getPos().y + 16.0f < Target->getPos().y - (PLAYER_SIZE_Y / 2.0f))
			{
				//主
				g_enemyObjs[i].obj->setPos(My->getPos().x, My->getPos().y - 4.0f);
				if (g_enemyObjs[i].enemyVer == 0)
				{
					//着陸時はエネミーの死亡処理
					if (g_enemyObjs[i].EnemyStatus == 2 || g_enemyObjs[i].EnemyStatus == 3)
					{
						//スコア加算
						ScoreSet(2 + (g_enemyObjs[i].EnemyLevel * 3));
						AddScoreSet(g_enemyObjs[i].obj, 2 + (g_enemyObjs[i].EnemyLevel * 3));

						g_enemyObjs[i].EnemyStatus = 4;
						//エネミー死亡時
						// 作成されていなければ、作成
						if (g_pEnemyDeath)
						{
							disposeSound(g_pEnemyDeath);
							g_pEnemyDeath = NULL;
						}
						if (!g_pEnemyDeath)
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pEnemyDeath = createSound(EnemyDeath, false);
						}
					}
					else
					{
						g_enemyObjs[i].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
						g_enemyObjs[i].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
					}
				}
				else
				{
					g_enemyObjs[i - 1].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
					g_enemyObjs[i - 1].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
				}
				if (g_enemyObjs[i].EnemyStatus != 4)
				{
					//相手
					g_pPlayer[j]->setPos(Target->getPos().x, Target->getPos().y + 4.0f);
					Gravity = -(Gravity / 1.5f);
				}
			}
			//下側の当たり判定
			else if (My->getPos().y - (PLAYER_SIZE_Y / 2.0f) > Target->getPos().y + 16.0f)
			{
				//主
				g_enemyObjs[i].obj->setPos(My->getPos().x, My->getPos().y + 4.0f);
				if (g_enemyObjs[i].enemyVer == 0)
				{
					//着陸時はエネミーの死亡処理
					if (g_enemyObjs[i].EnemyStatus == 2 || g_enemyObjs[i].EnemyStatus == 3)
					{
						//スコア加算
						ScoreSet(2 + (g_enemyObjs[i].EnemyLevel * 3));
						AddScoreSet(g_enemyObjs[i].obj, 2 + (g_enemyObjs[i].EnemyLevel * 3));

						g_enemyObjs[i].EnemyStatus = 4;
						//エネミー死亡時
						// 作成されていなければ、作成
						if (g_pEnemyDeath)
						{
							disposeSound(g_pEnemyDeath);
							g_pEnemyDeath = NULL;
						}
						if (!g_pEnemyDeath)
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pEnemyDeath = createSound(EnemyDeath, false);
						}
					}
					else
					{
						g_enemyObjs[i].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
						g_enemyObjs[i].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
					}
				}
				else
				{
					g_enemyObjs[i - 1].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
					g_enemyObjs[i - 1].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
				}
				
				if (g_enemyObjs[i].EnemyStatus != 4)
				{
					//相手
					g_pPlayer[j]->setPos(Target->getPos().x, Target->getPos().y - 4.0f);
					Gravity = -(Gravity / 1.5f);
				}
			}
			//右側の当たり判定
			if (My->getPos().x< Target->getPos().x - (PLAYER_SIZE_X / 2.0f))
			{
				//主
				g_enemyObjs[i].obj->setPos(My->getPos().x - 4.0f, My->getPos().y);
				if (g_enemyObjs[i].enemyVer == 0)
				{
					//着陸時はエネミーの死亡処理
					if (g_enemyObjs[i].EnemyStatus == 2 || g_enemyObjs[i].EnemyStatus == 3)
					{
						//スコア加算
						ScoreSet(2 + (g_enemyObjs[i].EnemyLevel * 3));
						AddScoreSet(g_enemyObjs[i].obj, 2 + (g_enemyObjs[i].EnemyLevel * 3));

						g_enemyObjs[i].EnemyStatus = 4;
						//エネミー死亡時
						// 作成されていなければ、作成
						if (g_pEnemyDeath)
						{
							disposeSound(g_pEnemyDeath);
							g_pEnemyDeath = NULL;
						}
						if (!g_pEnemyDeath)
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pEnemyDeath = createSound(EnemyDeath, false);
						}
					}
					//死亡時の落下中
					else if (g_enemyObjs[i].EnemyStatus == 1)
					{
						//１の場合は２に
						if (g_enemyObjs[i].EnemyCourse == 1)
						{
							g_enemyObjs[i].EnemyCourse = 2;
							//落下時間をリセット
							g_enemyObjs[i].EnemyFall = 0;
							g_enemyObjs[i].EnemyFallSpeed = 0;
							g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
						//２の場合は１に
						else if (g_enemyObjs[i].EnemyCourse == 2)
						{
							g_enemyObjs[i].EnemyCourse = 1;
							//落下時間をリセット
							g_enemyObjs[i].EnemyFall = 0;
							g_enemyObjs[i].EnemyFallSpeed = 0;
							g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
					}
					else
					{
						g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
						g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
					}
				}
				else
				{
					g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
					g_enemyObjs[i - 1].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
				}
				if (g_enemyObjs[i].EnemyStatus != 4)
				{
					//相手
					g_pPlayer[j]->setPos(Target->getPos().x + 4.0f, Target->getPos().y);
					g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
					g_playerMoveSpeed = -(g_playerMoveSpeed);
				}
			}
			//左側の当たり判定
			else if (My->getPos().x> Target->getPos().x + (PLAYER_SIZE_X / 2.0f))
			{
				//主
				g_enemyObjs[i].obj->setPos(My->getPos().x + 4.0f, My->getPos().y);
				if (g_enemyObjs[i].enemyVer == 0)
				{
					//着陸時はエネミーの死亡処理
					if (g_enemyObjs[i].EnemyStatus == 2 || g_enemyObjs[i].EnemyStatus == 3)
					{
						//スコア加算
						ScoreSet(2 + (g_enemyObjs[i].EnemyLevel * 3));
						AddScoreSet(g_enemyObjs[i].obj, 2 + (g_enemyObjs[i].EnemyLevel * 3));

						g_enemyObjs[i].EnemyStatus = 4;
						//エネミー死亡時
						// 作成されていなければ、作成
						if (g_pEnemyDeath)
						{
							disposeSound(g_pEnemyDeath);
							g_pEnemyDeath = NULL;
						}
						if (!g_pEnemyDeath)
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pEnemyDeath = createSound(EnemyDeath, false);
						}
					}
					//死亡時の落下中
					else if (g_enemyObjs[i].EnemyStatus == 1)
					{
						//１の場合は２に
						if (g_enemyObjs[i].EnemyCourse == 1)
						{
							g_enemyObjs[i].EnemyCourse = 2;
							//落下時間をリセット
							g_enemyObjs[i].EnemyFall = 0;
							g_enemyObjs[i].EnemyFallSpeed = 0;
							g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
						//２の場合は１に
						else if (g_enemyObjs[i].EnemyCourse == 2)
						{
							g_enemyObjs[i].EnemyCourse = 1;
							//落下時間をリセット
							g_enemyObjs[i].EnemyFall = 0;
							g_enemyObjs[i].EnemyFallSpeed = 0;
							g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
					}
					else
					{
						g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
						g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
					}
				}
				else
				{
					g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
					g_enemyObjs[i - 1].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
				}
				if (g_enemyObjs[i].EnemyStatus != 4)
				{
					//相手
					g_pPlayer[j]->setPos(Target->getPos().x - 4.0f, Target->getPos().y);
					g_pPlayerFlySpeed = -(g_pPlayerFlySpeed);
					g_playerMoveSpeed = -(g_playerMoveSpeed);
				}
			}
		}

		//当たった相手がエネミーだった場合
		else if (Target == g_enemyObjs[j].obj)
		{
			//上側の当たり判定
			if (My->getPos().y + 16.0f < Target->getPos().y - (PLAYER_SIZE_Y / 2.0f))
			{
				//主
				g_enemyObjs[i].obj->setPos(My->getPos().x, My->getPos().y - 4.0f);
				if (g_enemyObjs[i].enemyVer == 0)
				{
					g_enemyObjs[i].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
					g_enemyObjs[i].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
				}
				else
				{
					g_enemyObjs[i - 1].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
					g_enemyObjs[i - 1].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
				}
				//相手
				g_enemyObjs[j].obj->setPos(Target->getPos().x, Target->getPos().y + 4.0f);
				if (g_enemyObjs[j].enemyVer == 0)
				{
					g_enemyObjs[j].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
					g_enemyObjs[j].g_pEnemyFlySpeed_Y = -(g_enemyObjs[j].g_pEnemyFlySpeed_Y);
				}
				else
				{
					g_enemyObjs[j - 1].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
					g_enemyObjs[j - 1].g_pEnemyFlySpeed_Y = -(g_enemyObjs[j].g_pEnemyFlySpeed_Y);
				}
			}
			//下側の当たり判定
			else if (My->getPos().y - (PLAYER_SIZE_Y / 2.0f) > Target->getPos().y + 16.0f)
			{
				//主
				if (g_enemyObjs[i].enemyVer == 0)
				{
					g_enemyObjs[i].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
					g_enemyObjs[i].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
				}
				else
				{
					g_enemyObjs[i - 1].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
					g_enemyObjs[i - 1].g_pEnemyFlySpeed_Y = -(g_enemyObjs[i].g_pEnemyFlySpeed_Y);
				}
				g_enemyObjs[i].obj->setPos(My->getPos().x, My->getPos().y + 4.0f);
				//相手
				if (g_enemyObjs[j].enemyVer == 0)
				{
					g_enemyObjs[j].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
					g_enemyObjs[j].g_pEnemyFlySpeed_Y = -(g_enemyObjs[j].g_pEnemyFlySpeed_Y);
				}
				else
				{
					g_enemyObjs[j - 1].g_pEnemyMaxSpeed_Y = -(g_enemyObjs[i].g_pEnemyMaxSpeed_Y);
					g_enemyObjs[j - 1].g_pEnemyFlySpeed_Y = -(g_enemyObjs[j].g_pEnemyFlySpeed_Y);
				}
				g_enemyObjs[j].obj->setPos(Target->getPos().x, Target->getPos().y - 4.0f);
			}
			//右側の当たり判定
			if (My->getPos().x < Target->getPos().x - (PLAYER_SIZE_X / 2.0f))
			{
				//主
				g_enemyObjs[i].obj->setPos(My->getPos().x - 4.0f, My->getPos().y);
				if (g_enemyObjs[i].enemyVer == 0)
				{
					//死亡時の落下中
					if (g_enemyObjs[i].EnemyStatus == 1)
					{
						//１の場合は２に
						if (g_enemyObjs[i].EnemyCourse == 1)
						{
							g_enemyObjs[i].EnemyCourse = 2;
							//落下時間をリセット
							g_enemyObjs[i].EnemyFall = 0;
							g_enemyObjs[i].EnemyFallSpeed = 0;
							g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
						//２の場合は１に
						else if (g_enemyObjs[i].EnemyCourse == 2)
						{
							g_enemyObjs[i].EnemyCourse = 1;
							//落下時間をリセット
							g_enemyObjs[i].EnemyFall = 0;
							g_enemyObjs[i].EnemyFallSpeed = 0;
							g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
					}
					else
					{
						g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
						g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
					}
				}
				else
				{
					g_enemyObjs[i - 1].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
					g_enemyObjs[i - 1].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
				}
				//相手
				g_enemyObjs[j].obj->setPos(Target->getPos().x + 4.0f, Target->getPos().y);
				if (g_enemyObjs[j].enemyVer == 0)
				{
					//死亡時の落下中
					if (g_enemyObjs[j].EnemyStatus == 1)
					{
						//１の場合は２に
						if (g_enemyObjs[j].EnemyCourse == 1)
						{
							g_enemyObjs[j].EnemyCourse = 2;
							//落下時間をリセット
							g_enemyObjs[j].EnemyFall = 0;
							g_enemyObjs[j].EnemyFallSpeed = 0;
							g_enemyObjs[j].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[j + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
						//２の場合は１に
						else if (g_enemyObjs[j].EnemyCourse == 2)
						{
							g_enemyObjs[j].EnemyCourse = 1;
							//落下時間をリセット
							g_enemyObjs[j].EnemyFall = 0;
							g_enemyObjs[j].EnemyFallSpeed = 0;
							g_enemyObjs[j].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[j + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
					}
					else
					{
						g_enemyObjs[j].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
						g_enemyObjs[j].g_pEnemyFlySpeed_X = -(g_enemyObjs[j].g_pEnemyFlySpeed_X);
					}
				}
				else
				{
					g_enemyObjs[j - 1].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
					g_enemyObjs[j - 1].g_pEnemyFlySpeed_X = -(g_enemyObjs[j].g_pEnemyFlySpeed_X);
				}
			}
			//左側の当たり判定
			else if (My->getPos().x > Target->getPos().x + (PLAYER_SIZE_X / 2.0f))
			{
				//主
				if (g_enemyObjs[i].enemyVer == 0)
				{
					//死亡時の落下中
					if (g_enemyObjs[i].EnemyStatus == 1)
					{
						//１の場合は２に
						if (g_enemyObjs[i].EnemyCourse == 1)
						{
							g_enemyObjs[i].EnemyCourse = 2;
							//落下時間をリセット
							g_enemyObjs[i].EnemyFall = 0;
							g_enemyObjs[i].EnemyFallSpeed = 0;
							g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
						//２の場合は１に
						else if (g_enemyObjs[i].EnemyCourse == 2)
						{
							g_enemyObjs[i].EnemyCourse = 1;
							//落下時間をリセット
							g_enemyObjs[i].EnemyFall = 0;
							g_enemyObjs[i].EnemyFallSpeed = 0;
							g_enemyObjs[i].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[i + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
					}
					else
					{
						g_enemyObjs[i].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
						g_enemyObjs[i].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
					}
				}
				else
				{
					g_enemyObjs[i - 1].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
					g_enemyObjs[i - 1].g_pEnemyFlySpeed_X = -(g_enemyObjs[i].g_pEnemyFlySpeed_X);
				}
				g_enemyObjs[i].obj->setPos(My->getPos().x + 4.0f, My->getPos().y);
				//相手
				if (g_enemyObjs[j].enemyVer == 0)
				{
					//死亡時の落下中
					if (g_enemyObjs[j].EnemyStatus == 1)
					{
						//１の場合は２に
						if (g_enemyObjs[j].EnemyCourse == 1)
						{
							g_enemyObjs[j].EnemyCourse = 2;
							//落下時間をリセット
							g_enemyObjs[j].EnemyFall = 0;
							g_enemyObjs[j].EnemyFallSpeed = 0;
							g_enemyObjs[j].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[j + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
						//２の場合は１に
						else if (g_enemyObjs[j].EnemyCourse == 2)
						{
							g_enemyObjs[j].EnemyCourse = 1;
							//落下時間をリセット
							g_enemyObjs[j].EnemyFall = 0;
							g_enemyObjs[j].EnemyFallSpeed = 0;
							g_enemyObjs[j].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
							g_enemyObjs[j + 1].obj->addAngle(XMFLOAT3(0.0f, 180.0f, 0.0f));
						}
					}
					else
					{
						g_enemyObjs[j].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
						g_enemyObjs[j].g_pEnemyFlySpeed_X = -(g_enemyObjs[j].g_pEnemyFlySpeed_X);
					}
				}
				else
				{
					g_enemyObjs[j - 1].g_pEnemyMaxSpeed_X = -(g_enemyObjs[i].g_pEnemyMaxSpeed_X);
					g_enemyObjs[j - 1].g_pEnemyFlySpeed_X = -(g_enemyObjs[j].g_pEnemyFlySpeed_X);
				}
				g_enemyObjs[j].obj->setPos(Target->getPos().x - 4.0f, Target->getPos().y);
			}
		}
	}
}

//プレイヤーの当たり判定処理のまとめ
void CActionGameApp::PlayerCollision()
{
	for (int i = 0; i < 2; i++)
	{
		if (((g_pPlayer[i]->getPos().x < WINDOW_RIGHT && g_pPlayer[i]->getPos().x > WINDOW_LEFT) && g_pPlayer[i]->getPos().y > -200.0f) || g_pPlayer[i]->getPos().y <= -200.0f)
		{
			//画面下に出た時の判定
			if (g_pPlayer[i]->getPos().y <= -(WINDOW_WIDTH / 2.0f))
			{
				//水しぶきのアニメーション
				if (g_pPlayer[i]->getPos().x < WINDOW_RIGHT && g_pPlayer[i]->getPos().x > WINDOW_LEFT)
				{
					//水しぶきのアニメーション
					EnteringWaterCreate(g_pPlayer[i]);
					DeathStatusSet();
					if (g_pWater)
					{
						disposeSound(g_pWater);
						g_pWater = NULL;
					}
					if (g_pFall)
					{
						disposeSound(g_pFall);
						g_pFall = NULL;
					}
					// 作成されていなければ、作成
					if (!g_pWater)
					{
						// 第2引数：ループ設定
						// ループしないので、falseを設定
						g_pWater = createSound(Water, false);
					}
				}
			}
			
			PlayerLanding = false;
			//プレイヤーの対象物に対する当たり判定
			SideCollision(g_pPlayer[i], i);     //(側面)
			UnderCollision(g_pPlayer[i], XMFLOAT4(0.0f, BeforePlayerPos[i].y, 0.0f, 0.0f), i);    //(上)
			OverCollision(g_pPlayer[i], i);     //(下)

			//プレイヤーの最終位置を保存
			BeforePlayerPos[i].y = g_pPlayer[i]->getPos().y;
		}
	}
}


//エネミーの当たり判定処理のまとめ
void CActionGameApp::EnemyCollision()
{
	for (int i = 0; i < ENEMY_OBJECT_COUNT; i++)
	{
		if (((g_enemyObjs[i].enemyVer == 0 && g_enemyObjs[i].NowEdge != true) || g_enemyObjs[i].NowEdge == true) &&
			g_enemyObjs[i].obj != NULL && EnemyDeathFallFlag[i] != true && EnemyDeathFallFlag[i + 1] != true)
		{
			//画面下に出た時の判定
			if (g_enemyObjs[i].obj->getPos().y <= -(WINDOW_WIDTH / 2.0f))
			{
				if (g_pWater)
				{
					disposeSound(g_pWater);
					g_pWater = NULL;
				}
				// 作成されていなければ、作成
				if (!g_pWater)
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pWater = createSound(Water, false);
				}
				//水しぶきのアニメーション
				EnteringWaterCreate(g_enemyObjs[i].obj);
				EnteringWaterCreate(g_enemyObjs[i + 1].obj);

				BubbleCreate(g_enemyObjs[i].obj);
				BubbleCreate(g_enemyObjs[i + 1].obj);

				EnemyDeathFallFlag[i] = false;
				EnemyDeathFallFlag[i + 1] = false;
				EnemyDeathFallSpeed[i] = 3.0f;
				EnemyDeathFlag[i] = true;

				disposeSprite(g_enemyObjs[i].obj);
				g_enemyObjs[i].obj = NULL;

				disposeSprite(g_enemyObjs[i + 1].obj);
				g_enemyObjs[i + 1].obj = NULL;
				break;
			}

			//エンティティ同士の当たり判定
			if (g_pPlayer[0] != NULL && DeathFlag != true && DeathThunderFlag != true &&
				CollisionFlag == true && g_pPlayer[0]->getActive() == true && DeathCoolFlag != true)
			{
				EntityCplision(g_enemyObjs[i].obj, g_pPlayer[0], i, 0);
			}
			for (int j = i + 1; j < ENEMY_OBJECT_COUNT; ++j)
			{
				if (g_enemyObjs[j].obj != NULL &&
					g_enemyObjs[i].EnemyStatus != 2 && g_enemyObjs[j].EnemyStatus != 2 &&
					g_enemyObjs[i].EnemyStatus != 4 && g_enemyObjs[j].EnemyStatus != 4)
				{
					EntityCplision(g_enemyObjs[i].obj, g_enemyObjs[j].obj, i, j);
				}
			}

			//エネミーの対象物に対する当たり判定
			SideCollision(g_enemyObjs[i].obj, i);     //(側面)
			UnderCollision(g_enemyObjs[i].obj, XMFLOAT4(0.0f, BeforeEnemyPos[i].y, 0.0f, 0.0f), i);    //(上)
			OverCollision(g_enemyObjs[i].obj, i);     //(下)

			//Enemyの最終位置を保存
			BeforeEnemyPos[i].y = g_enemyObjs[i].obj->getPos().y;
		}
	}

	//エネミーのステータス変更
	procPlayMain_EnemyStatus();
	
	
}


//ボーナスステージの当たり判定
void CActionGameApp::BonusCollision()
{
	for (int i = 0; i < 2; i++)
	{
		PlayerLanding = false;
		//UnderCollision(g_pPlayer[i], XMFLOAT4(0.0f, BeforePlayerPos[i].y, 0.0f, 0.0f), i);    //(上)
		//OverCollision(g_pPlayer[i], i);     //(下)
		if (BeforePlayerPos[i].y >= g_pPlayer[i]->getPos().y)
		{
			//地面の当たり判定
			for (int j = 0; j < BGround.Count; ++j)
			{
				if (g_pBGround[j] != NULL)
				{
					if (g_pPlayer[i]->getPos().y > (g_pBGround[j]->getPos().y + (BGround.Size_Y / 2.0f) + (100.0f / 2.0f))
						&& g_pPlayer[i]->collisionOffset(g_pBGround[j], EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size))
					{
						//位置を当たり判定の外側にずらす
						g_pPlayer[i]->setPos(g_pPlayer[i]->getPos().x, g_pBGround[j]->getPos().y + (BGround.Size_Y / 2.0f) + PLAYER_SIZE_Y / 2.0f);
						//着陸状態にする
						PlayerLanding = true;
						break;
					}
				}
			}
		}
		if (g_pPlayer[i]->getPos().y - 16.0f >= WINDOW_TOP - (84.0f / 2.0f) - 16.0f)
		{
			//位置を当たり判定の外側にずらす
			g_pPlayer[i]->setPos(g_pPlayer[i]->getPos().x, WINDOW_TOP - (52.0f / 2.0f) - 16.0f);
			//プレイヤーの移動方向を反転
			if (Gravity < 0.0f)
			{
				//ぶつかった音
				// 作成されていなければ、作成
				if (!(g_pHit))
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pHit = createSound(Hit, false);
				}
				Gravity = -(Gravity);
			}
		}

		//重力を初期化
		if (PlayerLanding == true)
		{
			Gravity = 0.0f;
			//着陸した瞬間の横移動速度を維持
			if (g_pPlayerFlySpeed != 0.0f)
			{
				g_playerMoveSpeed = g_pPlayerFlySpeed;
				if (g_playerMoveSpeed > 0.0f)
				{
					WidthSwitch = true;
				}
				else if (g_playerMoveSpeed < 0.0f)
				{
					WidthSwitch = false;
				}
				g_pPlayerFlySpeed = 0.0f;
			}
		}
		//プレイヤーの最終位置を保存
		BeforePlayerPos[i].y = g_pPlayer[i]->getPos().y;
	}
}

void CActionGameApp::BBalloonCollision()
{
	for (int j = 0; j < 20; ++j)
	{
		if (g_pBalloon[j].Obj != NULL)
		{
			for (int i = 0; i < Pipe.Count; ++i)
			{
				if (g_pBalloon[j].Obj->collision(g_pPipe[i]))
				{
					g_pBalloon[j].inPipe = true;
					break;
				}
				else
				{
					g_pBalloon[j].inPipe = false;
				}
			}
			if (g_pBalloon[j].inPipe == false)
			{
				//50%で１，２を決める
						//１なら右方向、２なら左方向
				if (g_pBalloon[j].BalloonCourse == 3)
				{
					g_pBalloon[j].BalloonCourse = rand() % 2 + 1;
					//風船の移動量をランダムで決める
					g_pBalloon[j].BalloonMove = (float(rand() % 100 + 50) / 100.0f);
				}
			}
			for (int i = 0; i < 2; ++i)
			{
				//風船とプレイヤーが接触したとき
				if (g_pPlayer[i]->collisionOffset(g_pBalloon[j].Obj, EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size) && g_pBalloon[j].inPipe == false && g_pBalloon[j].HIt != true)
				{
					//接触したバルーンを破棄する
 					g_pBalloon[j].HIt = true;
					//割った風船の数を+1する
					BreakBallonCnt++;
					break;
				}
			}
		}

	}
}