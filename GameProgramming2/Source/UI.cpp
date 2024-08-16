//----------------------------------------------
// ファイル名 ：UI.cpp
// 概要　　　 ：UIの生成・配置・描画・破棄の処理
// 　　　　　 ：UIの値の制御
// 作者　　　 ：21Cu0312 河合 奏
// 更新内容   ：2022/03/09 21CU0312 河合 奏 作成
// 　　　　　 ：2022/03/02 21CU0312 河合 奏 UICreate()、UIrender()、UIDispose()、UIsetPos()を追加
//------------------------------------------------


#include "CActionGameApp.h"
#include "GameResource.h"

//UIの画像を作成
void CActionGameApp::UIcreate()
{
	//プレイヤーに関するUI
	//スコア
	PlayerScore.g_pCategory = createSprite(Tex_I_UI, PlayerScore.Size_X, PlayerScore.Size_Y);
	PlayerScore.g_pScore = createFont(Tex_Score, 6 , PlayerScore.Size_X, PlayerScore.Size_Y);
	
	//残機
	for (int i = 0; i < RemainCount; ++i)
	{
		g_pRemain[i] = createSprite(Tex_Remain,RemainSize_X, RemainSize_Y);
	}

	//トップスコア
	TopScore.g_pCategory = createSprite(Tex_Top_UI, TopScore.Size_X, PlayerScore.Size_Y);
	TopScore.g_pScore = createFont(Tex_Score, 6, PlayerScore.Size_X, PlayerScore.Size_Y);

	Phase_UI  = createSprite(Tex_PHASE_UI, PhaseSize_X, PhaseSize_Y);
	PhaseNum_UI = createFont(Tex_Score, 2, PlayerScore.Size_X, PlayerScore.Size_Y);

}

//UIの画像を描画
void CActionGameApp::UIrender()
{
	//プレイヤーに関するUI
	//スコア
 	renderSprite(PlayerScore.g_pCategory);
	renderFont(PlayerScore.g_pScore, PlayerScore.Score);

	//残機
	for (int i = 0; i < NowRemainCount; ++i)
	{
		renderSprite(g_pRemain[i]);
	}

	//トップスコア
	renderSprite(TopScore.g_pCategory);
	renderFont(TopScore.g_pScore,TopScore.Score);

	//フェイズ
	if (PhaseRenderCnt < 210)
	{
		++PhaseRenderCnt;
		if (PhaseRenderCnt % 60 < 30)
		{
			renderSprite(Phase_UI);
			renderFont(PhaseNum_UI, PhaseNum);
		}
	}
}

//UIの画像を破棄
void CActionGameApp::UIdispose()
{
	//プレイヤーに関するUI
	//スコア
	disposeSprite(PlayerScore.g_pCategory);
	disposeFont(PlayerScore.g_pScore);

	//残機
	for (int i = 0; i < RemainCount; ++i)
	{
		disposeSprite(g_pRemain[i]);
	}

	//トップスコア
	disposeSprite(TopScore.g_pCategory);
	disposeFont(TopScore.g_pScore);

	//フェイズ
	disposeSprite(Phase_UI);
	disposeFont(PhaseNum_UI);
}

//UIの配置
void CActionGameApp::UIsetPos()
{
	//プレイヤーに関するUI
	//スコア
	PlayerScore.g_pCategory->setPos(WINDOW_LEFT + (24.0f * 4.0f) + (PlayerScore.Size_X / 2.0f),WINDOW_TOP - (PlayerScore.Size_Y / 2.0f) - 64.0f);
	PlayerScore.g_pScore->setPos(WINDOW_LEFT + (24.0f * 4.0f) + (PlayerScore.Size_X / 2.0f), WINDOW_TOP - (PlayerScore.Size_Y / 2.0f) - 60.0f);

	//残機
	for (int i = 0; i < RemainCount; ++i)
	{
		if (g_pRemain[i] != NULL)
		{
			g_pRemain[i]->setPos(WINDOW_LEFT + (58.0f * 4.0f) + PlayerScore.Size_X + (RemainSize_X / 2.0f) - (PlayerScore.Size_X * (float)i), WINDOW_TOP - PlayerScore.Size_Y - 80.0f);
		}
	}

	//トップスコア
	TopScore.g_pCategory->setPos(-(16.0f * 4.0f) - (TopScore.Size_X / 2.0f), WINDOW_TOP - (PlayerScore.Size_Y / 2.0f) - 64.0f);
	TopScore.g_pScore->setPos(-(16.0f * 4.0f) - (PlayerScore.Size_X / 2.0f) + 4.0f, WINDOW_TOP - (PlayerScore.Size_Y / 2.0f) - 60.0f);

	//フェイズ
	Phase_UI->setPos(TopScore.Size_X - (PhaseSize_X / 2.0f), WINDOW_TOP - PlayerScore.Size_Y - (PhaseSize_Y / 2.0f) - 64.0f);
	PhaseNum_UI->setPos((PlayerScore.Size_X * 1.5f), WINDOW_TOP - PlayerScore.Size_Y - (PlayerScore.Size_Y / 2.0f) - 60.0f);
}

//スコアの処理
void CActionGameApp::ScoreSet(int SetNum)
{
	switch (SetNum)
	{
		//白
		case 0:
			PlayerScore.Score += 500;
			break;
		case 1:
			PlayerScore.Score += 1000;
			break;
		case 2:
			PlayerScore.Score += 750;
			break;
		//緑
		case 3:
			PlayerScore.Score += 750;
			break;
		case 4:
			PlayerScore.Score += 1500;
			break;
		case 5:
			PlayerScore.Score += 1000;
			break;
		//赤
		case 6:
			PlayerScore.Score += 1000;
			break;
		case 7:
			PlayerScore.Score += 2000;
			break;
		case 8:
			PlayerScore.Score += 1500;
			break;
	}

	//上限
	if (PlayerScore.Score > 999999)
	{
		PlayerScore.Score = 999999;
	}
}

//残機の処理
void CActionGameApp::RemainSet()
{
	--NowRemainCount;
}

//加算スコアの処理
void CActionGameApp::AddScoreSet(CPicture* g_pPicture, int getScore)
{
	for (int i = 0; i < AddScoreIndex; ++i)
	{
		if (g_pAddScore[i] == NULL)
		{
			switch (getScore)
			{
				//白
			case 0:
				g_pAddScore[i] = createFont(Tex_Addscore,3,AddScoreSize_X, AddScoreSize_Y);
				g_pAddScore[i]->setPos(g_pPicture->getPos().x - 32.0f, g_pPicture->getPos().y + 32.0f);
				AddScore[i] = 244;
				break;
			case 1:
				g_pAddScore[i] = createFont(Tex_Addscore, 4, AddScoreSize_X, AddScoreSize_Y);
				g_pAddScore[i]->setPos(g_pPicture->getPos().x- 32.0f, g_pPicture->getPos().y + 32.0f);
				AddScore[i] = 444;
				break;
			case 2:
				g_pAddScore[i] = createFont(Tex_Addscore, 3, AddScoreSize_X, AddScoreSize_Y);
				g_pAddScore[i]->setPos(g_pPicture->getPos().x - 32.0f, g_pPicture->getPos().y + 32.0f);
				AddScore[i] = 324;
				break;
				//緑
			case 3:
				g_pAddScore[i] = createFont(Tex_Addscore, 3, AddScoreSize_X, AddScoreSize_Y);
				g_pAddScore[i]->setPos(g_pPicture->getPos().x - 32.0f, g_pPicture->getPos().y + 32.0f);
				AddScore[i] = 324;
				break;
			case 4:
				g_pAddScore[i] = createFont(Tex_Addscore, 4, AddScoreSize_X, AddScoreSize_Y);
				g_pAddScore[i]->setPos(g_pPicture->getPos().x - 32.0f, g_pPicture->getPos().y + 32.0f);
				AddScore[i] = 244;
				break;
			case 5:
				g_pAddScore[i] = createFont(Tex_Addscore, 4, AddScoreSize_X, AddScoreSize_Y);
				g_pAddScore[i]->setPos(g_pPicture->getPos().x - 32.0f, g_pPicture->getPos().y + 32.0f);
				AddScore[i] = 444;
				break;
				//赤
			case 6:
				g_pAddScore[i] = createFont(Tex_Addscore, 4, AddScoreSize_X, AddScoreSize_Y);
				g_pAddScore[i]->setPos(g_pPicture->getPos().x - 32.0f, g_pPicture->getPos().y + 32.0f);
				AddScore[i] = 444;
				break;
			case 7:
				g_pAddScore[i] = createFont(Tex_Addscore, 4, AddScoreSize_X, AddScoreSize_Y);
				g_pAddScore[i]->setPos(g_pPicture->getPos().x - 32.0f, g_pPicture->getPos().y + 32.0f);
				AddScore[i] = 1444;
				break;
			case 8:
				g_pAddScore[i] = createFont(Tex_Addscore, 4, AddScoreSize_X, AddScoreSize_Y);
				g_pAddScore[i]->setPos(g_pPicture->getPos().x - 32.0f, g_pPicture->getPos().y + 32.0f);
				AddScore[i] = 244;
				break;
			}
			break;
		}
	}
	
}