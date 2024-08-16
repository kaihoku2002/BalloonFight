//----------------------------------------------------------
// ファイル名		：Load.cpp
// 概要				：ゲームロード処理の関数の定義
// 作成者			：21CU0136 松本賢太
// 更新内容			：2022/03/13 21CU0136松本　作成
//					  2022/03/15 21CU0136松本　すべて書き換え
//----------------------------------------------------------
#include "CActionGameApp.h"
#include "GameResource.h"
/*
 * ゲームロード処理を行う部分
 */
void CActionGameApp::procGameLoad()
{
	//タイトルロード
	if (IsLoad & 0b0001)
	{
		BlackScreenCreate();
	}
	//インゲームロード
	else if (IsLoad & 0b0010)
	{
		BlackScreenCreate();
	}
	//ゲームオーバーロード
	else if (IsLoad & 0b0100)
	{
		//--------------------------------------
		// playの画面をもう一度描画する
		//------------------------------------
		//背景の描画
		Backrender();

		//UIの描画
		UIrender();

		procPlayMain_procEnemy();
		////プレイヤーの画像は最初は0だけ作成、表示する
		//for (int i = 0; i < 2; i++)
		//{
		//	if (g_pPlayer[i] != NULL)
		//	{
		//		renderSprite(g_pPlayer[i]);
		//	}
		//}

		//オブジェクトの描画
		ThunderRender();
		Objrender();
		//----------------------------------------------------------------------------------
	}
	//ゲームクリアロード
	else if (IsLoad & 0b1000)
	{
		//--------------------------------------
		// playの画面をもう一度描画する
		//------------------------------------
		//背景の描画
		if (BonusON == true)
		{
			BBackrender();
		}
		else
		{
			Backrender();
		}
		
		//UIの描画
		UIrender();

		if (BonusON != true)
		{
			procPlayMain_procEnemy();
		}

		//プレイヤーの画像は最初は0だけ作成、表示する
		for (int i = 0; i < 2; i++)
		{
			if (g_pPlayer[i] != NULL)
			{
				renderSprite(g_pPlayer[i]);
			}
		}

		//オブジェクトの描画
		if (BonusON == true)
		{
			BObjrender();
		}
		else
		{
			ThunderRender();
			Objrender();
		}
		//----------------------------------------------------------------------------------
	}
	//黒いスクリーンを削除する
	else
	{
		if (g_Black != NULL)
		{
			disposeSprite(g_Black);
			g_Black = NULL;
		}
	}
}

/*
 * ゲームロード処理の黒いスクリーンの処理を行う部分
 */
void CActionGameApp::BlackScreenCreate()
{
	if (g_Black == NULL)
	{
		g_Black = createSprite(Tex_Black);
	}
	//画像が作成されていたら描画する
	if (g_Black != NULL)
	{
		renderSprite(g_Black);
	}
}