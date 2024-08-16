//----------------------------------------------------------
// ファイル名		：BonusClear.cpp
// 概要				：ボーナスステージクリア画面の処理の関数の定義
// 作成者			：21CU0136 松本賢太
// 更新内容			：2022/03/28 21CU0136松本　作成
//					：2022/03/30 21CU0136松本　アニメーション設定
//----------------------------------------------------------

#include "CActionGameApp.h"
#include "GameResource.h"
#include <Windows.h>

/*
 * ボーナスステージクリア画面の処理を行う部分
 */
void CActionGameApp::procBonusClear()
{
	switch (g_BonusClearPhase)
	{
		case eBegin:
		{
			//g_pPlayer が作成されている時のみ破棄する
			for (int i = 0; i < 2; i++)
			{
				if (g_pPlayer[i] != NULL)
				{
					disposeSprite(g_pPlayer[i]);
					g_pPlayer[i] = NULL;
				}
			}
			//ボーナスクリア画面開始時に行う処理
			procBonusClearBegin();
			//進行状態をメインに変更する
			g_BonusClearPhase = eMain;
		}
		break;
		case eMain:
		{
			//デバッグ用
			if (m_pDirectInput->isPressedOnce(DIK_F))
			{
				PerfectFlag = false;
			}
			//ロードのフラグをリセット
			IsLoad = IsLoad & 0b0111;
			//ボーナスクリア画面のメイン処理
			procBonusClearMain();
		}
		break;
		case eEnd:
		{
			//ロード処理
			IsLoad = IsLoad | 0b0010;
			//ボーナス画面終了時に行う処理
			procBonusClearEnd();
			procPlayEnd();
			//フェーズを戻す
			g_BonusClearPhase = eBegin;
			//再度タイトル画面に来た時に開始から処理を行うためにフェーズを戻しておく
			SetNextGameStatus(g_NextStatusFromBonusClear);
		}
		break;
	}
}

//関数名		:procBonusClearBegin()
//処理内容		:ボーナスクリア画面の開始時に行う処理
//引数			:なし
//戻り値		:なし
void CActionGameApp::procBonusClearBegin()
{
	//獲得スコア計算
	TotalScore = BalloonPoints * BreakBallonCnt; //20をボーナスステージの変数に変換
	//パーフェクトフラグの管理 片方の20をボーナスステージの変数に変換
	if (BreakBallonCnt == 20)
	{
		PerfectFlag = true;
	}

	//画像作成
	if (g_BonusClearBack == NULL)
	{
		g_BonusClearBack = createSprite(Tex_Black);
	}
	if (g_pBounusPerfect == NULL)
	{
		g_pBounusPerfect = createSprite(Tex_BounusPerfect);
	}
	if (g_pPlayer[0] == NULL)
	{
		g_pPlayer[0] = createSprite(Tex_Player,PLAYER_SIZE_X,PLAYER_SIZE_Y);
		g_pPlayer[0]->setPos(-PLAYER_SIZE_X * 5.5f, PLAYER_SIZE_Y * 1.0f);
	}
	if (g_pMultiplicationMark == NULL)
	{
		g_pMultiplicationMark = createSprite(Tex_Symbol, Symbol_SIZE_X, Symbol_SIZE_Y);
		g_pMultiplicationMark->setPos(-Symbol_SIZE_X * 4.5f, Symbol_SIZE_Y * 5.2f);
		g_pMultiplicationMark->setAnimation(0);
	}
	if (g_pEqualSign == NULL)
	{
		g_pEqualSign = createSprite(Tex_Symbol, PlayerScore.Size_X, Symbol_SIZE_Y);
		g_pEqualSign->setPos(Symbol_SIZE_X * 4.0f, Symbol_SIZE_Y * 5.2f);
		g_pEqualSign->setAnimation(1);
	}
	if (g_pPTS == NULL)
	{
		g_pPTS = createSprite(Tex_PTS, 108.0f, 28.0f);
		g_pPTS->setPos(108.0f * 3.5f, 28.0f * 4.5f);
	}
	if (g_pBBalloon == NULL)
	{
		g_pBBalloon = createSprite(Tex_BBalloon, 64.0f, 64.0f);
		g_pBBalloon->setPos(-64.0f * 3.3f, 64.0f * 1.9f);
	}

	//フォント作成
	if (g_BalloonScore == NULL)
	{
		g_BalloonScore = createFont(Tex_Score,3, PlayerScore.Size_X, PlayerScore.Size_Y);
		g_BalloonScore->setPos(-PlayerScore.Size_X * 8.5f, PlayerScore.Size_Y * 4.0f);
	}
	if (g_pGetBalloon == NULL)
	{
		g_pGetBalloon = createFont(Tex_Score, 2, PlayerScore.Size_X, PlayerScore.Size_Y);
		g_pGetBalloon->setPos(-PlayerScore.Size_X * 1.5f, PlayerScore.Size_Y * 4.0f);
	}
	if (g_pTotalScore == NULL)
	{
		g_pTotalScore = createFont(Tex_Score, 4, PlayerScore.Size_X, PlayerScore.Size_Y); //桁数を変数にできたらいい
		g_pTotalScore->setPos(PlayerScore.Size_X * 4.5f, PlayerScore.Size_Y * 4.0f);
	}
}
//関数名		:procBonusClearMain()
//処理内容		:ボーナスクリア画面のメイン処理
//引数			:なし
//戻り値		:なし
void CActionGameApp::procBonusClearMain()
{
	//時間の計算
	++BonusTimeCnt;
	//6秒後に自動で画面移行する
	if (BonusTimeCnt > 60 * 6)
	{
		//タイトルにステータスを移行する準備をする
		g_BonusClearPhase = eEnd;
		g_NextStatusFromBonusClear = ePlaying;
		//フェーズ1に移行
		PhaseNum = 1;
		Block.Count = BlockPos[PhaseNum - 1].ConnectCount[0] + BlockPos[PhaseNum - 1].ConnectCount[1] + BlockPos[PhaseNum - 1].ConnectCount[2] + BlockPos[PhaseNum - 1].ConnectCount[3] + BlockPos[PhaseNum - 1].ConnectCount[4];
		RightBlock.Count = BlockPos[PhaseNum - 1].Count;
		LeftBlock.Count = BlockPos[PhaseNum - 1].Count;
		Cloud.Count = CloudPos[PhaseNum - 1].Count;
	}

	//3秒後にスコア加算 20をボーナスステージの変数に変換 右の3をボーナスステージフェーズの変数に変換
	if (BonusTimeCnt > 60 * 3 && getballoonCnt / 3 < BreakBallonCnt)
	{
		//ボーナスポイント
		if (g_pPoint && BonusTimeCnt % 3 == 0)
		{
			disposeSound(g_pPoint);
			g_pPoint = NULL;
		}
		if (!g_pPoint)
		{
			// 第2引数：ループ設定
			// ループしないので、falseを設定
			g_pPoint = createSound(Point, false);
		}
		//繰り返し分を計算
		++getballoonCnt;
		//バルーン獲得数分加算
		PlayerScore.Score += 100;
		//減算
		TotalScore -= 100;
	}
	//計算が終わったタイミングでフラグをオンにする 20をボーナスステージの変数に変換 3をボーナスステージフェーズの変数に変換
	else if (getballoonCnt == BreakBallonCnt * 3)
	{
		ScoreFlag = true;
		getballoonCnt += 1;
	}
	//パーフェクト時の計算 プラスするスコアをフェーズによって変える
	if (PerfectFlag != false && ScoreFlag != false)
	{
		//ボーナスポイント
		if (g_pPoint)
		{
			disposeSound(g_pPoint);
			g_pPoint = NULL;
		}
		if (!g_pPoint)
		{
			// 第2引数：ループ設定
			// ループしないので、falseを設定
			g_pPoint = createSound(Point, false);
		}
		//1秒止める
		Sleep(1000);
		PlayerScore.Score += 10000;
		ScoreFlag = false;
	}
	//上限
	if (PlayerScore.Score > 999999)
	{
		PlayerScore.Score = 999999;
	}

	//最初から描画
	//画像描画
	if (g_BonusClearBack != NULL)
	{
		renderSprite(g_BonusClearBack);
	}
	if (g_pPlayer[0] != NULL)
	{
		renderSprite(g_pPlayer[0]);
	}
	if (g_pBBalloon != NULL)
	{
		renderSprite(g_pBBalloon);
	}
	//UIの描画
	UIrender();

	//0.5秒後に描画
	if (BonusTimeCnt > 30 * 1)
	{
		//画像描画
		if (g_pMultiplicationMark != NULL)
		{
			renderSprite(g_pMultiplicationMark);
		}
		//フォント描画
		if (g_pGetBalloon != NULL)
		{
			renderFont(g_pGetBalloon, BreakBallonCnt); //20の部分をボーナスステージで使用する変数に変更
		}
	}
	//0.95秒後に描画
	if ((float)BonusTimeCnt > 30.0f * 1.9f)
	{
		//アニメーションセット
		if (g_pBBalloon != NULL)
		{
			g_pBBalloon->setAnimation(4);
		}
	}
	//1秒後に描画、破棄
	if (BonusTimeCnt > 30 * 2)
	{
		//画像破棄
		if (g_pBBalloon != NULL)
		{
			disposeSprite(g_pBBalloon);
			g_pBBalloon = NULL;
		}
		//画像描画
		if (g_pEqualSign != NULL)
		{
			renderSprite(g_pEqualSign);
		}
		if (g_pPTS != NULL)
		{
			renderSprite(g_pPTS);
		}
		//フォント描画
		if (g_pTotalScore != NULL)
		{
			renderFont(g_pTotalScore, TotalScore);
		}
		if (g_BalloonScore != NULL)
		{
			renderFont(g_BalloonScore, BalloonPoints);
		}
	}
	//1.5秒後かつパーフェクト時に描画
	if (PerfectFlag != false && BonusTimeCnt > 30 * 3)
	{
		if (g_pBounusPerfect != NULL)
		{
			if (!g_pPerfect && BonusTimeCnt < 30 * 4)
			{
				// 第2引数：ループ設定
				// ループしないので、falseを設定
				g_pPerfect = createSound(Perfect, false);
			}
			renderSprite(g_pBounusPerfect);
		}
	}
	SoundPlay();
	SoundDispose();
}

//関数名		:procBonusClearEnd()
//処理内容		:ボーナスクリア画面の終了時に行う処理
//引数			:なし
//戻り値		:なし
void CActionGameApp::procBonusClearEnd()
{
	//画像の破棄
	if (g_BonusClearBack != NULL)
	{
		disposeSprite(g_BonusClearBack);
		g_BonusClearBack = NULL;
	}
	if (g_pBounusPerfect != NULL)
	{
		disposeSprite(g_pBounusPerfect);
		g_pBounusPerfect = NULL;
	}
	if (g_pPlayer[0] != NULL)
	{
		disposeSprite(g_pPlayer[0]);
		g_pPlayer[0] = NULL;
	}
	if (g_pPlayer[1] != NULL)
	{
		disposeSprite(g_pPlayer[1]);
		g_pPlayer[1] = NULL;
	}
	if (g_pMultiplicationMark != NULL)
	{
		disposeSprite(g_pMultiplicationMark);
		g_pMultiplicationMark = NULL;
	}
	if (g_pEqualSign != NULL)
	{
		disposeSprite(g_pEqualSign);
		g_pEqualSign = NULL;
	}
	if (g_pPTS != NULL)
	{
		disposeSprite(g_pPTS);
		g_pPTS = NULL;
	}

	//フォント破棄
	if (g_BalloonScore != NULL)
	{
		disposeFont(g_BalloonScore);
		g_BalloonScore = NULL;
	}
	if (g_pGetBalloon != NULL)
	{
		disposeFont(g_pGetBalloon);
		g_pGetBalloon = NULL;
	}
	if (g_pTotalScore != NULL)
	{
		disposeFont(g_pTotalScore);
		g_pTotalScore = NULL;
	}


	//値リセット
	getballoonCnt = 0;
	BonusTimeCnt = 0;
	PerfectFlag = false;
	ScoreFlag = false;
	BonusON = false;
	PhaseNum = 1;

	for (int i = 0; i < Balloon.Count; ++i)
	{
		g_pBalloon[i].BalloonCourse = 3;
		g_pBalloon[i].BalloonSpeed = 0.0f;
		g_pBalloon[i].inPipe = true;
		g_pBalloon[i].HIt = false;
	}
	NowballoonCnt = 0;
	BreakBallonCnt = 0;
	balloonCnt = 0;
	DeathCoolFlag = true;

	//破棄
	BObjDispose();
	SoundDispose();              //音声
}