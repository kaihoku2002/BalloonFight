/**
 * ここでそれぞれの画像のUV座標を指定する
 */

#pragma once

#include "stdafx.h"
#include "Common3DType.h"
 

float LeftX = 0.0f;
float RightX = 1.0f;
float OverY = 0.0f;
float DownY = 1.0f;
float UVCntX = 8.0f;
float UVCntY = 12.0f;

//ブロック（柱）
const std::vector <QuadrangleTexel>  kTexelBlockBers = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 3.0f, 1.0f / 1.0f},  {0.0f / 3.0f, 0.0f / 1.0f}, {1.0f / 3.0f, 1.0f / 1.0f}, {1.0f / 3.0, 0.0f / 1.0f}},//地面
	{{1.0f / 3.0f, 1.0f / 1.0f},  {1.0f / 3.0f, 0.0f / 1.0f}, {2.0f / 3.0f, 1.0f / 1.0f}, {2.0f / 3.0, 0.0f / 1.0f}},//柱（中央）
	{{2.0f / 3.0f, 1.0f / 1.0f},  {2.0f / 3.0f, 0.0f / 1.0f}, {3.0f / 3.0f, 1.0f / 1.0f}, {3.0f / 3.0, 0.0f / 1.0f}},//柱（先）
};

//パイプ（ボーナスステージ）
const std::vector <QuadrangleTexel>  kTexelBPipes = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 2.0f, 1.0f / 1.0f},  {0.0f / 2.0f, 0.0f / 1.0f}, {1.0f / 2.0f, 1.0f / 1.0f}, {1.0f / 2.0, 0.0f / 1.0f}},//地面
	{{1.0f / 2.0f, 1.0f / 1.0f},  {1.0f / 2.0f, 0.0f / 1.0f}, {2.0f / 2.0f, 1.0f / 1.0f}, {2.0f / 2.0, 0.0f / 1.0f}},//柱（中央）
};

//パイプ（ボーナスステージ）
const std::vector <QuadrangleTexel>  kTexeltitleballoons = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 4.0f, 1.0f / 1.0f},  {0.0f / 4.0f, 0.0f / 1.0f}, {1.0f / 4.0f, 1.0f / 1.0f}, {1.0f / 4.0, 0.0f / 1.0f}},//地面
	{{1.0f / 4.0f, 1.0f / 1.0f},  {1.0f / 4.0f, 0.0f / 1.0f}, {2.0f / 4.0f, 1.0f / 1.0f}, {2.0f / 4.0, 0.0f / 1.0f}},//柱（中央）
	{{2.0f / 4.0f, 1.0f / 1.0f},  {2.0f / 4.0f, 0.0f / 1.0f}, {3.0f / 4.0f, 1.0f / 1.0f}, {3.0f / 4.0, 0.0f / 1.0f}},//地面
	{{3.0f / 4.0f, 1.0f / 1.0f},  {3.0f / 4.0f, 0.0f / 1.0f}, {4.0f / 4.0f, 1.0f / 1.0f}, {4.0f / 4.0, 0.0f / 1.0f}},//柱（中央）
};

//プレイヤーの画像のUV座標
const std::vector <QuadrangleTexel>  kTexelPlayers = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 8.0f, 1.0f / 5.0f},  {0.0f / 8.0f, 0.0f / 5.0f}, {1.0f / 8.0f, 1.0f / 5.0f}, {1.0f / 8.0, 0.0f / 5.0f}},//風船２個歩行1(1)
	{{1.0f / 8.0f, 1.0f / 5.0f},  {1.0f / 8.0f, 0.0f / 5.0f}, {2.0f / 8.0f, 1.0f / 5.0f}, {2.0f / 8.0, 0.0f / 5.0f}},//風船２個歩行2(2)
	{{2.0f / 8.0f, 1.0f / 5.0f},  {2.0f / 8.0f, 0.0f / 5.0f}, {3.0f / 8.0f, 1.0f / 5.0f}, {3.0f / 8.0, 0.0f / 5.0f}},//風船２個歩行3(3)
	{{3.0f / 8.0f, 1.0f / 5.0f},  {3.0f / 8.0f, 0.0f / 5.0f}, {4.0f / 8.0f, 1.0f / 5.0f}, {4.0f / 8.0, 0.0f / 5.0f}},//風船２個歩行4(4)
	{{4.0f / 8.0f, 1.0f / 5.0f},  {4.0f / 8.0f, 0.0f / 5.0f}, {5.0f / 8.0f, 1.0f / 5.0f}, {5.0f / 8.0, 0.0f / 5.0f}},//風船２個歩行5(5)
	{{5.0f / 8.0f, 1.0f / 5.0f},  {5.0f / 8.0f, 0.0f / 5.0f}, {6.0f / 8.0f, 1.0f / 5.0f}, {6.0f / 8.0, 0.0f / 5.0f}},//風船２個歩行6(6)
	{{6.0f / 8.0f, 1.0f / 5.0f},  {6.0f / 8.0f, 0.0f / 5.0f}, {7.0f / 8.0f, 1.0f / 5.0f}, {7.0f / 8.0, 0.0f / 5.0f}},//風船２個歩行7(7)
	{{7.0f / 8.0f, 1.0f / 5.0f},  {7.0f / 8.0f, 0.0f / 5.0f}, {8.0f / 8.0f, 1.0f / 5.0f}, {8.0f / 8.0, 0.0f / 5.0f}},//風船２個歩行8(8)

	{{0.0f / 8.0f, 2.0f / 5.0f},  {0.0f / 8.0f, 1.0f / 5.0f}, {1.0f / 8.0f, 2.0f / 5.0f}, {1.0f / 8.0, 1.0f / 5.0f}},//風船１個歩行1(9)
	{{1.0f / 8.0f, 2.0f / 5.0f},  {1.0f / 8.0f, 1.0f / 5.0f}, {2.0f / 8.0f, 2.0f / 5.0f}, {2.0f / 8.0, 1.0f / 5.0f}},//風船１個歩行2(10)
	{{2.0f / 8.0f, 2.0f / 5.0f},  {2.0f / 8.0f, 1.0f / 5.0f}, {3.0f / 8.0f, 2.0f / 5.0f}, {3.0f / 8.0, 1.0f / 5.0f}},//風船１個歩行3(11)
	{{3.0f / 8.0f, 2.0f / 5.0f},  {3.0f / 8.0f, 1.0f / 5.0f}, {4.0f / 8.0f, 2.0f / 5.0f}, {4.0f / 8.0, 1.0f / 5.0f}},//風船１個歩行4(12)
	{{4.0f / 8.0f, 2.0f / 5.0f},  {4.0f / 8.0f, 1.0f / 5.0f}, {5.0f / 8.0f, 2.0f / 5.0f}, {5.0f / 8.0, 1.0f / 5.0f}},//風船１個歩行5(13)
	{{5.0f / 8.0f, 2.0f / 5.0f},  {5.0f / 8.0f, 1.0f / 5.0f}, {6.0f / 8.0f, 2.0f / 5.0f}, {6.0f / 8.0, 1.0f / 5.0f}},//風船１個歩行6(14)
	{{6.0f / 8.0f, 2.0f / 5.0f},  {6.0f / 8.0f, 1.0f / 5.0f}, {7.0f / 8.0f, 2.0f / 5.0f}, {7.0f / 8.0, 1.0f / 5.0f}},//風船１個歩行7(15)

	{{0.0f / 8.0f, 3.0f / 5.0f},  {0.0f / 8.0f, 2.0f / 5.0f}, {1.0f / 8.0f, 3.0f / 5.0f}, {1.0f / 8.0, 2.0f / 5.0f}},//風船２個飛行1(16)
	{{1.0f / 8.0f, 3.0f / 5.0f},  {1.0f / 8.0f, 2.0f / 5.0f}, {2.0f / 8.0f, 3.0f / 5.0f}, {2.0f / 8.0, 2.0f / 5.0f}},//風船２個飛行2(17)
	{{2.0f / 8.0f, 3.0f / 5.0f},  {2.0f / 8.0f, 2.0f / 5.0f}, {3.0f / 8.0f, 3.0f / 5.0f}, {3.0f / 8.0, 2.0f / 5.0f}},//風船２個飛行3(18)
	{{3.0f / 8.0f, 3.0f / 5.0f},  {3.0f / 8.0f, 2.0f / 5.0f}, {4.0f / 8.0f, 3.0f / 5.0f}, {4.0f / 8.0, 2.0f / 5.0f}},//風船２個飛行4(19)
	{{4.0f / 8.0f, 3.0f / 5.0f},  {4.0f / 8.0f, 2.0f / 5.0f}, {5.0f / 8.0f, 3.0f / 5.0f}, {5.0f / 8.0, 2.0f / 5.0f}},//風船２個飛行5(20)
	{{5.0f / 8.0f, 3.0f / 5.0f},  {5.0f / 8.0f, 2.0f / 5.0f}, {6.0f / 8.0f, 3.0f / 5.0f}, {6.0f / 8.0, 2.0f / 5.0f}},//風船２個飛行6(21)

	{{0.0f / 8.0f, 4.0f / 5.0f},  {0.0f / 8.0f, 3.0f / 5.0f}, {1.0f / 8.0f, 4.0f / 5.0f}, {1.0f / 8.0, 3.0f / 5.0f}},//風船１個飛行1(22)
	{{1.0f / 8.0f, 4.0f / 5.0f},  {1.0f / 8.0f, 3.0f / 5.0f}, {2.0f / 8.0f, 4.0f / 5.0f}, {2.0f / 8.0, 3.0f / 5.0f}},//風船１個飛行2(23)
	{{2.0f / 8.0f, 4.0f / 5.0f},  {2.0f / 8.0f, 3.0f / 5.0f}, {3.0f / 8.0f, 4.0f / 5.0f}, {3.0f / 8.0, 3.0f / 5.0f}},//風船１個飛行3(24)
	{{3.0f / 8.0f, 4.0f / 5.0f},  {3.0f / 8.0f, 3.0f / 5.0f}, {4.0f / 8.0f, 4.0f / 5.0f}, {4.0f / 8.0, 3.0f / 5.0f}},//風船１個飛行4(25)
	{{4.0f / 8.0f, 4.0f / 5.0f},  {4.0f / 8.0f, 3.0f / 5.0f}, {5.0f / 8.0f, 4.0f / 5.0f}, {5.0f / 8.0, 3.0f / 5.0f}},//風船１個飛行5(26)

	{{0.0f / 8.0f, 5.0f / 5.0f},  {0.0f / 8.0f, 4.0f / 5.0f}, {1.0f / 8.0f, 5.0f / 5.0f}, {1.0f / 8.0, 4.0f / 5.0f}},//死亡1(27)
	{{1.0f / 8.0f, 5.0f / 5.0f},  {1.0f / 8.0f, 4.0f / 5.0f}, {2.0f / 8.0f, 5.0f / 5.0f}, {2.0f / 8.0, 4.0f / 5.0f}},//死亡2(28)
	{{2.0f / 8.0f, 5.0f / 5.0f},  {2.0f / 8.0f, 4.0f / 5.0f}, {3.0f / 8.0f, 5.0f / 5.0f}, {3.0f / 8.0, 4.0f / 5.0f}},//死亡3(29)
	{{3.0f / 8.0f, 5.0f / 5.0f},  {3.0f / 8.0f, 4.0f / 5.0f}, {4.0f / 8.0f, 5.0f / 5.0f}, {4.0f / 8.0, 4.0f / 5.0f}},//ビリビリ(30)
};

 //エネミーの画像のUV座標
const std::vector <QuadrangleTexel>  kTexelEnemys = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{(LeftX = 0.0f) / UVCntX, (DownY = 1.0f) / UVCntY},  {LeftX / UVCntX, (OverY = 0.0f) / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)

	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	
	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)

	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	
	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)

	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)

	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)

	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)

	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)

	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)

	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)

	{{(LeftX = 0.0f) / UVCntX, ++DownY / UVCntY},  {LeftX / UVCntX, ++OverY / UVCntY}, {(RightX = 1.0f) / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
	{{++LeftX / UVCntX, DownY / UVCntY},  {LeftX / UVCntX, OverY / UVCntY}, {++RightX / UVCntX, DownY / UVCntY}, {RightX / UVCntX, OverY / UVCntY}},//風船２個歩行1(1)
};

//水しぶき
const std::vector <QuadrangleTexel>  kTexelEnteringWaters = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 3.0f, 1.0f / 1.0f},  {0.0f / 3.0f, 0.0f / 1.0f}, {1.0f / 3.0f, 1.0f / 1.0f}, {1.0f / 3.0, 0.0f / 1.0f}},//1
	{{1.0f / 3.0f, 1.0f / 1.0f},  {1.0f / 3.0f, 0.0f / 1.0f}, {2.0f / 3.0f, 1.0f / 1.0f}, {2.0f / 3.0, 0.0f / 1.0f}},//2
	{{2.0f / 3.0f, 1.0f / 1.0f},  {2.0f / 3.0f, 0.0f / 1.0f}, {3.0f / 3.0f, 1.0f / 1.0f}, {3.0f / 3.0, 0.0f / 1.0f}},//3
};

//魚
const std::vector <QuadrangleTexel>  kTexelFishs = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 9.0f, 1.0f / 2.0f},  {0.0f / 9.0f, 0.0f / 2.0f}, {1.0f / 9.0f, 1.0f / 2.0f}, {1.0f / 9.0, 0.0f / 2.0f}},//1
	{{1.0f / 9.0f, 1.0f / 2.0f},  {1.0f / 9.0f, 0.0f / 2.0f}, {2.0f / 9.0f, 1.0f / 2.0f}, {2.0f / 9.0, 0.0f / 2.0f}},//2
	{{2.0f / 9.0f, 1.0f / 2.0f},  {2.0f / 9.0f, 0.0f / 2.0f}, {3.0f / 9.0f, 1.0f / 2.0f}, {3.0f / 9.0, 0.0f / 2.0f}},//3
	{{3.0f / 9.0f, 1.0f / 2.0f},  {3.0f / 9.0f, 0.0f / 2.0f}, {4.0f / 9.0f, 1.0f / 2.0f}, {4.0f / 9.0, 0.0f / 2.0f}},//4
	{{4.0f / 9.0f, 1.0f / 2.0f},  {4.0f / 9.0f, 0.0f / 2.0f}, {5.0f / 9.0f, 1.0f / 2.0f}, {5.0f / 9.0, 0.0f / 2.0f}},//5
	{{5.0f / 9.0f, 1.0f / 2.0f},  {5.0f / 9.0f, 0.0f / 2.0f}, {6.0f / 9.0f, 1.0f / 2.0f}, {6.0f / 9.0, 0.0f / 2.0f}},//6
	{{6.0f / 9.0f, 1.0f / 2.0f},  {6.0f / 9.0f, 0.0f / 2.0f}, {7.0f / 9.0f, 1.0f / 2.0f}, {7.0f / 9.0, 0.0f / 2.0f}},//7
	{{7.0f / 9.0f, 1.0f / 2.0f},  {7.0f / 9.0f, 0.0f / 2.0f}, {8.0f / 9.0f, 1.0f / 2.0f}, {8.0f / 9.0, 0.0f / 2.0f}},//8
	{{8.0f / 9.0f, 1.0f / 2.0f},  {8.0f / 9.0f, 0.0f / 2.0f}, {9.0f / 9.0f, 1.0f / 2.0f}, {9.0f / 9.0, 0.0f / 2.0f}},//9

	{{0.0f / 9.0f, 2.0f / 2.0f},  {0.0f / 9.0f, 1.0f / 2.0f}, {1.0f / 9.0f, 2.0f / 2.0f}, {1.0f / 9.0, 1.0f / 2.0f}},//enemy1
	{{1.0f / 9.0f, 2.0f / 2.0f},  {1.0f / 9.0f, 1.0f / 2.0f}, {2.0f / 9.0f, 2.0f / 2.0f}, {2.0f / 9.0, 1.0f / 2.0f}},//enemy2
	{{2.0f / 9.0f, 2.0f / 2.0f},  {2.0f / 9.0f, 1.0f / 2.0f}, {3.0f / 9.0f, 2.0f / 2.0f}, {3.0f / 9.0, 1.0f / 2.0f}},//enemy3
	{{3.0f / 9.0f, 2.0f / 2.0f},  {3.0f / 9.0f, 1.0f / 2.0f}, {4.0f / 9.0f, 2.0f / 2.0f}, {4.0f / 9.0, 1.0f / 2.0f}},//enemy1
	{{4.0f / 9.0f, 2.0f / 2.0f},  {4.0f / 9.0f, 1.0f / 2.0f}, {5.0f / 9.0f, 2.0f / 2.0f}, {5.0f / 9.0, 1.0f / 2.0f}},//enemy2
	{{5.0f / 9.0f, 2.0f / 2.0f},  {5.0f / 9.0f, 1.0f / 2.0f}, {6.0f / 9.0f, 2.0f / 2.0f}, {6.0f / 9.0, 1.0f / 2.0f}},//enemy3
};

//雷弾
const std::vector <QuadrangleTexel>  kTexelThunderBalls = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 5.0f, 1.0f / 1.0f},  {0.0f / 5.0f, 0.0f / 1.0f}, {1.0f / 5.0f, 1.0f / 1.0f}, {1.0f / 5.0, 0.0f / 1.0f}},//1
	{{1.0f / 5.0f, 1.0f / 1.0f},  {1.0f / 5.0f, 0.0f / 1.0f}, {2.0f / 5.0f, 1.0f / 1.0f}, {2.0f / 5.0, 0.0f / 1.0f}},//2
	{{2.0f / 5.0f, 1.0f / 1.0f},  {2.0f / 5.0f, 0.0f / 1.0f}, {3.0f / 5.0f, 1.0f / 1.0f}, {3.0f / 5.0, 0.0f / 1.0f}},//3
	{{3.0f / 5.0f, 1.0f / 1.0f},  {3.0f / 5.0f, 0.0f / 1.0f}, {4.0f / 5.0f, 1.0f / 1.0f}, {4.0f / 5.0, 0.0f / 1.0f}},//3
	{{4.0f / 5.0f, 1.0f / 1.0f},  {4.0f / 5.0f, 0.0f / 1.0f}, {5.0f / 5.0f, 1.0f / 1.0f}, {5.0f / 5.0, 0.0f / 1.0f}},//3
};

//雷
const std::vector <QuadrangleTexel>  kTexelThunders = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
		{{0.0f / 4.0f, 1.0f / 1.0f},  {0.0f / 4.0f, 0.0f / 1.0f}, {1.0f / 4.0f, 1.0f / 1.0f}, {1.0f / 4.0, 0.0f / 1.0f}},//1
		{{1.0f / 4.0f, 1.0f / 1.0f},  {1.0f / 4.0f, 0.0f / 1.0f}, {2.0f / 4.0f, 1.0f / 1.0f}, {2.0f / 4.0, 0.0f / 1.0f}},//2
		{{2.0f / 4.0f, 1.0f / 1.0f},  {2.0f / 4.0f, 0.0f / 1.0f}, {3.0f / 4.0f, 1.0f / 1.0f}, {3.0f / 4.0, 0.0f / 1.0f}},//1
		{{3.0f / 4.0f, 1.0f / 1.0f},  {3.0f / 4.0f, 0.0f / 1.0f}, {4.0f / 4.0f, 1.0f / 1.0f}, {4.0f / 4.0, 0.0f / 1.0f}},//2
};

//雲
const std::vector <QuadrangleTexel>  kTexelClouds = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 3.0f, 1.0f / 1.0f},  {0.0f / 3.0f, 0.0f / 1.0f}, {1.0f / 3.0f, 1.0f / 1.0f}, {1.0f / 3.0, 0.0f / 1.0f}},//1
	{{1.0f / 3.0f, 1.0f / 1.0f},  {1.0f / 3.0f, 0.0f / 1.0f}, {2.0f / 3.0f, 1.0f / 1.0f}, {2.0f / 3.0, 0.0f / 1.0f}},//2
	{{2.0f / 3.0f, 1.0f / 1.0f},  {2.0f / 3.0f, 0.0f / 1.0f}, {3.0f / 3.0f, 1.0f / 1.0f}, {3.0f / 3.0, 0.0f / 1.0f}},//3
};

//泡
const std::vector <QuadrangleTexel>  kTexelBubbles = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 3.0f, 1.0f / 1.0f},  {0.0f / 3.0f, 0.0f / 1.0f}, {1.0f / 3.0f, 1.0f / 1.0f}, {1.0f / 3.0, 0.0f / 1.0f}},//1
	{{1.0f / 3.0f, 1.0f / 1.0f},  {1.0f / 3.0f, 0.0f / 1.0f}, {2.0f / 3.0f, 1.0f / 1.0f}, {2.0f / 3.0, 0.0f / 1.0f}},//2
	{{2.0f / 3.0f, 1.0f / 1.0f},  {2.0f / 3.0f, 0.0f / 1.0f}, {3.0f / 3.0f, 1.0f / 1.0f}, {3.0f / 3.0, 0.0f / 1.0f}},//3
};

//バックグラウンド
const std::vector <QuadrangleTexel>  kTex_BackAnims = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 4.0f, 1.0f / 1.0f},  {0.0f / 4.0f, 0.0f / 1.0f}, {1.0f / 4.0f, 1.0f / 1.0f}, {1.0f / 4.0, 0.0f / 1.0f}},//1
	{{1.0f / 4.0f, 1.0f / 1.0f},  {1.0f / 4.0f, 0.0f / 1.0f}, {2.0f / 4.0f, 1.0f / 1.0f}, {2.0f / 4.0, 0.0f / 1.0f}},//2
	{{2.0f / 4.0f, 1.0f / 1.0f},  {2.0f / 4.0f, 0.0f / 1.0f}, {3.0f / 4.0f, 1.0f / 1.0f}, {3.0f / 4.0, 0.0f / 1.0f}},//3
	{{3.0f / 4.0f, 1.0f / 1.0f},  {3.0f / 4.0f, 0.0f / 1.0f}, {4.0f / 4.0f, 1.0f / 1.0f}, {4.0f / 4.0, 0.0f / 1.0f}},//3
};

//バックグラウンド
const std::vector <QuadrangleTexel>  kTex_bBackAnims = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 4.0f, 1.0f / 1.0f},  {0.0f / 4.0f, 0.0f / 1.0f}, {1.0f / 4.0f, 1.0f / 1.0f}, {1.0f / 4.0, 0.0f / 1.0f}},//1
	{{1.0f / 4.0f, 1.0f / 1.0f},  {1.0f / 4.0f, 0.0f / 1.0f}, {2.0f / 4.0f, 1.0f / 1.0f}, {2.0f / 4.0, 0.0f / 1.0f}},//2
	{{2.0f / 4.0f, 1.0f / 1.0f},  {2.0f / 4.0f, 0.0f / 1.0f}, {3.0f / 4.0f, 1.0f / 1.0f}, {3.0f / 4.0, 0.0f / 1.0f}},//3
	{{3.0f / 4.0f, 1.0f / 1.0f},  {3.0f / 4.0f, 0.0f / 1.0f}, {4.0f / 4.0f, 1.0f / 1.0f}, {4.0f / 4.0, 0.0f / 1.0f}},//3
};

//シンボル
const std::vector<QuadrangleTexel> kTexelSymbol = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 2.0f,1.0f / 1.0f},{0.0f / 2.0f, 0.0f / 1.0f},{1.0f / 2.0f, 1.0f / 1.0f},{1.0f / 2.0f, 0.0f / 1.0f}},
	{{1.0f / 2.0f,1.0f / 1.0f},{1.0f / 2.0f, 0.0f / 1.0f},{2.0f / 2.0f, 1.0f / 1.0f},{2.0f / 2.0f, 0.0f / 1.0f}},
};
//バルーン（ボーナスステージ）
const std::vector<QuadrangleTexel> kTexelBBalloons = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 5.0f, 1.0f / 1.0f},  {0.0f / 5.0f, 0.0f / 1.0f}, {1.0f / 5.0f, 1.0f / 1.0f}, {1.0f / 5.0, 0.0f / 1.0f}},//1
	{{1.0f / 5.0f, 1.0f / 1.0f},  {1.0f / 5.0f, 0.0f / 1.0f}, {2.0f / 5.0f, 1.0f / 1.0f}, {2.0f / 5.0, 0.0f / 1.0f}},//2
	{{2.0f / 5.0f, 1.0f / 1.0f},  {2.0f / 5.0f, 0.0f / 1.0f}, {3.0f / 5.0f, 1.0f / 1.0f}, {3.0f / 5.0, 0.0f / 1.0f}},//3
	{{3.0f / 5.0f, 1.0f / 1.0f},  {3.0f / 5.0f, 0.0f / 1.0f}, {4.0f / 5.0f, 1.0f / 1.0f}, {4.0f / 5.0, 0.0f / 1.0f}},//4
	{{4.0f / 5.0f, 1.0f / 1.0f},  {4.0f / 5.0f, 0.0f / 1.0f}, {5.0f / 5.0f, 1.0f / 1.0f}, {5.0f / 5.0, 0.0f / 1.0f}},//5
};

//UI
 //数字のUV座標
const std::vector <QuadrangleTexel> kTexelNumbers = {
	//   左下        左上       右下         右上
	{{0.8f,1.0f},{0.8f,0.5f},{1.0f,1.0f},{1.0f,0.5f}},   //!<Number0
	{{0.0f,0.5f},{0.0f,0.0f},{0.2f,0.5f},{0.2f,0.0f}},   //!<Number1
	{{0.2f,0.5f},{0.2f,0.0f},{0.4f,0.5f},{0.4f,0.0f}},   //!<Number2
	{{0.4f,0.5f},{0.4f,0.0f},{0.6f,0.5f},{0.6f,0.0f}},   //!<Number3
	{{0.6f,0.5f},{0.6f,0.0f},{0.8f,0.5f},{0.8f,0.0f}},   //!<Number4
	{{0.8f,0.5f},{0.8f,0.0f},{1.0f,0.5f},{1.0f,0.0f}},   //!<Number5
	{{0.0f,1.0f},{0.0f,0.5f},{0.2f,1.0f},{0.2f,0.5f}},   //!<Number6
	{{0.2f,1.0f},{0.2f,0.5f},{0.4f,1.0f},{0.4f,0.5f}},   //!<Number7
	{{0.4f,1.0f},{0.4f,0.5f},{0.6f,1.0f},{0.6f,0.5f}},   //!<Number8
	{{0.6f,1.0f},{0.6f,0.5f},{0.8f,1.0f},{0.8f,0.5f}},   //!<Number9
};

//加算スコア
const std::vector <QuadrangleTexel>  kTexelAddScores = {
	//          左下　　　　　　              左上　　　　　             右下　　　 　              右上
	{{0.0f / 5.0f, 1.0f / 1.0f},  {0.0f / 5.0f, 0.0f / 1.0f}, {1.0f / 5.0f, 1.0f / 1.0f}, {1.0f / 5.0, 0.0f / 1.0f}},//1
	{{1.0f / 5.0f, 1.0f / 1.0f},  {1.0f / 5.0f, 0.0f / 1.0f}, {2.0f / 5.0f, 1.0f / 1.0f}, {2.0f / 5.0, 0.0f / 1.0f}},//2
	{{2.0f / 5.0f, 1.0f / 1.0f},  {2.0f / 5.0f, 0.0f / 1.0f}, {3.0f / 5.0f, 1.0f / 1.0f}, {3.0f / 5.0, 0.0f / 1.0f}},//3
	{{3.0f / 5.0f, 1.0f / 1.0f},  {3.0f / 5.0f, 0.0f / 1.0f}, {4.0f / 5.0f, 1.0f / 1.0f}, {4.0f / 5.0, 0.0f / 1.0f}},//4
	{{4.0f / 5.0f, 1.0f / 1.0f},  {4.0f / 5.0f, 0.0f / 1.0f}, {5.0f / 5.0f, 1.0f / 1.0f}, {5.0f / 5.0, 0.0f / 1.0f}},//5
};