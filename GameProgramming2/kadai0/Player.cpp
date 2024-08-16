//プレイヤーの処理
//21CU0207_海北
#include "CActionGameApp.h"
#include "GameResource.h"

//関数名		:procPlayMain_movePlayer()
//処理内容		:プレイヤーの移動処理
//引数			:なし
//戻り値		:なし
void CActionGameApp::procPlayMain_movePlayer()
{
	//死亡時以外
	if (DeathFlag != true && DeathThunderFlag != true)
	{
		//プレイヤーの移動
	/*for (int i = 0; i < 2; i++)
	{
		XMFLOAT4 pos = g_pPlayer[i]->getPos();
	}*/

		XMFLOAT4 pos0 = g_pPlayer[0]->getPos();
		XMFLOAT4 pos1 = g_pPlayer[1]->getPos();

		//プレイヤーが地面にいるときの横移動の処理
		if (PlayerLanding == true)
		{
			//右に移動する時
			if (m_pDirectInput->isKeyPressed(DIK_RIGHTARROW))
			{
				//段々と速度を上げる
				if (g_playerMoveSpeed <= 2.6f)
				{
					g_playerMoveSpeed += 0.1f;
				}
				pos0.x += g_playerMoveSpeed;
				pos1.x += g_playerMoveSpeed;

				MoveAnim = true;

				WidthSwitch = true;
				if (DeathCoolFlag == true)
				{
					DeathCoolFlag = false;
				}
			}

			//左に移動する時
			else if (m_pDirectInput->isKeyPressed(DIK_LEFTARROW))
			{
				//段々と速度を上げる
				if (g_playerMoveSpeed >= -2.6f)
				{
					g_playerMoveSpeed -= 0.1f;
				}
				pos0.x += g_playerMoveSpeed;
				pos1.x += g_playerMoveSpeed;

				MoveAnim = true;

				WidthSwitch = false;
				if (DeathCoolFlag == true)
				{
					DeathCoolFlag = false;
				}
			}



			//止まった時に徐々に
			else
			{

				//右移動している時
				if (WidthSwitch == true)
				{
					if (g_playerMoveSpeed > 0.0f)
					{
						g_playerMoveSpeed -= 0.1f;
						pos0.x += g_playerMoveSpeed;
						pos1.x += g_playerMoveSpeed;
						MoveAnim = false;
					}
					else
					{
						g_playerMoveSpeed = 0.0f;
					}
				}
				//左移動している時
				else if (WidthSwitch != true)
				{
					if (g_playerMoveSpeed < 0.0f)
					{
						g_playerMoveSpeed += 0.1f;
						pos0.x += g_playerMoveSpeed;
						pos1.x += g_playerMoveSpeed;

						MoveAnim = false;
					}
					else
					{
						g_playerMoveSpeed = 0.0f;
					}
				}
			}
			for (int i = 0; i < 2; i++)
			{
				g_pPlayer[i]->setPos(pos0);
			}

		}

		//重力を追加 空中にいる間は少しずつ速く落下するようにする
		if (PlayerLanding != true)
		{
			if (Gravity <= 4.0f)
			{
				Gravity += 0.03f;

				/*g_pJumpRise -= 0.1f;*/
			}
			pos0.y -= Gravity;
			pos1.y -= Gravity;
		}

		//スペースキーが押されたらジャンプする
		if (m_pDirectInput->isPressedOnce(DIK_SPACE))
		{
			if (g_pJumpRise <= g_pMaxRise)
			{
				g_pJumpPower += 0.002f;
				g_pJumpRise += g_pJumpPower;
			}

			if (Gravity > -3.0f)
			{
				Gravity -= 0.5f;

			}

			pos0.y += g_pJumpRise;
			pos1.y += g_pJumpRise;

			for (int i = 0; i < 2; i++)
			{
				g_pPlayer[i]->setPos(pos0);
			}

			if (JumpCount < 2)
			{
				++JumpCount;
			}
			if (DeathCoolFlag == true)
			{
				DeathCoolFlag = false;
			}
		}

		//空中での向いてる方向
		if (PlayerLanding == false)
		{
			//右に移動する時
			if (m_pDirectInput->isPressedOnce(DIK_RIGHTARROW))
			{
				WidthSwitch = true;
			}

			//左に移動する時
			else if (m_pDirectInput->isPressedOnce(DIK_LEFTARROW))
			{
				WidthSwitch = false;
			}
		}


		//空中移動
		if (PlayerLanding == false)
		{
			//着陸した瞬間の横移動速度を維持
			if (g_playerMoveSpeed != 0.0f)
			{
				g_pPlayerFlySpeed = g_playerMoveSpeed;
				g_playerMoveSpeed = 0.0f;
			}
			//右に移動する時
			if (m_pDirectInput->isPressedOnce(DIK_RIGHTARROW) && m_pDirectInput->isKeyPressed(DIK_SPACE)
				|| m_pDirectInput->isKeyTrigger(DIK_RIGHTARROW) && m_pDirectInput->isPressedOnce(DIK_SPACE))
			{
				//段々と速度を上げる
				if (g_pPlayerFlySpeed < 3.0f)
				{
					g_pPlayerFlySpeed += 0.5f;
				}
				else
				{
					g_pPlayerFlySpeed = 3.0f;
				}
				FlameCnt = 0;
			}

			//左に移動する時
			else if (m_pDirectInput->isPressedOnce(DIK_LEFTARROW) && m_pDirectInput->isKeyPressed(DIK_SPACE)
				|| m_pDirectInput->isKeyTrigger(DIK_LEFTARROW) && m_pDirectInput->isPressedOnce(DIK_SPACE))
			{
				//段々と速度を上げる
				if (g_pPlayerFlySpeed > -3.0f)
				{
					g_pPlayerFlySpeed -= 0.5f;
				}
				else
				{
					g_pPlayerFlySpeed = -3.0f;
				}
				FlameCnt = 0;
			}

			pos0.x += g_pPlayerFlySpeed;
			pos1.x += g_pPlayerFlySpeed;

			for (int i = 0; i < 2; i++)
			{
				g_pPlayer[i]->setPos(pos0);
			}
		}

		//操作がない場合、g_playerMoveSpeedを0に戻しておく
		if (PlayerLanding != true)
		{
			g_playerMoveSpeed = 0.0f;
		}




		//------------------------------------------------
		//プレイヤーの当たり判定の処理
		if (BonusON == true)
		{
			BonusCollision();
		}
		else
		{
			PlayerCollision();
		}

		//------------------------------------------------

	}
	//死亡時
	else if(DeathFlag == true)
	{
	//画面外に出るまで落下する
		if (g_pPlayer[0]->getPos().y < WINDOW_BOTTOM + 32.0f || g_pPlayer[1]->getPos().y < WINDOW_BOTTOM + 32.0f)
		{
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
				//水しぶきのアニメーション
				EnteringWaterCreate(g_pPlayer[0]);
				EnteringWaterCreate(g_pPlayer[1]);

				DeathStatusSet();
		}
		//最初に少し上昇
		else if (g_pPlayer[0]->getPos().y < BeforePlayerPos->y + 32.0f && DeathFallFlag != true)
		{
			// 作成されていなければ、作成
			if (!g_pFall)
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pFall = createSound(Fall, false);
			}
			g_playerMoveSpeed = 2.0f;
		}
		//上昇後下降
		else if (g_playerMoveSpeed >= -6.0f)
		{
			// 作成されていなければ、作成
			if (!g_pFall)
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pFall = createSound(Fall, false);
			}
			g_playerMoveSpeed -= 0.1f;
			DeathFallFlag = true;
		}
		g_pPlayer[0]->setPos(g_pPlayer[0]->getPos().x, g_pPlayer[0]->getPos().y + g_playerMoveSpeed);
		g_pPlayer[1]->setPos(g_pPlayer[0]->getPos().x, g_pPlayer[0]->getPos().y);
	}

	if (DeathCoolFlag != true)
	{
		//プレイヤーのアニメーション
		PlayerAnim();
	}
}

//関数名		:procPlayMain_BothEnds()
//処理内容		:画面端の処理
//引数			:なし
//戻り値		:なし
void CActionGameApp::procPlayMain_BothEnds()
{
	for (int i = 0; i < 2; i++)
	{
		//左端に行った時
		if (g_pPlayer[i]->getPos().x < -400.0f)
		{
			
			
			//プレイヤー０が画面端にいった時
			if (PlayerNum == 0)
			{
				g_pPlayer[1]->setPos(g_pPlayer[0]->getPos().x + 1024.0f, g_pPlayer[0]->getPos().y);
				//メインのプレイヤーは１になる
				PlayerNum = 1;
			}
			//プレイヤー１が画面端にいった時
			else if (PlayerNum == 1)
			{
				g_pPlayer[0]->setPos(g_pPlayer[1]->getPos().x + 1024.0f, g_pPlayer[0]->getPos().y);
				//メインのプレイヤーは１になる
				PlayerNum = 1;

			}
		}

		//右端に行った時
		if (g_pPlayer[i]->getPos().x > 400.0f)
		{
			
			//プレイヤー０が画面端にいった時
			if (PlayerNum == 0)
			{
				g_pPlayer[1]->setPos(g_pPlayer[0]->getPos().x - 1024.0f, g_pPlayer[0]->getPos().y);
				//メインのプレイヤーは１になる
				PlayerNum = 1;
			}
			//プレイヤー１が画面端にいった時
			else if (PlayerNum == 1)
			{
				g_pPlayer[0]->setPos(g_pPlayer[1]->getPos().x - 1024.0f, g_pPlayer[0]->getPos().y);
				//メインのプレイヤーは１になる
				PlayerNum = 1;

			}
		}
	}
	

	
}