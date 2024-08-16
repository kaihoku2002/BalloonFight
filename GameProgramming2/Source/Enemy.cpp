//----------------------------------------------
// ファイル名 ：Enemy.cpp
// 概要　　　 ：エネミーの生成・配置・描画・破棄・移動の処理
// 作者　　　 ：21CU0239 渡辺清太郎
// 更新内容     :2022/03/09/　エネミー画像の作成・エネミーの描画・エネミーの破棄
//------------------------------------------------

#include "CActionGameApp.h"
#include "GameResource.h"
#include <math.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


//関数名		　 :procPlayMain_EnemyCreate()
//処理内容		:エネミーの作成
//引数			:なし
//戻り値		    :なし
void CActionGameApp::procPlayMain_EnemyCreate()
{
	for (int i = 0; i < iEnemyCount[PhaseNum - 1]; ++i)
	{
		g_enemyObjs[i].beginPos = EnemybeginPos[PhaseNum - 1][i];
		g_enemyObjs[i].EnemyLevel = iEnemyLevel[PhaseNum - 1][i];
	}

	//敵の画像を作成する
	for (int i = 0; i < iEnemyCount[PhaseNum - 1]; ++i)
	{
		//それぞれの　obj　が　NULLの時のみ画像を作成する
		if (g_enemyObjs[i].obj == NULL)
		{
			//敵の画像を作成する
			g_enemyObjs[i].obj = createSprite(Tex_Enemy1, ENEMY_SIZE_X, ENEMY_SIZE_Y);
		}
	}
	//敵の画像を配置する
	for (int i = 0; i < iEnemyCount[PhaseNum - 1]; ++i)
	{
		//g_enemyObjs[i].obj が作成されている場合のみ作成する
		if (g_enemyObjs[i].obj != NULL)
		{
			//敵の画像を配置する
			g_enemyObjs[i].obj->setPos(g_enemyObjs[i].beginPos);
			g_enemyObjs[i].obj->setAnimation(0 + (g_enemyObjs[i].EnemyLevel * 18));
			g_enemyObjs[i].obj->setAngle(0.0f, 0.0f, 0.0f);
		}
	}
}


//関数名		:procPlayMain_EnemyBothEnd()
//処理内容		:画面端の処理
//引数			:なし
//戻り値		:なし
void CActionGameApp::procPlayMain_EnemyBothEnd()
{
	//エネミーが画面端を超えたら反対側の画面端に描画する
	//左端に行ったとき
	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
	{
		//enemyVerが0の時
		if (g_enemyObjs[i].enemyVer == 0 && g_enemyObjs[i].obj != NULL)
		{
			//左端に行ったとき
			if (g_enemyObjs[i].obj->getPos().x < WINDOW_LEFT + (ENEMY_SIZE_X / 2.0f))
			{
				//座標を調整
				g_enemyObjs[i + 1].obj->setPos(g_enemyObjs[i].obj->getPos().x + WINDOW_WIDTH, g_enemyObjs[i].obj->getPos().y);
				//画面外に完全に出た場合
				if (g_enemyObjs[i].obj->getPos().x < WINDOW_LEFT - (ENEMY_SIZE_X / 2.0f))
				{
					g_enemyObjs[i].obj->setPos(g_enemyObjs[i + 1].obj->getPos().x, g_enemyObjs[i + 1].obj->getPos().y);
					g_enemyObjs[i + 1].NowEdge = false;
				}
			}
			//右端に行ったとき
			else if (g_enemyObjs[i].obj->getPos().x > WINDOW_RIGHT - (ENEMY_SIZE_X / 2.0f))
			{
				//座標を調整
				g_enemyObjs[i + 1].obj->setPos(g_enemyObjs[i].obj->getPos().x - WINDOW_WIDTH, g_enemyObjs[i].obj->getPos().y);
				g_enemyObjs[i + 1].NowEdge = true;
				//画面外に完全に出た場合
				if (g_enemyObjs[i].obj->getPos().x > WINDOW_RIGHT + (ENEMY_SIZE_X / 2.0f))
				{
					g_enemyObjs[i].obj->setPos(g_enemyObjs[i + 1].obj->getPos().x, g_enemyObjs[i + 1].obj->getPos().y);
					g_enemyObjs[i + 1].NowEdge = false;
				}
			}
			else
			{
				g_enemyObjs[i + 1].obj->setPos(g_enemyObjs[i].obj->getPos().x, g_enemyObjs[i].obj->getPos().y);
				g_enemyObjs[i + 1].NowEdge = false;
			}
		}
	}
	
}


//関数名		:procPlayMain_procEnemy()
//処理内容		:エネミーのメイン処理
//引数			:なし
//戻り値		    :なし
void CActionGameApp::procPlayMain_procEnemy()
{


	//乱数表の基準値を設定
	srand((unsigned)time(NULL));


	//敵の処理
	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
	{
		//敵画像が作成されていたら処理を行う
		if (g_enemyObjs[i].obj != NULL && g_enemyObjs[i].EnemyStatus != 4)
		{
			//描画する
			renderSprite(g_enemyObjs[i].obj);

			if (g_enemyObjs[i].EnemyStatus == 0 &&
				EnemyDeathFallFlag[i] != true &&
				EnemyDeathFallFlag[i + 1] != true)
			{

				//カウンタを起動
				g_enemyObjs[i].flameCnt[0] += 1;
				g_enemyObjs[i].flameCnt[1] += 1;

				//エネミーの座標
				g_enemyObjs[i].enemyPos = g_enemyObjs[i].obj->getPos();
				//プレイヤーの座標
				XMFLOAT4 Playerpos = g_pPlayer[0]->getPos();

				//現在のエネミーの座標によってEnemyAreaの値を変える
				//左上
				if (g_enemyObjs[i].enemyPos.x < AreaLineLeft && g_enemyObjs[i].enemyPos.x > WINDOW_LEFT && g_enemyObjs[i].enemyPos.y > AreaLineOver)
				{
					g_enemyObjs[i].EnemyArea = 0;
				}
				//中央上
				else if (g_enemyObjs[i].enemyPos.x > AreaLineLeft && g_enemyObjs[i].enemyPos.x < AreaLineRight && g_enemyObjs[i].enemyPos.y > AreaLineOver)
				{
					g_enemyObjs[i].EnemyArea = 1;
				}
				//右上
				else if (g_enemyObjs[i].enemyPos.x < WINDOW_RIGHT && g_enemyObjs[i].enemyPos.x > AreaLineRight && g_enemyObjs[i].enemyPos.y > AreaLineOver)
				{
					g_enemyObjs[i].EnemyArea = 2;
				}
				//左
				if (g_enemyObjs[i].enemyPos.x < AreaLineLeft && g_enemyObjs[i].enemyPos.x > WINDOW_LEFT &&
					g_enemyObjs[i].enemyPos.y < AreaLineOver && g_enemyObjs[i].enemyPos.y > AreaLineUnder)
				{
					g_enemyObjs[i].EnemyArea = 3;
				}
				//中央
				else if (g_enemyObjs[i].enemyPos.x > AreaLineLeft && g_enemyObjs[i].enemyPos.x < AreaLineRight &&
					g_enemyObjs[i].enemyPos.y < AreaLineOver && g_enemyObjs[i].enemyPos.y > AreaLineUnder)
				{
					g_enemyObjs[i].EnemyArea = 4;
				}
				//右
				else if (g_enemyObjs[i].enemyPos.x < WINDOW_RIGHT && g_enemyObjs[i].enemyPos.x > AreaLineRight &&
					g_enemyObjs[i].enemyPos.y < AreaLineOver && g_enemyObjs[i].enemyPos.y > AreaLineUnder)
				{
					g_enemyObjs[i].EnemyArea = 5;
				}
				//左下
				else if (g_enemyObjs[i].enemyPos.x < AreaLineLeft && g_enemyObjs[i].enemyPos.x > WINDOW_LEFT && g_enemyObjs[i].enemyPos.y < AreaLineUnder)
				{
					g_enemyObjs[i].EnemyArea = 6;
				}
				//中央下
				else if (g_enemyObjs[i].enemyPos.x > AreaLineLeft && g_enemyObjs[i].enemyPos.x < AreaLineRight && g_enemyObjs[i].enemyPos.y < AreaLineUnder)
				{
					g_enemyObjs[i].EnemyArea = 7;
				}
				//右下
				else if (g_enemyObjs[i].enemyPos.x < WINDOW_RIGHT && g_enemyObjs[i].enemyPos.x > AreaLineRight && g_enemyObjs[i].enemyPos.y < AreaLineUnder)
				{
					g_enemyObjs[i].EnemyArea = 8;
				}

				//段々と速度を上げる
				//x軸の移動
				//g_pEnemyMaxSpeed_Xがプラスの場合
				if (g_enemyObjs[i].g_pEnemyMaxSpeed_X >= 0.1)
				{
					if (g_enemyObjs[i].g_pEnemyFlySpeed_X < g_enemyObjs[i].g_pEnemyMaxSpeed_X)
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_X += 0.1;
					}
				}
				//g_pEnemyMaxSpeed_Xがマイナスの場合
				else if (g_enemyObjs[i].g_pEnemyMaxSpeed_X <= -0.1)
				{
					if (g_enemyObjs[i].g_pEnemyFlySpeed_X > g_enemyObjs[i].g_pEnemyMaxSpeed_X)
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_X -= 0.1;
					}
				}
				//y軸の移動
				//g_pEnemyMaxSpeed_Yがプラスの場合
				if (g_enemyObjs[i].g_pEnemyMaxSpeed_Y >= 0.1)
				{
					if (g_enemyObjs[i].g_pEnemyFlySpeed_Y < g_enemyObjs[i].g_pEnemyMaxSpeed_Y)
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_Y += 0.1;
					}
				}
				//g_pEnemyMaxSpeed_Yがマイナスの場合
				else if (g_enemyObjs[i].g_pEnemyMaxSpeed_Y <= -0.1)
				{
					if (g_enemyObjs[i].g_pEnemyFlySpeed_Y > g_enemyObjs[i].g_pEnemyMaxSpeed_Y)
					{
						g_enemyObjs[i].g_pEnemyFlySpeed_Y -= 0.1;
					}
				}


				//一定フレームを超えたら向かう座標を再取得する
				if (g_enemyObjs[i].obj->collision(g_enemyObjs[i].DirectionPos,64.0f) || g_enemyObjs[i].flameCnt[1] >= (rand() % 100) + 360)
				{
					//乱数を所得
					g_enemyObjs[i].pattern = rand() % 10;
					//エネミーの現在のエリアに応じて、ランダムに座標を取得する
					//左上
					if (g_enemyObjs[i].EnemyArea == 0)
					{
						//中央上に移動
						if (g_enemyObjs[i].pattern > 4)
						{
							g_enemyObjs[i].DirectionPos.x = 0.0f;
							g_enemyObjs[i].DirectionPos.y = 400.0f;
						}
						//左に移動
						else if (g_enemyObjs[i].pattern > 8)
						{
							g_enemyObjs[i].DirectionPos.x = -400.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
						//中央に移動
						else
						{
							g_enemyObjs[i].DirectionPos.x = 0.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
					}
					//中央上
					else if (g_enemyObjs[i].EnemyArea == 1)
					{
						//左上に移動
						if (g_enemyObjs[i].pattern > 4)
						{
							g_enemyObjs[i].DirectionPos.x = -400.0f;
							g_enemyObjs[i].DirectionPos.y = 400.0f;
						}
						//右上に移動
						else if (g_enemyObjs[i].pattern > 8)
						{
							g_enemyObjs[i].DirectionPos.x = 400.0f;
							g_enemyObjs[i].DirectionPos.y = 400.0f;
						}
						//中央に移動
						else
						{
							g_enemyObjs[i].DirectionPos.x = 0.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}

					}
					//右上
					else if (g_enemyObjs[i].EnemyArea == 2)
					{
						//中央上に移動
						if (g_enemyObjs[i].pattern < 4)
						{
							g_enemyObjs[i].DirectionPos.x = 0.0f;
							g_enemyObjs[i].DirectionPos.y = 400.0f;
						}
						//右に移動
						else if (g_enemyObjs[i].pattern < 8)
						{
							g_enemyObjs[i].DirectionPos.x = 400.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
						//中央に移動
						else
						{
							g_enemyObjs[i].DirectionPos.x = 0.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
					}
					//左
					if (g_enemyObjs[i].EnemyArea == 3)
					{
						//左上に移動
						if (g_enemyObjs[i].pattern < 4)
						{
							g_enemyObjs[i].DirectionPos.x = -400.0f;
							g_enemyObjs[i].DirectionPos.y = 400.0f;
						}
						//左下に移動
						else if (g_enemyObjs[i].pattern < 8)
						{
							g_enemyObjs[i].DirectionPos.x = -400.0f;
							g_enemyObjs[i].DirectionPos.y = -200.0f;
						}
						//中央に移動
						else
						{
							g_enemyObjs[i].DirectionPos.x = 0.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
					}
					//中央
					else if (g_enemyObjs[i].EnemyArea == 4)
					{
						//中央上に移動
						if (g_enemyObjs[i].pattern < 2)
						{
							g_enemyObjs[i].DirectionPos.x = 400.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
						//左上に移動
						else if (g_enemyObjs[i].pattern < 5)
						{
							g_enemyObjs[i].DirectionPos.x = -400.0f;
							g_enemyObjs[i].DirectionPos.y = 400.0f;
						}
						//右上に移動
						else if (g_enemyObjs[i].pattern < 8)
						{
							g_enemyObjs[i].DirectionPos.x = 400.0f;
							g_enemyObjs[i].DirectionPos.y = 400.0f;
						}
						//右に移動
						else if (g_enemyObjs[i].pattern < 9)
						{
							g_enemyObjs[i].DirectionPos.x = 400.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
						//左に移動
						else
						{
							g_enemyObjs[i].DirectionPos.x = -400.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
					}
					//右
					else if (g_enemyObjs[i].EnemyArea == 5)
					{
						//右上に移動
						if (g_enemyObjs[i].pattern < 4)
						{
							g_enemyObjs[i].DirectionPos.x = 400.0f;
							g_enemyObjs[i].DirectionPos.y = 400.0f;
						}
						//右下に移動
						if (g_enemyObjs[i].pattern < 8)
						{
							g_enemyObjs[i].DirectionPos.x = 400.0f;
							g_enemyObjs[i].DirectionPos.y = -200.0f;
						}
						//中央に移動
						else
						{
							g_enemyObjs[i].DirectionPos.x = 0.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
					}
					//左下
					if (g_enemyObjs[i].EnemyArea == 6)
					{
						//左に移動
						if (g_enemyObjs[i].pattern < 8)
						{
							g_enemyObjs[i].DirectionPos.x = -400.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
						//中央下に移動
						else
						{
							g_enemyObjs[i].DirectionPos.x = 0.0f;
							g_enemyObjs[i].DirectionPos.y = -200.0f;
						}
					}
					//中央下
					else if (g_enemyObjs[i].EnemyArea == 7)
					{
						//右下に移動
						if (g_enemyObjs[i].pattern < 5)
						{
							g_enemyObjs[i].DirectionPos.x = 400.0f;
							g_enemyObjs[i].DirectionPos.y = -200.0f;
						}
						//左下に移動
						else
						{
							g_enemyObjs[i].DirectionPos.x = -400.0f;
							g_enemyObjs[i].DirectionPos.y = -200.0f;
						}
					}
					//右下
					else if (g_enemyObjs[i].EnemyArea == 8)
					{
						//右に移動
						if (g_enemyObjs[i].pattern < 8)
						{
							g_enemyObjs[i].DirectionPos.x = 400.0f;
							g_enemyObjs[i].DirectionPos.y = 100.0f;
						}
						//中央下に移動
						else
						{
							g_enemyObjs[i].DirectionPos.x = 0.0f;
							g_enemyObjs[i].DirectionPos.y = -200.0f;
						}
					}
					g_enemyObjs[i].flameCnt[1] = 0;
				}

				if ((g_enemyObjs[i].flameCnt[0] >= (rand() % 40) + 120) || g_enemyObjs[i].enemyPos.y < EnemyNotInWater)
				{

					//	エネミーと向かう点の距離を計測
					g_enemyObjs[i].PlayerDistance.x = g_enemyObjs[i].DirectionPos.x - g_enemyObjs[i].enemyPos.x;
					g_enemyObjs[i].PlayerDistance.y = g_enemyObjs[i].DirectionPos.y - g_enemyObjs[i].enemyPos.y;

					//エネミーと向かう点を繋ぐ直線を求める
					g_enemyObjs[i].g_pEnemyMoveLine = sqrt((g_enemyObjs[i].PlayerDistance.x * g_enemyObjs[i].PlayerDistance.x) + (g_enemyObjs[i].PlayerDistance.y * g_enemyObjs[i].PlayerDistance.y));
					//プレイヤーとエネミーを繋ぐ直線を求める
					g_enemyObjs[i].g_pPlayerEnemyLine = sqrt(((Playerpos.x - g_enemyObjs[i].enemyPos.x) * (Playerpos.x - g_enemyObjs[i].enemyPos.x)) + ((Playerpos.y - g_enemyObjs[i].enemyPos.y) * (Playerpos.y - g_enemyObjs[i].enemyPos.y)));

					//乱数を所得
					g_enemyObjs[i].pattern = rand() % 10;
					//エネミーとプレイヤーの距離が一定以下ならプレイヤーの座標を取得し、追従する
					if (g_enemyObjs[i].g_pPlayerEnemyLine <= 300.0f && g_enemyObjs[i].pattern < 3 &&
						(PlayerLanding == true && g_pPlayer[0]->getPos().y > g_enemyObjs[i].obj->getPos().y) != true)
					{
						g_enemyObjs[i].g_pEnemyMaxSpeed_X = (Playerpos.x - g_enemyObjs[i].enemyPos.x) / g_enemyObjs[i].g_pPlayerEnemyLine * g_enemyObjs[i].SpeedMagnification;
						g_enemyObjs[i].g_pEnemyMaxSpeed_Y = (Playerpos.y - g_enemyObjs[i].enemyPos.y) / g_enemyObjs[i].g_pPlayerEnemyLine * g_enemyObjs[i].SpeedMagnification;
					}
					//それ以外の場合は向かう点に向けて速度を取得
					else
					{
						g_enemyObjs[i].g_pEnemyMaxSpeed_X = (g_enemyObjs[i].PlayerDistance.x / g_enemyObjs[i].g_pEnemyMoveLine * g_enemyObjs[i].SpeedMagnification);
						g_enemyObjs[i].g_pEnemyMaxSpeed_Y = (g_enemyObjs[i].PlayerDistance.y / g_enemyObjs[i].g_pEnemyMoveLine * g_enemyObjs[i].SpeedMagnification);
					}

					g_enemyObjs[i].flameCnt[0] = 0;

				}

				//移動
				g_enemyObjs[i].enemyPos.x += g_enemyObjs[i].g_pEnemyFlySpeed_X;
				g_enemyObjs[i].enemyPos.y += g_enemyObjs[i].g_pEnemyFlySpeed_Y;
				g_enemyObjs[i].obj->setPos(g_enemyObjs[i].enemyPos);

				//エネミーのレベルによってエネミーのスピードを調整する値を上昇させる
				if (g_enemyObjs[i].EnemyLevel == 1)
				{
					g_enemyObjs[i].SpeedMagnification = 2.5;
				}
				else if (g_enemyObjs[i].EnemyLevel == 2)
				{
					g_enemyObjs[i].SpeedMagnification = 4.5;
				}

				//デバッグ用
				if (m_pDirectInput->isKeyPressed(DIK_1))
				{
					g_enemyObjs[i].EnemyLevel = 1;
				}
				if (m_pDirectInput->isKeyPressed(DIK_2))
				{
					g_enemyObjs[i].EnemyLevel = 2;
				}
			}

		}
	}
	//エネミーの当たり判定
	EnemyCollision();

	//エネミーの画面端処理
	procPlayMain_EnemyBothEnd();

	//アニメーション
	EnemyAnim();

}

//関数名		　 :procPlayMain_EnemyDispose()
//処理内容		:エネミーの破棄
//引数			:なし
//戻り値		    :なし
void CActionGameApp::procPlayMain_EnemyDispose()
{
	//敵画像を破棄する
	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
	{
		//それぞれの obj が作成されている場合のみ破棄する
		if (g_enemyObjs[i].obj != NULL)
		{
			disposeSprite(g_enemyObjs[i].obj);
			g_enemyObjs[i].obj = NULL;
		}
	}
}

void CActionGameApp::procPlayMain_EnemyStatus()//エネミーのステータス
{
	//敵の処理
	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
	{

		//敵画像が作成されていたら処理を行う
		if (g_enemyObjs[i].obj != NULL)
		{

			//エネミーが落下中のステータスの時の挙動
			if (g_enemyObjs[i].EnemyStatus == 1)
			{

				//50%で１，２を決める
				//１なら右方向、２なら左方向
				if (g_enemyObjs[i].EnemyCourse == 3)
				{
					g_enemyObjs[i].EnemyCourse = rand() % 2 + 1;

				}
				//エネミーの落下方向はランダムで決まる
				//１なら右方向
				if (g_enemyObjs[i].EnemyCourse == 1)
				{
					g_enemyObjs[i].obj->setPos(g_enemyObjs[i].obj->getPos().x + g_enemyObjs[i].EnemyFallSpeed, g_enemyObjs[i].obj->getPos().y - 1.0f);


					//落下の時間を増やしておく
					++g_enemyObjs[i].EnemyFall;
				}

				//エネミーの落下方向はランダムで決まる
				//２なら左方向
				else if (g_enemyObjs[i].EnemyCourse == 2)
				{
					g_enemyObjs[i].obj->setPos(g_enemyObjs[i].obj->getPos().x - g_enemyObjs[i].EnemyFallSpeed, g_enemyObjs[i].obj->getPos().y - 1.0f);
					//落下の時間を増やしておく
					++g_enemyObjs[i].EnemyFall;
				}

				//落下時間が一定数を超えたときに、落下の方向を変える
				if (g_enemyObjs[i].EnemyFall > EnemyFallTime)
				{
					//１の場合は２に
					if (g_enemyObjs[i].EnemyCourse == 1)
					{
						g_enemyObjs[i].EnemyCourse = 2;
						//落下時間をリセット
						g_enemyObjs[i].EnemyFall = 0;
					}
					//２の場合は１に
					else if (g_enemyObjs[i].EnemyCourse == 2)
					{
						g_enemyObjs[i].EnemyCourse = 1;
						//落下時間をリセット
						g_enemyObjs[i].EnemyFall = 0;
					}
				}

				//落下速度（X軸を加速させる）
				//初速から最高速度（中間）までは加速する
				if (g_enemyObjs[i].EnemyFall <= EnemyFallTime / 2)
				{
					g_enemyObjs[i].EnemyFallSpeed += 0.07f;
				}

				else if (g_enemyObjs[i].EnemyFall > EnemyFallTime / 2)
				{
					g_enemyObjs[i].EnemyFallSpeed -= 0.07f;
				}



			}

			//エネミーが着地したときのステータス
			else if (g_enemyObjs[i].EnemyStatus == 2)
			{
				if (g_enemyObjs[i].EnemyReturn_Num > rand() % 7 + 4)
				{
					BalloonReloadFlag[i] = true;
				}
				else if (BalloonReloadFlag[i] != true)
				{
					//乱数で感覚を開けてふうせんを膨らませて復活する
					g_enemyObjs[i].EnemyReturn_Num += 0.01666;

					g_enemyObjs[i].obj->setAnimation(0 + (g_enemyObjs[i].EnemyLevel * 18));
					g_enemyObjs[i + 1].obj->setAnimation(0 + (g_enemyObjs[i].EnemyLevel * 18));
				}
				
			}

			//ゲームが始まって最初に風船をいれる時なので、復活の速さが一定になるようにする
			else if (g_enemyObjs[i].EnemyStatus == 3)
			{
				if (BalloonReloadFlag[i] == false)
				{
					g_enemyObjs[i].EnemyStatus = 0;

					//復活したので値をリセット
					g_enemyObjs[i].EnemyReturn_Num = 0.0;
				}
			}

			else if (g_enemyObjs[i].EnemyStatus == 4)
			{
				//それぞれの obj が作成されている場合のみ破棄する
				if (g_enemyObjs[i].obj != NULL)
				{
					if (EnemyDeathFlag[i] == true)
					{
						disposeSprite(g_enemyObjs[i].obj);
						g_enemyObjs[i].obj = NULL;

						disposeSprite(g_enemyObjs[i + 1].obj);
						g_enemyObjs[i + 1].obj = NULL;
						EnemyDeathFlag[i] = false;
					}
					else
					{
						//画面外に出るまで落下する
						if (g_enemyObjs[i].obj->getPos().y < WINDOW_BOTTOM + 32.0f || g_enemyObjs[i + 1].obj->getPos().y < WINDOW_BOTTOM + 32.0f)
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
							//泡
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
						}
						//最初に少し上昇
						else if (EnemyDeathFallSpeed[i] > -8.0f)
						{
							g_enemyObjs[i].obj->setPos(g_enemyObjs[i].obj->getPos().x, g_enemyObjs[i].obj->getPos().y + (EnemyDeathFallSpeed[i] -= 0.2f));
							g_enemyObjs[i + 1].obj->setPos(g_enemyObjs[i].obj->getPos().x, g_enemyObjs[i].obj->getPos().y);
							EnemyDeathFallFlag[i] = true;
							EnemyDeathFallFlag[i + 1] = true;
							if (EnemyDeathFallSpeed[i] > 0.0f)
							{
								//アニメーション
								g_enemyObjs[i].obj->setAnimation(13 + (g_enemyObjs[i].EnemyLevel * 18));
								g_enemyObjs[i + 1].obj->setAnimation(13 + (g_enemyObjs[i].EnemyLevel * 18));
							}
							else
							{
								++AnimCount[AnimCountEnemy + i];
								if (AnimCount[AnimCountEnemy + i] % 7 != 0)
								{
									if (AnimCount[AnimCountEnemy + i] < 4)
									{
										g_enemyObjs[i].obj->setAnimation(13 + (g_enemyObjs[i].EnemyLevel * 18));
										g_enemyObjs[i + 1].obj->setAnimation(13 + (g_enemyObjs[i].EnemyLevel * 18));
									}
									else if (AnimCount[AnimCountEnemy + i] < 7)
									{
										g_enemyObjs[i].obj->setAnimation(14 + (g_enemyObjs[i].EnemyLevel * 18));
										g_enemyObjs[i + 1].obj->setAnimation(14 + (g_enemyObjs[i].EnemyLevel * 18));
									}
								}
								else
								{
									AnimCount[AnimCountEnemy + i] = 0;
								}
							}
						}
						//上昇後下降
						else
						{
							g_enemyObjs[i].obj->setPos(g_enemyObjs[i].obj->getPos().x, g_enemyObjs[i].obj->getPos().y + EnemyDeathFallSpeed[i]);
							g_enemyObjs[i + 1].obj->setPos(g_enemyObjs[i].obj->getPos().x, g_enemyObjs[i].obj->getPos().y);
							++AnimCount[AnimCountEnemy + i];
							if (AnimCount[AnimCountEnemy + i] % 7 != 0)
							{
								if (AnimCount[AnimCountEnemy + i] < 4)
								{
									g_enemyObjs[i].obj->setAnimation(13 + (g_enemyObjs[i].EnemyLevel * 18));
									g_enemyObjs[i + 1].obj->setAnimation(13 + (g_enemyObjs[i].EnemyLevel * 18));
								}
								else if (AnimCount[AnimCountEnemy + i] < 7)
								{
									g_enemyObjs[i].obj->setAnimation(14 + (g_enemyObjs[i].EnemyLevel * 18));
									g_enemyObjs[i + 1].obj->setAnimation(14 + (g_enemyObjs[i].EnemyLevel * 18));
								}
							}
							else
							{
								AnimCount[AnimCountEnemy + i] = 0;
							}
						}
					}
				}
			}
		}


	}

}