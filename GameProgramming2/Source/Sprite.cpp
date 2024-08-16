#include "stdafx.h"
#include "CActionGameApp.h"
#include "GameResource.h"
#include "UV.h"


/**
 * 関数名 : createSprite()
 * 処理内容 : 指定されたパスにある画像を、指定されたサイズで作成する
 * 引数 :	path_		画像のあるパス
 *			width_		作成する画像の幅
 *			height_		作成する画像の高さ
 * 戻り値 : 作成した画像を管理するオブジェクト
 */
CPicture* CActionGameApp::createSprite (LPCWSTR path_, float width_, float height_)
{
	vector <QuadrangleTexel>  singleTexels = {
	QuadrangleTexel{ { 0, 1.0f },{ 0, 0.0f },{ 1, 1.0f },{ 1, 0.0f } }	// 指定するUV座標が一つの配列
	};
	XMFLOAT2 spriteSize = { width_, height_};
	CPicture* object = NULL;

	//プレイヤー
	if (path_ == Tex_Player)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelPlayers);            //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_EnteringWater)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelEnteringWaters);      //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_Thunder)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelThunders);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_ThunderBall)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelThunderBalls);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_Bubble)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelBubbles);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_Fish)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelFishs);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_Cloud)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelClouds);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_Enemy1)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelEnemys);               //!<指定するUＶ座標の配列
	}
	else if(path_ == Tex_BackAnim)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTex_BackAnims);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_bBackAnim)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTex_bBackAnims);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_BlockBer)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelBlockBers);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_BPipe)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelBPipes);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_titleballoon)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexeltitleballoons);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_Symbol)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelSymbol);               //!<指定するUＶ座標の配列
	}
	else if (path_ == Tex_BBalloon)
	{
		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //!<スプライトの位置
			spriteSize,                //!<スプライトサイズ
			kTexelBBalloons);               //!<指定するUＶ座標の配列
	}
	else
	{

		object = CPicture::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f, 0.0f, 0.0f, 0.0f },	// スプライトの位置
			spriteSize,					// スプライトのサイズ
			singleTexels);				// 指定するUV座標の配列
	}

	return object;
}

CFont* CActionGameApp::createFont(LPCWSTR path_, int digits_, float width_, float height_)
{
	XMFLOAT2 spriteSize = { width_, height_ };
	CFont* objects = NULL;

	if (path_ == Tex_Addscore)
	{
		objects = CFont::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //スプライトの位置
			spriteSize,                //スプライトサイズ
			kTexelAddScores,          //指定するUV座標の配列
			digits_);                  //桁数
	}
	else
	{
		objects = CFont::create(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_AlphaHLSL, path_,
			{ 0.0f,0.0f,0.0f,0.0f },   //スプライトの位置
			spriteSize,                //スプライトサイズ
			kTexelNumbers,          //指定するUV座標の配列
			digits_);                  //桁数
	}

	return objects;
}
