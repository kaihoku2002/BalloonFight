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

//オブジェクトの生成
void CActionGameApp::ObjCreate()
{
	/*背景
	g_pBackGround = createSprite(Tex_BackGround,BackGround_X, BackGround_Y);
	*/
	//波(中央)
	for (int i = 0; i < Wave.Count; ++i)
	{
		g_pWave[i] = createSprite(Tex_Wave, Wave.Size_X, Wave.Size_Y);
	}
	//波(両端)
	for (int i = 0; i < EndWave.Count; ++i)
	{
		g_pEndWave[i] = createSprite(Tex_EndWave, EndWave.Size_X, EndWave.Size_Y);
	}
	//地面(中央)
	for (int i = 0; i < Ground.Count; ++i)
	{
		g_pGround[i] = createSprite(Tex_Ground, Ground.Size_X, Ground.Size_Y);
	}
	//地面(右端)
	g_pRightGround = createSprite(Tex_RightGround, RightGround.Size_X, RightGround.Size_Y);
	//地面(左端)
	g_pLeftGround = createSprite(Tex_LeftGround, LeftGround.Size_X, LeftGround.Size_Y);
	//浮島(中央)
	for (int i = 0; i < Block.Count; ++i)
	{
		g_pBlock[i] = createSprite(Tex_Block, Block.Size_X, Block.Size_Y);
	}
	//浮島(右端)
	for (int i = 0; i < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++i)
	{
		g_pRightBlock[i] = createSprite(Tex_RightBlock, RightBlock.Size_X, RightBlock.Size_Y);
	}
	//浮島(左端)
	for (int i = 0; i < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++i)
	{
		g_pLeftBlock[i] = createSprite(Tex_LeftBlock, LeftBlock.Size_X, LeftBlock.Size_Y);
	}
	//雲
	for (int i = 0; i < CloudPos[PhaseNum - 1].Count; ++i)
	{
		g_pCloud[i] = createSprite(Tex_Cloud, Cloud.Size_X, Cloud.Size_Y);
	}
	//浮島(柱)
	for (int i = 0; i < (BlockBerPos[PhaseNum - 1].ConnectCount[0] + BlockBerPos[PhaseNum - 1].ConnectCount[1] + BlockBerPos[PhaseNum - 1].ConnectCount[2] + BlockBerPos[PhaseNum - 1].ConnectCount[3] + BlockBerPos[PhaseNum - 1].ConnectCount[4]); ++i)
	{
		g_pBlockBer[i] = createSprite(Tex_BlockBer, BlockBer.Size_X, BlockBer.Size_Y);
	}
}

//オブジェクトの描画
void CActionGameApp::Objrender()
{
	//地面(中央)
	for (int i = 0; i < Ground.Count; ++i)
	{
		renderSprite(g_pGround[i]);
	}
	//地面(右端)
	renderSprite(g_pRightGround);
	//地面(左端)
	renderSprite(g_pLeftGround);
	//浮島(中央)
	for (int i = 0; i < Block.Count; ++i)
	{
		renderSprite(g_pBlock[i]);
	}
	//浮島(柱)
	for (int i = 0; i < (BlockBerPos[PhaseNum - 1].ConnectCount[0] + BlockBerPos[PhaseNum - 1].ConnectCount[1] + BlockBerPos[PhaseNum - 1].ConnectCount[2] + BlockBerPos[PhaseNum - 1].ConnectCount[3] + BlockBerPos[PhaseNum - 1].ConnectCount[4]); ++i)
	{
		renderSprite(g_pBlockBer[i]);
	}
	//浮島(中右端)
	for (int i = 0; i < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++i)
	{
		renderSprite(g_pRightBlock[i]);
	}
	//浮島(左端)
	for (int i = 0; i < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++i)
	{
		renderSprite(g_pLeftBlock[i]);
	}
	//死亡時のみ表示する
	if (DeathFlag == true)
	{
		for (int i = 0; i < 2; i++)
		{
			if (g_pPlayer[i] != NULL)
			{
				renderSprite(g_pPlayer[i]);
			}
		}
	}
	for (int i = 0; i < ENEMY_OBJECT_COUNT; ++i)
	{
		if (g_enemyObjs[i].EnemyStatus == 4 && g_enemyObjs[i].obj != NULL)
		{
			renderSprite(g_enemyObjs[i].obj);
		}
	}


	//泡の描画
	for (int i = 0; i < BubbleCount; ++i)
	{
		if (g_pBubble[i] != NULL)
		{
			renderSprite(g_pBubble[i]);
		}
	}
	//波(中央)
	for (int i = 0; i < Wave.Count; ++i)
	{
		renderSprite(g_pWave[i]);
	}
	//波(両端)
	for (int i = 0; i < EndWave.Count; ++i)
	{
		renderSprite(g_pEndWave[i]);
	}
}

//背景・曇描画
void CActionGameApp::Backrender()
{
	//背景が作成されていたら描画する
	if (g_pBackground != NULL)
	{
		renderSprite(g_pBackground);
	}
	//雲
	for (int i = 0; i < Cloud.Count; ++i)
	{
		renderSprite(g_pCloud[i]);
	}
}

//オブジェクトの破棄
void CActionGameApp::ObjDispose()
{
	/*背景
	disposeSprite(g_pBackGround);
	*/
	g_pBackground = NULL;
	//波(中央)
	for (int i = 0; i < Wave.Count; ++i)
	{
		disposeSprite(g_pWave[i]);
		g_pWave[i] = NULL;
	}
	//波(両端)
	for (int i = 0; i < EndWave.Count; ++i)
	{
		disposeSprite(g_pEndWave[i]);
		g_pEndWave[i] = NULL;
	}
	//地面(中央)
	for (int i = 0; i < Ground.Count; ++i)
	{
		disposeSprite(g_pGround[i]);
		g_pGround[i] = NULL;
	}
	//地面(右端)
	disposeSprite(g_pRightGround);
	g_pRightGround = NULL;
	//地面(左端)
	disposeSprite(g_pLeftGround);
	g_pLeftGround = NULL;
	//浮島(中央)
	for (int i = 0; i < Block.Count; ++i)
	{
		disposeSprite(g_pBlock[i]);
		g_pBlock[i] = NULL;
	}
	//浮島(中央)
	for (int i = 0; i < (BlockBerPos[PhaseNum - 1].ConnectCount[0] + BlockBerPos[PhaseNum - 1].ConnectCount[1] + BlockBerPos[PhaseNum - 1].ConnectCount[2] + BlockBerPos[PhaseNum - 1].ConnectCount[3] + BlockBerPos[PhaseNum - 1].ConnectCount[4]); ++i)
	{
		disposeSprite(g_pBlockBer[i]);
		g_pBlockBer[i] = NULL;
	}
	//浮島(右端)
	for (int i = 0; i < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++i)
	{
		disposeSprite(g_pRightBlock[i]);
		g_pRightBlock[i] = NULL;
	}
	//浮島(左端)
	for (int i = 0; i < (BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count); ++i)
	{
		disposeSprite(g_pLeftBlock[i]);
		g_pLeftBlock[i] = NULL;
	}
	//雲
	for (int i = 0; i < Cloud.Count; ++i)
	{
		disposeSprite(g_pCloud[i]);
		g_pCloud[i] = NULL;
	}
}

//オブジェクトの設置
void CActionGameApp::ObjSetPos()
{
	//波
	//(中央)
	for (int i = 0; i < Wave.Count; ++i)
	{
		g_pWave[i]->setPos(-(WINDOW_WIDTH / 2.0f - Wave.Size_X / 2.0f) + (((float)i + 2.0f) * Wave.Size_X),
			WINDOW_BOTTOM + Wave.Size_Y / 2.0f);
	}
	//(左端)
	for (int i = 0; i < EndWave.Count / 2; ++i)
	{
		g_pEndWave[i]->setPos(-(WINDOW_WIDTH / 2.0f - EndWave.Size_X / 2.0f) + ((float)i * Wave.Size_X),
			WINDOW_BOTTOM + EndWave.Size_Y / 2.0f);
	}
	//(右端)
	for (int i = EndWave.Count / 2; i < EndWave.Count; ++i)
	{
		g_pEndWave[i]->setPos((WINDOW_WIDTH / 2.0f - EndWave.Size_X / 2.0f) - (((float)i - EndWave.Count / 2) * Wave.Size_X),
			WINDOW_BOTTOM + EndWave.Size_Y / 2.0f);
	}
	//地面
	//左側
	for (int i = 0; i < (Ground.Count/2) + RightGround.Count; ++i)
	{
		//(右端)
		if (i == (Ground.Count / 2) + RightGround.Count - 1)
		{
			g_pRightGround->setPos(-(WINDOW_WIDTH / 2.0f) + (((float)i - 3.0f) * Ground.Size_X) - (RightGround.Size_X / 2.0f),
				WINDOW_BOTTOM + 56.0f + (RightGround.Size_Y / 2.0f));
		}
		//(中央)
		else
		{
			g_pGround[i]->setPos(-(WINDOW_WIDTH / 2.0f) + (((float)i - 3.0f) * Ground.Size_X),
				WINDOW_BOTTOM + 56.0f + (Ground.Size_Y / 2.0f));
		}
	}
	//右側
	for (int i = Ground.Count / 2; i < Ground.Count + 1.0f; ++i)
	{
		//(左端)
		if (i == Ground.Count)
		{
			g_pLeftGround->setPos((WINDOW_WIDTH / 2.0f) - ((((float)i - 3.0f) - ((Ground.Count + LeftGround.Count) / 2)) * Ground.Size_X) + (LeftGround.Size_X / 2.0f),
				WINDOW_BOTTOM + 56.0f + (LeftGround.Size_Y / 2.0f));
		}
		//(中央)
		else
		{
			g_pGround[i]->setPos((WINDOW_WIDTH / 2.0f) - (((float)i - (Ground.Count / 2) - 3.0f) * Ground.Size_X),
				WINDOW_BOTTOM + 56.0f + (Ground.Size_Y / 2.0f));
		}
	}
	//浮島
	for (int i = 0 , CentralCnt = 0; i < BlockPos[PhaseNum - 1].Count; ++i)
	{
		for (int j = -1; j < BlockPos[PhaseNum - 1].ConnectCount[i] + 1; ++j)
		{
			//(左端)
			if (j == -1)
			{
				g_pLeftBlock[i]->setPos(-(((float)(BlockPos[PhaseNum - 1].ConnectCount[i]) / 2.0f) * Block.Size_X) - (LeftBlock.Size_X / 2.0f) + (32.0f * BlockPos[PhaseNum - 1].PosX[i]),
					WINDOW_BOTTOM + (32.0f * BlockPos[PhaseNum - 1].PosY[i]) + (Block.Size_Y / 2.0f));
			}
			//(右端)
			else if (j == BlockPos[PhaseNum - 1].ConnectCount[i])
			{
				g_pRightBlock[i]->setPos(-(((float)(BlockPos[PhaseNum - 1].ConnectCount[i]) / 2.0f) * Block.Size_X) + ((float)j * Block.Size_X) + (RightBlock.Size_X / 2.0f) + (32.0f * BlockPos[PhaseNum - 1].PosX[i]),
					WINDOW_BOTTOM + (32.0f * BlockPos[PhaseNum - 1].PosY[i]) + (Block.Size_Y / 2.0f));
			}
			//(中央)
			else
			{
				g_pBlock[CentralCnt]->setPos(-(((float)(BlockPos[PhaseNum - 1].ConnectCount[i]) / 2.0f) * Block.Size_X) + ((float)j * Block.Size_X) + (Block.Size_X / 2.0f) + (32.0f * BlockPos[PhaseNum - 1].PosX[i]),
					WINDOW_BOTTOM + (32.0f * BlockPos[PhaseNum - 1].PosY[i]) + (Block.Size_Y / 2.0f));
				++CentralCnt;
			}
		}
	}
	//浮島(柱)
	for (int i = 0; i < BlockBerPos[PhaseNum - 1].Count; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			//(左端)
			if (j == -1)
			{
				g_pLeftBlock[i+ BlockPos[PhaseNum - 1].Count]->setPos(-(1.0f * BlockBer.Size_X) + (32.0f * BlockBerPos[PhaseNum - 1].PosX[i]),
					WINDOW_BOTTOM + (32.0f * BlockBerPos[PhaseNum - 1].PosY[i]) + (Block.Size_Y / 2.0f));
			}
			//(右端)
			else if (j == 1)
			{
				g_pRightBlock[i+ BlockPos[PhaseNum - 1].Count]->setPos(1.0f * BlockBer.Size_X + (32.0f * BlockBerPos[PhaseNum - 1].PosX[i]),
					WINDOW_BOTTOM + (32.0f * BlockBerPos[PhaseNum - 1].PosY[i]) + (Block.Size_Y / 2.0f));
			}
			//(中央)
			else
			{
				for (int CentralCnt = 0; CentralCnt < BlockBerPos[PhaseNum - 1].ConnectCount[i]; ++CentralCnt)
				{
					g_pBlockBer[CentralCnt + (i * BlockBerPos[PhaseNum - 1].ConnectCount[i])]->setPos((32.0f * BlockBerPos[PhaseNum - 1].PosX[i]),
						WINDOW_BOTTOM + (32.0f * BlockBerPos[PhaseNum - 1].PosY[i]) + (Block.Size_Y / 2.0f) - (BlockBer.Size_Y * CentralCnt));
					if (CentralCnt == 0)
					{
						g_pBlockBer[CentralCnt + (i * BlockBerPos[PhaseNum - 1].ConnectCount[i])]->setAnimation(0);
					}
					else if (CentralCnt == (BlockBerPos[PhaseNum - 1].ConnectCount[i] - 1))
					{
						g_pBlockBer[CentralCnt + (i * BlockBerPos[PhaseNum - 1].ConnectCount[i])]->setAnimation(2);
					}
					else
					{
						g_pBlockBer[CentralCnt + (i * BlockBerPos[PhaseNum - 1].ConnectCount[i])]->setAnimation(1);
					}
				}
			}
		}
	}
	//雲
	for (int i = 0; i < CloudPos[PhaseNum - 1].Count; ++i)
	{
		g_pCloud[i]->setPos((32.0f * CloudPos[PhaseNum - 1].PosX[i]) + Cloud.Size_X / 2.0f,WINDOW_BOTTOM + (32.0f * CloudPos[PhaseNum - 1].PosY[i]) + (Cloud.Size_Y / 2.0f));
	}
}


//ボーナスステージのオブジェクト作成
void CActionGameApp::BObjCreate()
{
	//以下ボーナスステージの画像作成
	//地面
	for (int i = 0; i < BGround.Count; ++i)
	{
		if (g_pBGround[i] == NULL)
		{
			g_pBGround[i] = createSprite(Tex_BGround, BGround.Size_X, BGround.Size_Y);
		}

	}
	//土管
	for (int i = 0; i < 16; ++i)
	{
		if (g_pPipe[i] == NULL)
		{
			g_pPipe[i] = createSprite(Tex_BPipe, Pipe.Size_X, Pipe.Size_Y);
		}
	}
	//背景
	g_pBBackGround = createSprite(Tex_bBacGround);
	//背景アニメーション
	g_pBBackAnim = createSprite(Tex_bBackAnim);

}

//ボーナスステージの画像描画
void CActionGameApp::BObjrender()
{
	//地面
	for (int i = 0; i < BGround.Count; ++i)
	{
		if (g_pBGround[i] != NULL)
		{
			renderSprite(g_pBGround[i]);
		}
	}
	//土管
	for (int i = 0; i < 16; ++i)
	{
		if (g_pPipe[i] != NULL)
		{
			renderSprite(g_pPipe[i]);
		}

	}

}

//ボーナスステージの画像配置
void CActionGameApp::BObjSetPos()
{
	//地面
	for (int i = 0; i < BGround.Count; ++i)
	{
		if (g_pBGround[i] != NULL)
		{
			g_pBGround[i]->setPos(-(WINDOW_WIDTH / 2.0f) + (((float)i + 1) * BGround.Size_X) - (BGround.Size_X / 2.0f) - (64.0f * 2.0f), (WINDOW_BOTTOM + BGround.Size_Y / 2));

		}
	}
	//土管1
	for (int i = 0; i < 4; ++i)
	{
		if (g_pPipe[i + 0] != NULL)
		{
			g_pPipe[i + 0]->setPos((WINDOW_LEFT + ((float)32.0 * 4.0)), (WINDOW_BOTTOM + ((float)64.0 + 32.0 * i) + 16.0f));
			//一番上は土管の口にする
			if (i + 0 == 3)
			{
				g_pPipe[i + 0]->setAnimation(1);
			}
		}

	}
	//土管2
	for (int i = 0; i < 5; ++i)
	{
		if (g_pPipe[i + 4] != NULL)
		{
			g_pPipe[i + 4]->setPos((WINDOW_LEFT + ((float)32.0 * 10.0)), (WINDOW_BOTTOM + ((float)64.0 + 32.0 * i) + 16.0f));
			//一番上は土管の口にする
			if (i + 4 == 8)
			{
				g_pPipe[i + 4]->setAnimation(1);
			}
		}

	}
	//土管3
	for (int i = 0; i < 3; ++i)
	{
		if (g_pPipe[i + 9] != NULL)
		{
			g_pPipe[i + 9]->setPos((WINDOW_LEFT + ((float)32.0 * 20.0)), (WINDOW_BOTTOM + ((float)64.0 + 32.0 * i) + 16.0f));
			//一番上は土管の口にする
			if (i + 9 == 11)
			{
				g_pPipe[i + 9]->setAnimation(1);
			}
		}

	}
	//土管4
	for (int i = 0; i < 4; ++i)
	{
		if (g_pPipe[i + 12] != NULL)
		{
			g_pPipe[i + 12]->setPos((WINDOW_LEFT + ((float)32.0 * 26.0)), (WINDOW_BOTTOM + ((float)64.0 + 32.0 * i) + 16.0f));
			//一番上は土管の口にする
			if (i + 12 == 15)
			{
				g_pPipe[i + 12]->setAnimation(1);
			}
		}

	}
}

//ボーナスステージの画像破棄
void CActionGameApp::BObjDispose()
{
	//地面
	for (int i = 0; i < BGround.Count; ++i)
	{
		if (g_pBGround[i] != NULL)
		{
			disposeSprite(g_pBGround[i]);
			g_pBGround[i] = NULL;
		}

	}
	//土管
	for (int i = 0; i < 16; ++i)
	{
		if (g_pPipe[i] != NULL)
		{
			disposeSprite(g_pPipe[i]);
			g_pPipe[i] = NULL;
		}

	}
	//風船
	for (int i = 0; i < 20; ++i)
	{
		if (g_pBalloon[i].Obj != NULL)
		{
			disposeSprite(g_pBalloon[i].Obj);
			g_pBalloon[i].Obj = NULL;
		}
	}
	//背景
	if (g_pBBackGround != NULL)
	{
		disposeSprite(g_pBBackGround);
		g_pBBackGround = NULL;
	}
}

//背景の描画
void CActionGameApp::BBackrender()
{
	if (g_pBBackGround != NULL)
	{
		renderSprite(g_pBBackGround);
		if (g_pBBackAnim != NULL)
		{
			++AnimCount[AnimCountBack];
			if (AnimCount[AnimCountBack] % 30 == 0)
			{
				g_pBBackAnim->stepAnimation();
				AnimCount[AnimCountBack] = 0;
			}
			renderSprite(g_pBBackAnim);
		}
	}
}

//風船設置
void CActionGameApp::balloonSet()
{
	++balloonCnt;
	//風船
	if (NowballoonCnt < 20)
	{
		if (g_pBalloon[NowballoonCnt].Obj == NULL && balloonCnt % 50 == 0)
		{
			int RandNum = (rand() * (rand() % 30)) % 60;
			g_pBalloon[NowballoonCnt].Obj = createSprite(Tex_BBalloon, Balloon.Size_X, Balloon.Size_Y);
			if (RandNum < 15)
			{
				g_pBalloon[NowballoonCnt].Obj->setPos((WINDOW_LEFT + ((float)32.0 * 4.0)) , WINDOW_BOTTOM + 92.0f);
			}
			else if (RandNum < 30)
			{
				g_pBalloon[NowballoonCnt].Obj->setPos((WINDOW_LEFT + ((float)32.0 * 10.0)) , WINDOW_BOTTOM + 92.0f);
			}
			else if (RandNum < 45)
			{
				g_pBalloon[NowballoonCnt].Obj->setPos((WINDOW_LEFT + ((float)32.0 * 20.0)) , WINDOW_BOTTOM + 92.0f);
			}
			else if (RandNum < 60)
			{
				g_pBalloon[NowballoonCnt].Obj->setPos((WINDOW_LEFT + ((float)32.0 * 26.0)) , WINDOW_BOTTOM + 92.0f);
			}
			++NowballoonCnt;
		}
	}
}