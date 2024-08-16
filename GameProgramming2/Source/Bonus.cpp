#include "CActionGameApp.h"
#include "GameResource.h"



//ボーナスステージのメイン処理
void CActionGameApp::BonusStage()
{

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

	BBackrender();

	//UIの描画
	UIrender();

	//風船
	// 設置
	balloonSet();
	//当たり判定
	BBalloonCollision();
	BalloonAnim();
	for (int i = 0; i < BALLOON_OBJECT_COUNT; ++i)
	{
		//作成されていたら処理を行う
		if (g_pBalloon[i].Obj != NULL)
		{
			/*g_pBallon->setPos(g_pBallon->getPos().x, g_pBallon->getPos().y + 3.0f);*/


			//左の移動処理
			if (g_pBalloon[i].BalloonCourse == 1)
			{
				if (-(g_pBalloon[i].BalloonMove) < g_pBalloon[i].BalloonSpeed)
				{
					g_pBalloon[i].BalloonSpeed -= 0.07;
				}
				else
				{
					g_pBalloon[i].BalloonCourse = 2;
				}
				g_pBalloon[i].Obj->setPos(g_pBalloon[i].Obj->getPos().x + g_pBalloon[i].BalloonSpeed, g_pBalloon[i].Obj->getPos().y + 2.5f);
			}
			//右の移動処理
			else if (g_pBalloon[i].BalloonCourse == 2)
			{
				if (g_pBalloon[i].BalloonMove > g_pBalloon[i].BalloonSpeed)
				{
					g_pBalloon[i].BalloonSpeed += 0.07;
				}
				else
				{
					g_pBalloon[i].BalloonCourse = 1;
				}
				g_pBalloon[i].Obj->setPos(g_pBalloon[i].Obj->getPos().x + g_pBalloon[i].BalloonSpeed, g_pBalloon[i].Obj->getPos().y + 2.5f);
			}
			//土管の中
			else if(g_pBalloon[i].BalloonCourse == 3)
			{
				g_pBalloon[i].Obj->setPos(g_pBalloon[i].Obj->getPos().x, g_pBalloon[i].Obj->getPos().y + 2.5f);
			}
		}
	}
	//描画
	for (int i = 0; i < 20; ++i)
	{
		if (g_pBalloon[i].Obj != NULL)
		{
			renderSprite(g_pBalloon[i].Obj);
		}

	}


	//オブジェクト描画
	BObjrender();

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
}
