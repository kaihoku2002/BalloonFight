//----------------------------------------------------------
// ファイル名		：Thunder.cpp
// 概要				：雷と雷の弾を制御する関数の定義
// 作成者			：21CU0136 松本賢太
// 更新内容			：2022/03/10 21CU0136 松本　弾の速度を徐々に早くするよう調整…ThunderBall0Pos(),ThunderBall1Pos()
//					  2022/03/15 21CU0136 松本  時間の補正処理変更…Cnt→Phase
//					  2022/03/16 21CU0136 松本  プレイヤーとの当たり判定を実装…ThunderBallCollision()、ThunderBall()処理順変更
// 					  2022/03/17 21CU0136 松本  ブロックとの当たり判定調整…ThunderBallCollision()
//  				  2022/03/18 21CU0136 松本  ボール加速処理変更…Thunder(),ThunderBallCollision(),ThunderBall0Pos(),ThunderBall1Pos()
//  				  2022/03/18 21CU0136 松本  ブロックとの当たり判定調整…ThunderBallCollision()
//----------------------------------------------------------

#include "CActionGameApp.h"
#include "GameResource.h"
#include <time.h>
#include <stdlib.h>

/*
 * 雷の処理を行う関数
 */
void CActionGameApp::Thunder()
{

	//落雷タイミングの処理
	++g_ThunderObj.ThunderTime;
	if (g_ThunderObj.ThunderTime == 29.5 * 60.0 && g_ThunderObj.Phase == 0 && g_ThunderObj.Cnt < 2)
	{
		CloudThunderRand = rand() % 2;
		//アニメーションフラグをオンにする
		g_ThunderObj.AnimFlag = true;
	}
	//１発目の発射タイミング
	if (g_ThunderObj.ThunderTime == 30 * 60 && g_ThunderObj.Phase == 0 && g_ThunderObj.Cnt < 2)
	{
		//アニメーションフラグをオフにする
		g_ThunderObj.AnimFlag = false;
		//フラグを設定
		g_ThunderObj.flag = g_ThunderObj.flag | 0b0001;

		//雷のフェーズをカウント
		g_ThunderObj.Phase = 1;
		//個数をカウント
		++g_ThunderObj.Cnt;

		//時間のリセット
		g_ThunderObj.ThunderTime = 0;

		//座標の設定
		ThunderPos();
	}
	//１発目のフラグがオンになったら雷をみえるようにする
	if (g_ThunderObj.flag & 0b0001)
	{
		//雷を表示
		g_ThunderObj.obj->setActive(true);
		//消えるまでの時間を計測
		++g_ThunderObj.DisThunder;
	}

	//２発目以降の発射タイミング
	if (g_ThunderObj.ThunderTime == 9.5 * 60.0 && g_ThunderObj.Phase >= 1 && g_ThunderObj.Cnt < 2)
	{
		CloudThunderRand = rand() % 4;
		//アニメーションフラグをオンにする
		g_ThunderObj.AnimFlag = true;
	}
	if (g_ThunderObj.ThunderTime == 10 * 60 && g_ThunderObj.Phase >= 1 && g_ThunderObj.Cnt < 2)
	{
		//アニメーションフラグをオフにする
		g_ThunderObj.AnimFlag = false;

		//フラグを設定
		g_ThunderObj.flag = g_ThunderObj.flag | 0b0010;

		//雷のフェーズをカウント
		++g_ThunderObj.Phase;
		//個数をカウント
		++g_ThunderObj.Cnt;

		//時間のリセット
		g_ThunderObj.ThunderTime = 0;

		//座標の設定
		ThunderPos();
	}
	//2発目のフラグがオンになったら雷を見えるようにする
	if (g_ThunderObj.flag & 0b0010)
	{
		//雷を表示
		g_ThunderObj.obj->setActive(true);
		//消えるまでの時間を計測
		++g_ThunderObj.DisThunder;
	}

	//0.5秒後に雷を消す
	if (g_ThunderObj.DisThunder > 0.5 * 60)
	{
		//雷を非表示
		g_ThunderObj.obj->setActive(false);

		//時間のリセット
		g_ThunderObj.DisThunder = 0.0;

		//アニメーションフラグをオフにする
		g_ThunderObj.AnimFlag = false;

		//雷の弾の加速値を設定
		if (g_ThunderObj.Phase > 3 && BallAcceleration < MaxBallAcceleration)
		{
			BallAcceleration = BallAcceleration + 0.5f;
		}
		//弾のスピードの値をリセットする
		for (int i = 0; i < ThunderBallCnt; ++i)
		{
			if (g_ThunderBallObj[i].obj == NULL)
			{
					//スピードを毎回リセットする
					g_ThunderBallObj[i].XMoveSpeed = DefaultXSpeed;
					g_ThunderBallObj[i].YMoveSpeed = DefaultYSpeed;
			}
		}

		//弾を作成
		for (int i = 0; i < ThunderBallCnt; ++i)
		{
			if (g_ThunderBallObj[i].obj == NULL)
			{
				//1発目
				if (g_ThunderObj.flag == 0b0001 && g_ThunderObj.Phase == 1)
				{
					g_ThunderBallObj[0].obj = createSprite(Tex_ThunderBall, g_ThunderBallObj[0].Ball_SIZE_X, g_ThunderBallObj[0].Ball_SIZE_Y);
					ThunderBall0Pos();
				}
				//2発目
				else if (g_ThunderObj.flag == 0b0010 && g_ThunderObj.Phase == 2)
				{
					g_ThunderBallObj[1].obj = createSprite(Tex_ThunderBall, g_ThunderBallObj[1].Ball_SIZE_X, g_ThunderBallObj[1].Ball_SIZE_Y);
					ThunderBall1Pos();
				}
				//3発目以降で弾が１つ画面上に存在する場合
				else if (g_ThunderBallObj[0].obj == NULL && g_ThunderBallObj[1].obj != NULL)
				{
					g_ThunderBallObj[0].obj = createSprite(Tex_ThunderBall, g_ThunderBallObj[0].Ball_SIZE_X, g_ThunderBallObj[0].Ball_SIZE_Y);
					ThunderBall0Pos();
				}
				else if (g_ThunderBallObj[0].obj != NULL && g_ThunderBallObj[1].obj == NULL)
				{
					g_ThunderBallObj[1].obj = createSprite(Tex_ThunderBall, g_ThunderBallObj[1].Ball_SIZE_X, g_ThunderBallObj[1].Ball_SIZE_Y);
					ThunderBall1Pos();
				}
				//画面上に1つもない場合
				else if (g_ThunderBallObj[1].obj == NULL)
				{
					g_ThunderBallObj[1].obj = createSprite(Tex_ThunderBall, g_ThunderBallObj[1].Ball_SIZE_X, g_ThunderBallObj[1].Ball_SIZE_Y);
					ThunderBall1Pos();
				}
			}
		}
		//フラグのリセット
		g_ThunderObj.flag = 0b0000;
	}

	//時間の補正
	if (g_ThunderObj.ThunderTime >= 11 * 60 && g_ThunderObj.Phase >= 1)
	{
		g_ThunderObj.ThunderTime = 0;
	}

	ThunderAnim();

}

/*
 * 雷の弾の処理
 */
void CActionGameApp::ThunderBall()
{
	//弾が存在するときのみ処理を行う
	for (int i = 0; i < ThunderBallCnt; ++i)
	{
		if (g_ThunderBallObj[i].obj != NULL)
		{
			//座標の取得
			XMFLOAT4 EnemyBallPos = g_ThunderBallObj[i].obj->getPos();
			//移動
			//バウンドの処理
			//画面上下
			if (g_ThunderBallObj[i].obj->getPos().y >= WINDOW_TOP - (g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) ||
				g_ThunderBallObj[i].obj->getPos().y <= WINDOW_BOTTOM)
			{
				g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;

				if (!g_pThunderHit)
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pThunderHit = createSound(ThunderHit, false);
				}
			}
			//画面左右
			else if (g_ThunderBallObj[i].obj->getPos().x <= WINDOW_LEFT + (g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) - g_ThunderBallObj[i].XMoveSpeed ||
				g_ThunderBallObj[i].obj->getPos().x >= WINDOW_RIGHT - (g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) - g_ThunderBallObj[i].XMoveSpeed)
			{
				g_ThunderBallObj[i].XMoveSpeed = -g_ThunderBallObj[i].XMoveSpeed;

				if (!g_pThunderHit)
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pThunderHit = createSound(ThunderHit, false);
				}
			}

			//移動
			EnemyBallPos.x += g_ThunderBallObj[i].XMoveSpeed;
			EnemyBallPos.y += g_ThunderBallObj[i].YMoveSpeed;
			//セット 
			g_ThunderBallObj[i].obj->setPos(EnemyBallPos);

			//スピードの上限
			//X値
			if (g_ThunderBallObj[i].XMoveSpeed > 5.0f)
			{
				g_ThunderBallObj[i].XMoveSpeed = 5.0f;
			}
			else if (g_ThunderBallObj[i].XMoveSpeed < -5.0f)
			{
				g_ThunderBallObj[i].XMoveSpeed = -5.0f;
			}
			//Y値
			if (g_ThunderBallObj[i].YMoveSpeed > 5.0f)
			{
				g_ThunderBallObj[i].YMoveSpeed = 5.0f;
			}
			else if (g_ThunderBallObj[i].YMoveSpeed < -5.0f)
			{
				g_ThunderBallObj[i].YMoveSpeed = -5.0f;
			}

			//画面外に行った際に弾を消す
			if (g_ThunderBallObj[i].obj->getPos().y <= WINDOW_BOTTOM)
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
			//当たり判定
			ThunderBallCollision();
		}
	}
}

/*
 * 雷の弾の当たり判定の処理を行う関数
 */
void CActionGameApp::ThunderBallCollision()
{
	//雷
	for (int i = 0; i < g_ThunderObj.Cnt; ++i)
	{
		if (g_ThunderObj.obj != NULL && g_ThunderObj.obj->getActive() == true)
		{
			if (g_pPlayer[0]->collisionOffset(g_ThunderObj.obj, EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size))
			{
				//残機を減らす
				DeathThunderFlag = true;
			}
		}
	}
	//雷の弾
	for (int i = 0; i < ThunderBallCnt; ++i)
	{
		if (g_ThunderBallObj[i].obj != NULL)
		{
			//通常ブロック(浮島)
			for (int j = 0; j < Block.Count; ++j)
			{
				if (g_pBlock[j] != NULL)
				{
					if (g_ThunderBallObj[i].obj->collision(g_pBlock[j]))
					{
						//上下
						if (g_pBlock[j]->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (Block.Size_Y / 2.0f)) + g_ThunderBallObj[i].YMoveSpeed <= g_ThunderBallObj[i].obj->getPos().y)
						{
							g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
							g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pBlock[j]->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (Block.Size_Y / 2.0f)));

						}
						else if (g_pBlock[j]->getPos().y - ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (Block.Size_Y / 2.0f)) + g_ThunderBallObj[i].YMoveSpeed >= g_ThunderBallObj[i].obj->getPos().y)
						{
							g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
							g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pBlock[j]->getPos().y - ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (Block.Size_Y / 2.0f)));

						}
						//左右
						else if (g_pBlock[j]->getPos().x - ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (Block.Size_X / 2.0f)) - g_ThunderBallObj[i].XMoveSpeed >= g_ThunderBallObj[i].obj->getPos().x)
						{
							g_ThunderBallObj[i].XMoveSpeed = -g_ThunderBallObj[i].XMoveSpeed;
							g_ThunderBallObj[i].obj->setPos(g_pBlock[j]->getPos().x - ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (Block.Size_X / 2.0f)), g_ThunderBallObj[i].obj->getPos().y);

						}
						else if (g_pBlock[j]->getPos().x + ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (Block.Size_X / 2.0f)) + g_ThunderBallObj[i].XMoveSpeed <= g_ThunderBallObj[i].obj->getPos().x)
						{
							g_ThunderBallObj[i].XMoveSpeed = -g_ThunderBallObj[i].XMoveSpeed;
							g_ThunderBallObj[i].obj->setPos(g_pBlock[j]->getPos().x + ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (Block.Size_X / 2.0f)), g_ThunderBallObj[i].obj->getPos().y);

						}
						if (!g_pThunderHit)
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pThunderHit = createSound(ThunderHit, false);
						}
					}
				}
			}
			//左端ブロック(浮島)
			for (int j = 0; j < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++j)
			{
				if (g_pLeftBlock[j] != NULL)
				{
					if (g_ThunderBallObj[i].obj->collision(g_pLeftBlock[j]))
					{
						//上
						if (g_pLeftBlock[j]->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (LeftBlock.Size_Y / 2.0f)) + g_ThunderBallObj[i].YMoveSpeed <= g_ThunderBallObj[i].obj->getPos().y)
						{
							g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pLeftBlock[j]->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (LeftBlock.Size_Y / 2.0f)));
							g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
						}
						//下
						else if (g_pLeftBlock[j]->getPos().y - ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (LeftBlock.Size_Y / 2.0f)) + g_ThunderBallObj[i].YMoveSpeed >= g_ThunderBallObj[i].obj->getPos().y)
						{
							g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pLeftBlock[j]->getPos().y - ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (LeftBlock.Size_Y / 2.0f)));
							g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
						}
						//左
						if (g_pLeftBlock[j]->getPos().x - ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (LeftBlock.Size_X / 2.0f)) + g_ThunderBallObj[i].XMoveSpeed >= g_ThunderBallObj[i].obj->getPos().x)
						{
							g_ThunderBallObj[i].obj->setPos(g_pLeftBlock[j]->getPos().x - ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (LeftBlock.Size_Y / 2.0f)), g_ThunderBallObj[i].obj->getPos().y);
							g_ThunderBallObj[i].XMoveSpeed = -g_ThunderBallObj[i].XMoveSpeed;
						}
						if (!g_pThunderHit)
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pThunderHit = createSound(ThunderHit, false);
						}
					}
				}
			}
			//右端ブロック(浮島)
			for (int j = 0; j < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++j)
			{
				if (g_pRightBlock[j] != NULL)
				{
					if (g_ThunderBallObj[i].obj->collision(g_pRightBlock[j]))
					{
						//上
						if (g_pRightBlock[j]->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (RightBlock.Size_Y / 2.0f)) + g_ThunderBallObj[i].YMoveSpeed <= g_ThunderBallObj[i].obj->getPos().y)
						{
							g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pRightBlock[j]->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (RightBlock.Size_Y / 2.0f)));
							g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
						}
						//下
						else if (g_pRightBlock[j]->getPos().y - ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (RightBlock.Size_Y / 2.0f)) + g_ThunderBallObj[i].YMoveSpeed >= g_ThunderBallObj[i].obj->getPos().y)
						{
							g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pRightBlock[j]->getPos().y - ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (RightBlock.Size_Y / 2.0f)));
							g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
						}
						//右
						if (g_pRightBlock[j]->getPos().x + ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (RightBlock.Size_X / 2.0f)) + g_ThunderBallObj[i].XMoveSpeed <= g_ThunderBallObj[i].obj->getPos().x)
						{
							g_ThunderBallObj[i].obj->setPos(g_pRightBlock[j]->getPos().x + ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (RightBlock.Size_X / 2.0f)), g_ThunderBallObj[i].obj->getPos().y);
							g_ThunderBallObj[i].XMoveSpeed = -g_ThunderBallObj[i].XMoveSpeed;
						}
						if (!g_pThunderHit)
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pThunderHit = createSound(ThunderHit, false);
						}
					}
				}
			}
			//柱
			for (int j = 0; j < (BlockBerPos[PhaseNum - 1].ConnectCount[0] + BlockBerPos[PhaseNum - 1].ConnectCount[1] + BlockBerPos[PhaseNum - 1].ConnectCount[2] + BlockBerPos[PhaseNum - 1].ConnectCount[3] + BlockBerPos[PhaseNum - 1].ConnectCount[4]); ++j)
			{
				if (g_pBlockBer[j] != NULL)
				{
					if (g_ThunderBallObj[i].obj->collision(g_pBlockBer[j]))
					{
						//上下
						if (g_pBlockBer[j]->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (BlockBer.Size_Y / 2.0f)) + g_ThunderBallObj[i].YMoveSpeed <= g_ThunderBallObj[i].obj->getPos().y)
						{
							g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
							g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pBlockBer[j]->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (BlockBer.Size_Y / 2.0f)));

						}
						else if (g_pBlockBer[j]->getPos().y - ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (BlockBer.Size_Y / 2.0f)) + g_ThunderBallObj[i].YMoveSpeed >= g_ThunderBallObj[i].obj->getPos().y)
						{
							g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
							g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pBlockBer[j]->getPos().y - ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (BlockBer.Size_Y / 2.0f)));

						}
						//左右
						if (g_pBlockBer[j]->getPos().x - (BlockBer.Size_X / 2.0f) + (g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) - g_ThunderBallObj[i].XMoveSpeed >= g_ThunderBallObj[i].obj->getPos().x)
						{
							g_ThunderBallObj[i].XMoveSpeed = -g_ThunderBallObj[i].XMoveSpeed;
							g_ThunderBallObj[i].obj->setPos(g_pBlockBer[j]->getPos().x - ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (BlockBer.Size_X / 2.0f)), g_ThunderBallObj[i].obj->getPos().y);

						}
						else if (g_pBlockBer[j]->getPos().x + (BlockBer.Size_X / 2.0f) + (g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + g_ThunderBallObj[i].XMoveSpeed <= g_ThunderBallObj[i].obj->getPos().x)
						{
							g_ThunderBallObj[i].XMoveSpeed = -g_ThunderBallObj[i].XMoveSpeed;
							g_ThunderBallObj[i].obj->setPos(g_pBlockBer[j]->getPos().x + ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (BlockBer.Size_X / 2.0f)), g_ThunderBallObj[i].obj->getPos().y);

						}
						if (!g_pThunderHit)
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pThunderHit = createSound(ThunderHit, false);
						}
					}
				}
			}
			//通常地面
			for (int j = 0; j < Ground.Count; ++j)
			{
				if (g_pGround[j] != NULL)
				{
					if (g_ThunderBallObj[i].obj->collision(g_pGround[j]))
					{
						//上
						if (g_pGround[j]->getPos().y + (Ground.Size_Y / 2.0f + g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + g_ThunderBallObj[i].YMoveSpeed <= g_ThunderBallObj[i].obj->getPos().y)
						{
							g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pGround[j]->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (Ground.Size_Y / 2.0f)));
							g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
						}
						if (!g_pThunderHit)
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pThunderHit = createSound(ThunderHit, false);
						}
					}
				}
			}
			//左端地面
			if (g_ThunderBallObj[i].obj->collision(g_pLeftGround))
			{
				//上
				if (g_pLeftGround->getPos().y + (LeftGround.Size_Y / 2.0f + g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + g_ThunderBallObj[i].YMoveSpeed <= g_ThunderBallObj[i].obj->getPos().y)
				{
					g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pLeftGround->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (LeftGround.Size_Y / 2.0f)));
					g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
				}
				//左
				else if (g_pLeftGround->getPos().x - (LeftGround.Size_X / 2.0f + g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) - g_ThunderBallObj[i].XMoveSpeed >= g_ThunderBallObj[i].obj->getPos().x)
				{
					g_ThunderBallObj[i].obj->setPos(g_pLeftGround->getPos().x - ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + (LeftGround.Size_X / 2.0f)), g_ThunderBallObj[i].obj->getPos().y);
					g_ThunderBallObj[i].XMoveSpeed = -g_ThunderBallObj[i].XMoveSpeed;
				}
				if (!g_pThunderHit)
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pThunderHit = createSound(ThunderHit, false);
				}
			}
			//右端地面
			if (g_ThunderBallObj[i].obj->collision(g_pRightGround))
			{
				//上
				if (g_pRightGround->getPos().y + (RightGround.Size_Y / 2.0f + g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + g_ThunderBallObj[i].YMoveSpeed <= g_ThunderBallObj[i].obj->getPos().y)
				{
					g_ThunderBallObj[i].obj->setPos(g_ThunderBallObj[i].obj->getPos().x, g_pRightGround->getPos().y + ((g_ThunderBallObj[i].Ball_SIZE_Y / 2.0f) + (RightGround.Size_Y / 2.0f)));
					g_ThunderBallObj[i].YMoveSpeed = -g_ThunderBallObj[i].YMoveSpeed;
				}
				//右
				else if (g_pRightGround->getPos().x + (RightGround.Size_X / 2.0f + g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) + g_ThunderBallObj[i].XMoveSpeed <= g_ThunderBallObj[i].obj->getPos().x)
				{
					g_ThunderBallObj[i].obj->setPos(g_pRightGround->getPos().x + ((g_ThunderBallObj[i].Ball_SIZE_X / 2.0f) - (RightGround.Size_X / 2.0f)), g_ThunderBallObj[i].obj->getPos().y);
					g_ThunderBallObj[i].XMoveSpeed = -g_ThunderBallObj[i].XMoveSpeed;
				}
				if (!g_pThunderHit)
				{
					// 第2引数：ループ設定
					// ループしないので、falseを設定
					g_pThunderHit = createSound(ThunderHit, false);
				}
			}
		}
	}
	//プレイヤー
	for (int j = 0; j < 2; ++j)
	{
		if (g_pPlayer[j] != NULL && DeathFlag != true && DeathThunderFlag != true &&
			CollisionFlag == true && g_pPlayer[0]->getActive() == true && DeathCoolFlag != true)
		{
			for (int i = 0; i < ThunderBallCnt; ++i)
			{
				if (g_ThunderBallObj[i].obj != NULL)
				{
					if (g_pPlayer[j]->collisionOffset(g_ThunderBallObj[i].obj, EntityToObjCollisionData.Pos, EntityToObjCollisionData.Size))
					{
						//弾を消す
						disposeSprite(g_ThunderBallObj[i].obj);
						g_ThunderBallObj[i].obj = NULL;
						//個数カウントを減らす
						--g_ThunderObj.Cnt;
						//補正
						if (g_ThunderObj.Cnt < 0)
						{
							g_ThunderObj.Cnt = 0;
						}
						//弾のスピードを戻す
						g_ThunderBallObj[i].XMoveSpeed = DefaultXSpeed;
						g_ThunderBallObj[i].YMoveSpeed = DefaultYSpeed;
						//残機を減らす
						DeathThunderFlag = true;
						//雷のフェーズを戻す
						g_ThunderObj.Phase = 0;
						if (!g_pThunderDeath)
						{
							// 第2引数：ループ設定
							// ループしないので、falseを設定
							g_pThunderDeath = createSound(ThunderDeath, false);
						}
					}
				}
			}
		}
	}
}

/*
 * 雷の座標の処理を行う関数
 */
void CActionGameApp::ThunderPos()
{
	//乱数の調整
	g_ThunderObj.ThunderRand = rand() % 4;

	//画像のセット
	for (int i = 0; i < Cloud.Count; ++i)
	{
		if (PhaseNum == 1)
		{
			g_ThunderObj.obj->setPos(g_pCloud[i]->getPos().x, g_pCloud[i]->getPos().y);
		}
		else
		{
			if (CloudThunderRand == 0)
			{
				g_ThunderObj.obj->setPos(g_pCloud[0]->getPos().x, g_pCloud[0]->getPos().y);
			}
			else
			{
				g_ThunderObj.obj->setPos(g_pCloud[1]->getPos().x, g_pCloud[1]->getPos().y);
			}
		}
	}
	//乱数によって雷の向きを変える
	if (g_ThunderObj.ThunderRand == 0)
	{
		//右上
		g_ThunderObj.obj->setPos(g_ThunderObj.obj->getPos().x + 36.0f + g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y + 80.0f);
		g_ThunderObj.obj->setAngle(0.0f, 180.0f, .0f);
	}
	else if (g_ThunderObj.ThunderRand == 1)
	{
		//左上
		g_ThunderObj.obj->setPos(g_ThunderObj.obj->getPos().x - 28.0f - g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y + 76.0f);
		g_ThunderObj.obj->setAngle(0.0f, 0.0f, 0.0f);
	}
	else if (g_ThunderObj.ThunderRand == 2)
	{
		//右下
		g_ThunderObj.obj->setPos(g_ThunderObj.obj->getPos().x + 36.0f + g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y - 88.0f);
		g_ThunderObj.obj->setAngle(0.0f, 0.0f, 180.0f);
	}
	else if (g_ThunderObj.ThunderRand == 3)
	{
		//左下
		g_ThunderObj.obj->setPos(g_ThunderObj.obj->getPos().x - 28.0f - g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y - 92.0f);
		g_ThunderObj.obj->setAngle(0.0f, 180.0f, 180.0f);
	}
}

/*
 * 弾0の座標設定を行う関数
 */
void CActionGameApp::ThunderBall0Pos()
{
	//乱数によって弾の処理を変更
	if (g_ThunderBallObj[0].obj != NULL)
	{
		//右上
		if (g_ThunderObj.ThunderRand == 0)
		{
			//弾のベクトルを変更
			if (g_ThunderBallObj[0].XMoveSpeed < 0)
			{
				g_ThunderBallObj[0].XMoveSpeed = -g_ThunderBallObj[0].XMoveSpeed;
			}
			if (g_ThunderBallObj[0].YMoveSpeed < 0)
			{
				g_ThunderBallObj[0].YMoveSpeed = -g_ThunderBallObj[0].YMoveSpeed;
			}
			g_ThunderBallObj[0].obj->setPos(g_ThunderObj.obj->getPos().x + g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y + g_ThunderObj.Thunder_SIZE_Y / 2);
			//徐々にスピードを速くする
			if (g_ThunderObj.Phase > 2)
			{
				g_ThunderBallObj[0].XMoveSpeed = g_ThunderBallObj[0].XMoveSpeed + BallAcceleration;
				g_ThunderBallObj[0].YMoveSpeed = g_ThunderBallObj[0].YMoveSpeed + (BallAcceleration * 2);
			}
		}
		//左上
		else if (g_ThunderObj.ThunderRand == 1)
		{
			//弾のベクトルを変更
			if (g_ThunderBallObj[0].XMoveSpeed > 0)
			{
				g_ThunderBallObj[0].XMoveSpeed = -g_ThunderBallObj[0].XMoveSpeed;
			}
			if (g_ThunderBallObj[0].YMoveSpeed < 0)
			{
				g_ThunderBallObj[0].YMoveSpeed = -g_ThunderBallObj[0].YMoveSpeed;
			}
			//画像のセット
			g_ThunderBallObj[0].obj->setPos(g_ThunderObj.obj->getPos().x - g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y + g_ThunderObj.Thunder_SIZE_Y / 2);
			//徐々にスピードを速くする
			if (g_ThunderObj.Phase > 2)
			{
				g_ThunderBallObj[0].XMoveSpeed = g_ThunderBallObj[0].XMoveSpeed - BallAcceleration;
				g_ThunderBallObj[0].YMoveSpeed = g_ThunderBallObj[0].YMoveSpeed + (BallAcceleration * 2);
			}
		}
		//右下
		else if (g_ThunderObj.ThunderRand == 2)
		{
			//弾のベクトルを変更
			if (g_ThunderBallObj[0].XMoveSpeed < 0)
			{
				g_ThunderBallObj[0].XMoveSpeed = -g_ThunderBallObj[0].XMoveSpeed;
			}
			if (g_ThunderBallObj[0].YMoveSpeed > 0)
			{
				g_ThunderBallObj[0].YMoveSpeed = -g_ThunderBallObj[0].YMoveSpeed;
			}
			//画像のセット
			g_ThunderBallObj[0].obj->setPos(g_ThunderObj.obj->getPos().x + g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y - g_ThunderObj.Thunder_SIZE_Y / 2);
			//徐々にスピードを速くする
			if (g_ThunderObj.Phase > 2)
			{
				g_ThunderBallObj[0].XMoveSpeed = g_ThunderBallObj[0].XMoveSpeed + BallAcceleration;
				g_ThunderBallObj[0].YMoveSpeed = g_ThunderBallObj[0].YMoveSpeed - (BallAcceleration * 2);
			}
		}
		//左下
		else if (g_ThunderObj.ThunderRand == 3)
		{
			//弾のベクトルを変更
			if (g_ThunderBallObj[0].XMoveSpeed > 0)
			{
				g_ThunderBallObj[0].XMoveSpeed = -g_ThunderBallObj[0].XMoveSpeed;
			}
			if (g_ThunderBallObj[0].YMoveSpeed > 0)
			{
				g_ThunderBallObj[0].YMoveSpeed = -g_ThunderBallObj[0].YMoveSpeed;
			}
			//画像のセット
			g_ThunderBallObj[0].obj->setPos(g_ThunderObj.obj->getPos().x - g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y - g_ThunderObj.Thunder_SIZE_Y / 2);
			//徐々にスピードを速くする
			if (g_ThunderObj.Phase > 2)
			{
				g_ThunderBallObj[0].XMoveSpeed = g_ThunderBallObj[0].XMoveSpeed - BallAcceleration;
				g_ThunderBallObj[0].YMoveSpeed = g_ThunderBallObj[0].YMoveSpeed - (BallAcceleration * 2);
			}
		}
	}
}
/*
 * 弾1の座標設定を行う関数
 */
void CActionGameApp::ThunderBall1Pos()
{
	//乱数によって弾の処理を変更
	if (g_ThunderBallObj[1].obj != NULL)
	{
		//右上
		if (g_ThunderObj.ThunderRand == 0)
		{
			//弾のベクトルを変更
			if (g_ThunderBallObj[1].XMoveSpeed < 0)
			{
				g_ThunderBallObj[1].XMoveSpeed = -g_ThunderBallObj[1].XMoveSpeed;
			}
			if (g_ThunderBallObj[1].YMoveSpeed < 0)
			{
				g_ThunderBallObj[1].YMoveSpeed = -g_ThunderBallObj[1].YMoveSpeed;
			}
			g_ThunderBallObj[1].obj->setPos(g_ThunderObj.obj->getPos().x + g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y + g_ThunderObj.Thunder_SIZE_Y / 2);
			//徐々にスピードを速くする
			if (g_ThunderObj.Phase > 2)
			{
				g_ThunderBallObj[1].XMoveSpeed = g_ThunderBallObj[1].XMoveSpeed + BallAcceleration;
				g_ThunderBallObj[1].YMoveSpeed = g_ThunderBallObj[1].YMoveSpeed + (BallAcceleration * 2);
			}
		}
		//左上
		else if (g_ThunderObj.ThunderRand == 1)
		{
			//弾のベクトルを変更
			if (g_ThunderBallObj[1].XMoveSpeed > 0)
			{
				g_ThunderBallObj[1].XMoveSpeed = -g_ThunderBallObj[1].XMoveSpeed;
			}
			if (g_ThunderBallObj[1].YMoveSpeed < 0)
			{
				g_ThunderBallObj[1].YMoveSpeed = -g_ThunderBallObj[1].YMoveSpeed;
			}
			//画像のセット
			g_ThunderBallObj[1].obj->setPos(g_ThunderObj.obj->getPos().x - g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y + g_ThunderObj.Thunder_SIZE_Y / 2);
			//徐々にスピードを速くする
			if (g_ThunderObj.Phase > 2)
			{
				g_ThunderBallObj[1].XMoveSpeed = g_ThunderBallObj[1].XMoveSpeed - BallAcceleration;
				g_ThunderBallObj[1].YMoveSpeed = g_ThunderBallObj[1].YMoveSpeed + (BallAcceleration * 2);
			}
		}
		//右下
		else if (g_ThunderObj.ThunderRand == 2)
		{
			//弾のベクトルを変更
			if (g_ThunderBallObj[1].XMoveSpeed < 0)
			{
				g_ThunderBallObj[1].XMoveSpeed = -g_ThunderBallObj[1].XMoveSpeed;
			}
			if (g_ThunderBallObj[1].YMoveSpeed > 0)
			{
				g_ThunderBallObj[1].YMoveSpeed = -g_ThunderBallObj[1].YMoveSpeed;
			}
			//画像のセット
			g_ThunderBallObj[1].obj->setPos(g_ThunderObj.obj->getPos().x + g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y - g_ThunderObj.Thunder_SIZE_Y / 2);
			//徐々にスピードを速くする
			if (g_ThunderObj.Phase > 2)
			{
				g_ThunderBallObj[1].XMoveSpeed = g_ThunderBallObj[1].XMoveSpeed + BallAcceleration;
				g_ThunderBallObj[1].YMoveSpeed = g_ThunderBallObj[1].YMoveSpeed - (BallAcceleration * 2);
			}
		}
		//左下
		else if (g_ThunderObj.ThunderRand == 3)
		{
			//弾のベクトルを変更
			if (g_ThunderBallObj[1].XMoveSpeed > 0)
			{
				g_ThunderBallObj[1].XMoveSpeed = -g_ThunderBallObj[1].XMoveSpeed;
			}
			if (g_ThunderBallObj[1].YMoveSpeed > 0)
			{
				g_ThunderBallObj[1].YMoveSpeed = -g_ThunderBallObj[1].YMoveSpeed;
			}
			//画像のセット
			g_ThunderBallObj[1].obj->setPos(g_ThunderObj.obj->getPos().x - g_ThunderObj.Thunder_SIZE_X / 2, g_ThunderObj.obj->getPos().y - g_ThunderObj.Thunder_SIZE_Y / 2);
			//徐々にスピードを速くする
			if (g_ThunderObj.Phase > 2)
			{
				g_ThunderBallObj[1].XMoveSpeed = g_ThunderBallObj[1].XMoveSpeed - BallAcceleration;
				g_ThunderBallObj[1].YMoveSpeed = g_ThunderBallObj[1].YMoveSpeed - (BallAcceleration * 2);
			}
		}
	}
}

/*
 * 雷の画像の作成を行う関数
 */
void CActionGameApp::ThunderCreate()
{
	//画像作成
	if (g_ThunderObj.obj == NULL)
	{
		g_ThunderObj.obj = createSprite(Tex_Thunder, g_ThunderObj.Thunder_SIZE_X, g_ThunderObj.Thunder_SIZE_Y);
		//最初は見せなくする
		g_ThunderObj.obj->setActive(false);
	}
}

/*
 * 雷の画像の描画を行う関数
 */
void CActionGameApp::ThunderRender()
{
	//画像描画
	if (g_ThunderObj.obj != NULL)
	{
		renderSprite(g_ThunderObj.obj);
	}

	//弾描画
	for (int i = 0; i < ThunderBallCnt; ++i)
	{
		if (g_ThunderBallObj[i].obj != NULL)
		{
			renderSprite(g_ThunderBallObj[i].obj);
		}
	}
}

/*
 * 雷の画像の破棄を行う関数
 */
void CActionGameApp::ThunderDispose()
{
	//画像破棄
	if (g_ThunderObj.obj != NULL)
	{
		disposeSprite(g_ThunderObj.obj);
		g_ThunderObj.obj = NULL;
	}

	//弾破棄
	for (int i = 0; i < ThunderBallCnt; ++i)
	{
		if (g_ThunderBallObj[i].obj != NULL)
		{
			disposeSprite(g_ThunderBallObj[i].obj);
			g_ThunderBallObj[i].obj = NULL;
		}
	}

	//フラグリセット
	g_ThunderObj.flag = 0b0000;

	//個数のリセット
	g_ThunderObj.Cnt = 0;

	//時間のリセット
	g_ThunderObj.ThunderTime = 0;
	g_ThunderObj.Phase = 0;

	g_ThunderObj.AnimFlag = false;
}