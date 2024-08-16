/**
* @file CActionGameApp.h
* @author 織戸　喜隆
* @date 日付（2017.02.14）
*/
#pragma once

#include "stdafx.h"
#include "CApplication.h"
#include "CPicture.h"
#include "MediaResource.h"
#include "UVAnimation.h"
#include "CFont.h"
// --------------------------------------------
// 枠内は細田弥卯が記述（2021_09_29）
#include "CSound.h"
// --------------------------------------------

struct Obj
{
	int Count;
	const float Size_X;
	const float Size_Y;
};

struct StageObjPos
{
	const int Count;
	const int ConnectCount[5];
	const float PosX[5];
	const float PosY[5];
};

class CActionGameApp :
	public CApplication
{
	typedef CApplication super;
private:
	int m_activeEnemies										= 0;

	CPicture* createSprite(LPCWSTR path_, float width_ = WINDOW_WIDTH, float height_ = WINDOW_HEIGHT);
	void renderSprite( CPicture* object);
	void renderSprite(CPicture* object, XMFLOAT3 color);
	void renderSprite(CPicture* object, float r, float g, float b);
	void renderSprite(CPicture* object, XMFLOAT4 color);
	void disposeSprite( CPicture* object);
	CFont* createFont(LPCWSTR path_, int digits_, float width_, float height_);
	void renderFont(CFont* object, int num_);
	void disposeFont(CFont* object);
	bool createSpaceship(void);
	void initCameraInfo();
	void doOpenning();
	void doPlaying();
	void doGameClear();
	void doGameOver();
	void doEnding();

	void procTitle();
	void procGame();
	void procClear();
	void procGameOver();

	// --------------------------------------------
	// 枠内は細田弥卯が記述（2021_09_29）

	CSound* createSound(const char* filePath_, const bool loop_ = false);
	void PlaySourceSound(CSound* const objects);
	void disposeSound(CSound* const objects);
	void StopSourceSound(CSound* const objects);
	// --------------------------------------------

	// 課題用関数
	void procTitleBegin();
	void procTitleMain();
	void procTitleEnd();
	void procPlayBegin();
	void procPlayMain();
	void procPlayEnd();
	

public:
	CActionGameApp();
	~CActionGameApp();
	void render(XMFLOAT4X4 matView, XMFLOAT4X4 matProj);
	void release();

private:



	//-----------------------------------------------------------
	//UI関連
private:
	//変数宣言
	struct UI
	{
		int Score;
		CPicture* g_pCategory;
		CFont* g_pScore;
		float Size_X;
		float Size_Y;
	};

	//---------------------------------------------------
	//プレイヤーに関するUI
	//スコア
	UI PlayerScore
	{
		000000,
		NULL,
		NULL,
		32.0f,
		32.0f,
	};
	//残機
#define RemainCount 2
	CPicture* g_pRemain[RemainCount] = { NULL,NULL };
	int NowRemainCount = RemainCount;
	float RemainSize_X = 16.0f;
	float RemainSize_Y = 24.0f;
	//---------------------------------------------------

	//---------------------------------------------------
	//トップスコアのUI
	UI TopScore
	{
		0,
		NULL,
		NULL,
		64.0f,
		32.0f,
	};
	//---------------------------------------------------

	//加算スコア
#define AddScoreIndex 6
	CFont* g_pAddScore[AddScoreIndex] = { NULL,NULL, NULL, NULL, NULL, NULL };
	const float AddScoreSize_X = 16.0f;
	const float AddScoreSize_Y = 32.0f;
	int AddScore[AddScoreIndex] = { 0,0,0,0,0,0 };
	int AddScoreCnt[AddScoreIndex] = { 0,0,0,0,0,0 };

	//---------------------------------------------------
	//フェイズ
	CPicture* Phase_UI = NULL;
	const float PhaseSize_X = 192.0f;
	const float PhaseSize_Y = 32.0f;
	CFont* PhaseNum_UI = NULL;
	int PhaseNum = 1;
	int PhaseRenderCnt = 0;

	//---------------------------------------------------
	//関数宣言
	void UIcreate();       //UIの画像を作成
	void UIrender();       //UIの画像を描画
	void UIdispose();      //UIの画像を破棄
	void UIsetPos();       //UIの配置
	void AddScoreSet(CPicture* g_pPicture, int getScore);    //加算スコアの表示・設置
	void ScoreSet(int SetNum);       //スコアの処理
	void RemainSet();      //残機の処理
	//---------------------------------------------------
//-----------------------------------------------------------



//プレイヤー関連-------------------------------------------
	//プレイヤーの画像を管理する変数
	CPicture* g_pPlayer[2] = { NULL,NULL };

	//プレイヤーの表示サイズ
	const float PLAYER_SIZE_X = 64.0f;
	const float PLAYER_SIZE_Y = 128.0f;

	//フレームカウンタ
	int FlameCnt = 0;

	//今の風船の数
	int BalloonCount = 2;

	void procPlayMain_movePlayer();     //プレイヤーの移動処理
	void procPlayMain_BothEnds();		//画面橋の処理
//---------------------------------------------------------

//プレイヤーの縦移動処理関連-------------------------------
	//プレイヤーのジャンプ力
	float g_pJumpRise = 0.0f;
	//プレイヤーのジャンプの力 押していくたびに0.1ずつ増えていく
	float g_pJumpPower = 0.0f;
	//プレイヤーの最大上昇量
	float g_pMaxRise = 1.0f;

	//プレイヤーが地面に着地しているかのフラグ
	//trueなら着地している。falseなら着地していない
	bool PlayerLanding = false;

	//プレイヤーがどちら方向に移動していたかを保存しておく変数
	//trueなら右移動、falseなら左移動
	bool WidthSwitch = NULL;

	//落下速度
	float Gravity = 0.0f;

	//MAXの重力量（下降速度）4.0fより速く落下しない
	const float MaxGravity = 4.0f;
	//---------------------------------------------------------

	//プレイヤーの横移動処理関連-------------------------------
	//プレイヤーの移動速度
	float g_playerMoveSpeed = 0.0f;
	float g_pRunSpeed = 0.0f;
	//プレイヤーの空中移動速度
	float g_pPlayerFlySpeed = 0.0f;
	//---------------------------------------------------------


	//画面端の処理関連-----------------------------------------

			//どちらの画像のプレイヤーが表示されているかを保存するための変数
			//メインの画像になっているか
	int PlayerNum = 0;

	//---------------------------------------------------------


	private:
	//-------------------------------------------------------
	//Enemy関連
	//関数宣言
	void procPlayMain_EnemyCreate(); //エネミーの作成
	void procPlayMain_procEnemy();   //エネミーの描画
	void procPlayMain_EnemyDispose();//エネミーの破棄
	void procPlayMain_EnemyBothEnd();//エネミーの画面端処理
	void procPlayMain_EnemyStatus();

	//変数宣言
	//エネミーの情報を纏める構造体
	struct Enemy
	{
		//画像管理用
		CPicture* obj;
		//エネミーの初期座標
		XMFLOAT2 beginPos;
		//画面端の処理用のバージョン　０：常に画面に表示されている方　１：反対側に出る方
		int enemyVer = 0;
		//画面端にいるかのフラグ
		bool NowEdge = false;
		//エネミーの移動した座標量
		float MovedPos = 0.0f;
		//エネミーとプレイヤーの距離を保存する変数
		XMFLOAT4 PlayerDistance;
		//エネミーの飛行速度
		float g_pEnemyFlySpeed_X = -1.5f;
		float g_pEnemyFlySpeed_Y = 1.5f;

		//エネミーとプレイヤーを繋ぐ直線
		float g_pPlayerEnemyLine;
		//エネミーが移動するライン
		float g_pEnemyMoveLine;

		//エネミーの行動パターン
		int pattern;

		XMFLOAT4 enemyPos;

		XMFLOAT4 DirectionPos;

		//落下時の動きを左右反転する際にも使用
		int EnemyCourse = 3;

		//エネミーが落下中にどれだけ一方の方向に移動したか
		int EnemyFall = 0;

		//一定量移動したら落下する向きを逆にする
		float EnemyFallSpeed = 0.0f;

		//エネミーのステータスを管理する変数
		//０が空中、１が落下中、２が着地、３がゲームが始まって最初に風船をいれる時、４が消滅
		int EnemyStatus = 3;

		//エネミーのレベルを管理する変数（ステータスが２の時に風船を膨らませて復活する際に１増やす　　レベルは０，１，２の三種類）
		//０が白（雑魚）、１が緑（普通）、２が赤（エース機）
		//最初からエネミーのレベルが０ではないエネミーに関しては作成のタイミングとかで代入すればよいだろう
		int EnemyLevel = 0;

		//エネミーがふうせんを膨らませて復活するまでにかかる時間の乱数を保存しておく変数
		float EnemyReturn_Num = 0.0;

		////エネミーが着地しているか
		//bool EnemyLanding = NULL;

		//エネミーの最高速度
		float  g_pEnemyMaxSpeed_X;
		float  g_pEnemyMaxSpeed_Y;

		//エネミーのレベルのよって速度を調整する値
		double SpeedMagnification = 1.0;

		//エネミーの今いるエリアを管理する変数
		//0：左上　1：中央上　2：右上　3：左下　4：中央下　5：右下
		int EnemyArea;

		//フレームカウンタ
		int flameCnt[2] = {0, 0};
	};
	
	//エネミーのサイズ
	float ENEMY_SIZE_X = 64.0f;
	float ENEMY_SIZE_Y = 128.0f;
	
	//エネミーの数
	#define ENEMY_OBJECT_COUNT  10
	
	//敵の情報を管理する変数
	Enemy g_enemyObjs[ENEMY_OBJECT_COUNT] =
	{
		{NULL,XMFLOAT2((0.0f - 112.0f),-32.0f),0},		//0
		{NULL,XMFLOAT2((0.0f - 112.0f),-32.0f),1},		//1
		{NULL,XMFLOAT2(0.0f ,-32.0f),0},				//2
		{NULL,XMFLOAT2(0.0f ,-32.0f),1},				//3
		{NULL,XMFLOAT2((0.0f + 112.0f),-32.0f),0},		//4
		{NULL,XMFLOAT2((0.0f + 112.0f),-32.0f),1},		//5
		{NULL,XMFLOAT2((0.0f + 112.0f),-42.0f),0},		//6
		{NULL,XMFLOAT2((0.0f + 112.0f),-42.0f),1},		//7
		{NULL,XMFLOAT2((0.0f + 112.0f),-42.0f),0},		//8
		{NULL,XMFLOAT2((0.0f + 112.0f),-42.0f),1},		//9
	};
	
	//エネミーが落下する時間を計測する変数
	int EnemyFallTime = 100;
	
	//エネミーの最高速度
	float g_pEnemyFlyMaxSpeed = 3.0f;
	
	//エネミーが陸地に居るかの判定
	//trueなら着地している。falseなら浮遊している
	bool g_pEnemyLanding = NULL;

	//エネミーの移動量が下記の値を超えたらプレイヤーの座標を取得する
	double GetPlayerPos = 1.0;

	XMFLOAT4 enemyPos = { 0.0f,300.0f,0.0f,0.0f };
	XMFLOAT4 PlayerPos = { 0.0f,0.0f,0.0f,0.0f };

	//下記のフレーム数を超えたらプレイヤーの座標を再取得する
	int GetPos = 180;
	//エネミーが入水しないように調整する為の値
	float EnemyNotInWater = -230.0f;


	//現在のエリア判定のための値
	float AreaLineLeft = WINDOW_WIDTH / 3 - WINDOW_WIDTH / 2;
	float AreaLineRight = -WINDOW_WIDTH / 3 + WINDOW_WIDTH / 2;
	float AreaLineUnder = WINDOW_HEIGHT / 3 - WINDOW_HEIGHT / 2;
	float AreaLineOver = -WINDOW_HEIGHT / 3 + WINDOW_HEIGHT / 2;
	//------------------------------------------------------------

	//------------------------------------------------------------
	//Fish関連
	//関数宣言
	void procPlayMain_moveFish();     //魚の移動処理
	void procPlayMain_AlgorithmFish(); //魚のアルゴリズム
	//変数宣言
	CPicture* g_pFish = NULL;
	//魚とプレイヤーの当たり判定を変える変数
	float ActiveArea_Num = 8.0f;		//魚が出現する幅を変えるための変数
	float KillArea_Num = 16.0f;			//魚がプレイヤーを殺せる幅を変えるための変数
	float FishPos = 0.0f;
	const float FISH_SIZE_X = 64.0f;
	const float FISH_SIZE_Y = 128.0f;
	//魚の横移動を反転させるための変数(trueなら左に移動、falseなら右に移動)
	bool Movewhich = true;
	//魚が下にいるかどうかの変数(trueなら下にいる、falseなら下にいない)
	bool FishLanding = true;
	//魚が捕食行動をするかどうかの変数
	//プレイヤーを狙っている場合（1の時は0番目の画像を狙うのか、2の時は1番目の画像を狙うのか）
	//0の時は何も狙っていない時
	//プレイヤー
	int AimPlayer = 0;
	//敵
	int AimEnemy = 0;
	//--------------------------------------------------------



	//---------------------------------------------------------
	//ObjSet関連
	//関数宣言
	void ObjCreate();  //オブジェクトの作成
	void Objrender();  //オブジェクトの描画
	void Backrender(); //背景の描画
	void ObjDispose(); //オブジェクトの破棄
	void ObjSetPos();  //オブジェクトの設置
	//以下ボーナスステージ関連
	void BObjCreate();  //オブジェクトの作成
	void BObjrender();  //オブジェクトの描画
	void BBackrender(); //背景の描画
	void BObjDispose(); //オブジェクトの破棄
	void BObjSetPos();  //オブジェクトの設置
	void BonusStage();
	void BBalloonCollision();
	void BonusCollision();
	void balloonSet();

	//背景関連の宣言
	CPicture* g_pBackground = NULL;
	CPicture* g_pBackAnim = NULL;
	//オブジェクトの構造体宣言
	//画像位置
	//浮島
	StageObjPos BlockPos[3]
	{
		{
			1,
			{6,0,0,0,0},
			{0.0f,0.0f,0.0f,0.0f,0.0f},
			{11.0f,0.0f,0.0f,0.0f,0.0f}
		},

		{
			3,
			{6,2,2,0,0},
			{0.0f,-8.0f,10.0f,0.0f,0.0f},
			{11.0f,18.0f,19.0f,0.0f,0.0f}
		},
		
		{
			2,
			{1,0,0,0,0},
			{0.0f,-4.0f,0.0f,0.0f,0.0f},
			{6.0f,22.0f,0.0f,0.0f,0.0f},
		},
	};

	//浮島(柱)
	StageObjPos BlockBerPos[3]
	{
		{
			0,
			{0,0,0,0,0},
			{0.0f,0.0f,0.0f,0.0f,0.0f},
			{0.0f,0.0f,0.0f,0.0f,0.0f}
		},

		{
			0,
			{0,0,0,0,0},
			{0.0f,0.0f,0.0f,0.0f,0.0f},
			{0.0f,0.0f,0.0f,0.0f,0.0f}
		},

		{
			3,
			{4,4,4,0,0},
			{-6.5f,1.5f,10.5f,0.0f,0.0f},
			{12.0f,17.0f,22.0f,0.0f,0.0f},
		},
	};


	//雲
	StageObjPos CloudPos[3]
	{
		1,
		{1,0,0,0,0},
		{0.0f,0.0f,0.0f,0.0f,0.0f},
		{20.0f,0.0f,0.0f,0.0f,0.0f},


		2,
		{1,1,0,0,0},
		{-12.0f,8.0f,0.0f,0.0f,0.0f},
		{12.0f,14.0f,0.0f,0.0f,0.0f},


		2,
		{1,1,0,0,0},
		{6.0f,-12.0f,0.0f,0.0f,0.0f},
		{10.0f,18.0f,0.0f,0.0f,0.0f},

	};


	//画像情報
	//波(中央)
	Obj Wave
	{
		4,
		128.0f,
		128.0f
	};
	CPicture* g_pWave[8] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
	//波(両端)
	Obj EndWave
	{
		4,
		128.0f,
		128.0f
	};
	CPicture* g_pEndWave[4] = { NULL,NULL,NULL,NULL };
	//地面(中央)
	Obj Ground
	{
		14,
		64.0f,
		72.0f
	};
	CPicture* g_pGround[14] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
	//地面(右端)
	Obj RightGround
	{
		1,
		32.0f,
		72.0f
	};
	CPicture* g_pRightGround = NULL;
	//地面(左端)
	Obj LeftGround
	{
		1,
		32.0f,
		72.0f
	};
	CPicture* g_pLeftGround = NULL;
	//浮島(中央)
	Obj Block
	{
		BlockPos[PhaseNum - 1].ConnectCount[0] + BlockPos[PhaseNum - 1].ConnectCount[1] + BlockPos[PhaseNum - 1].ConnectCount[2] + BlockPos[PhaseNum - 1].ConnectCount[3] + BlockPos[PhaseNum - 1].ConnectCount[4],
		64.0f,
		32.0f
	};
	CPicture* g_pBlock[12] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
	//浮島(右端)
	Obj RightBlock
	{
		BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count,
		32.0f,
		32.0f
	};
	CPicture* g_pRightBlock[5] = { NULL,NULL,NULL,NULL,NULL };
	//浮島(左端)
	Obj LeftBlock
	{
		(BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count),
		32.0f,
		32.0f
	};
	CPicture* g_pLeftBlock[5] = { NULL,NULL,NULL,NULL,NULL };
	//雲
	Obj Cloud
	{
		CloudPos[PhaseNum - 1].Count,
		128.0f,
		128.0f
	};
	CPicture* g_pCloud[4] = { NULL,NULL,NULL,NULL };
	//浮島(柱)
	Obj BlockBer
	{
		(BlockBerPos[PhaseNum - 1].ConnectCount[0] + BlockBerPos[PhaseNum - 1].ConnectCount[1] + BlockBerPos[PhaseNum - 1].ConnectCount[2] + BlockBerPos[PhaseNum - 1].ConnectCount[3] + BlockBerPos[PhaseNum - 1].ConnectCount[4]),
		32.0f,
		32.0f
	};
	CPicture* g_pBlockBer[12] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };

	//ボーナスステージ関連
	//地面
	Obj BGround
	{
		//連結させた時に必要な数
		20,
		//Xサイズ
		64.0f,
		//Yサイズ
		64.0f
	};
	//ボーナスステージの地面の画像を管理する変数
	CPicture* g_pBGround[20] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL, };
	//土管
	Obj Pipe
	{
		//連結させた際の数
		16,
		//Xサイズ
		64.0f,
		//Yサイズ
		32.0f
	};
	//土管の画像を管理する変数
	CPicture* g_pPipe[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,  NULL,  NULL,  NULL,  NULL, };
	//風船
	Obj Balloon
	{
		//連結させた際の数
		20,
		//Xサイズ
		64.0f,
		//Yサイズ
		64.0f
	};
	//風船関連の構造体
	struct BalloonData
	{
		CPicture* Obj;
		//風船が最初に動く方向をランダムで決めるための変数(1なら左に移動、2なら右に移動)
		//風船が土管に当たっている間は左右に動かない様にするためにも使用する(3の時は左右に動かない)
		int BalloonCourse = 3;
		//風船が左右に動くスピード
		float BalloonSpeed = 0.0f;
		//風船が左右に動く量を決める変数
		float BalloonMove = 0.0f;
		//パイプない判定フラグ
		bool inPipe = true;
		bool HIt = false;
	};

	//風船の数
	#define BALLOON_OBJECT_COUNT  20
	//放出した風船の数
	int NowballoonCnt = 0;
	//風船
	BalloonData g_pBalloon[BALLOON_OBJECT_COUNT] =
	{
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		{NULL},

	};
	//割った風船の数を管理する変数
	int BreakBallonCnt = 0;
	
	//風船放出タイミング用カウンタ
	int balloonCnt = 0;

	//背景
	CPicture* g_pBBackGround = NULL;
	CPicture* g_pBBackAnim = NULL;

	bool BonusON = false;		//ボーナスステージを開始するかの変数
	//----------------------------------------------------------

	
	
	//----------------------------------------------------------
	//当たり判定関連の構造体定義
	struct CollisionData
	{
		XMFLOAT4 Pos;
		XMFLOAT2 Size;
	};

	//-----------------------------------------
	//プレイヤーに関連の宣言
	//前回のフレームでの最終座標
	XMFLOAT4 BeforePlayerPos[2] =
	{
		{0.0f, 0.0f, 0.0f, 0.0f },
		{0.0f, 0.0f, 0.0f, 0.0f }
	};

	XMFLOAT4 BeforeEnemyPos[ENEMY_OBJECT_COUNT] =
	{
		{0.0f, 0.0f, 0.0f, 0.0f },
		{0.0f, 0.0f, 0.0f, 0.0f },
		{0.0f, 0.0f, 0.0f, 0.0f },
	};

	//プレイヤーの当たり判定データ
	CollisionData EntityToObjCollisionData
	{
		{0.0f,-16.0f,0.0f,0.0f},                       //現在座標からの当たり判定の移動量
		{(20.0f / PLAYER_SIZE_X),(50.0f / PLAYER_SIZE_Y)}//当たり判定のサイズ比率
	};
	//-----------------------------------------
	//変数宣言
	bool CollisionFlag = true;

	//関数宣言
	void UnderCollision(CPicture* Getg_pPicture,XMFLOAT4 GetBeforePos, int i);   //当たり判定（上）
	void SideCollision(CPicture* Getg_pPicture,int i);    //当たり判定（側面）
	void OverCollision(CPicture* Getg_pPicture, int i);    //当たり判定（下）
	void EntityCplision(CPicture* My, CPicture* Target,int i,int j);
	
	void PlayerCollision();							//プレイヤーの当たり判定の処理を全てまとめたもの
	void EnemyCollision();							//エネミーの当たり判定の処理を全てまとめたもの
	//-----------------------------------------------------------



//記述:松本----------------------------------------------------------------------------------------------------------------------------

private:
	//-----------------------------------------------------------
	//雷の処理を行う関数
	void Thunder();
	//雷の座標の関数
	void ThunderPos();
	//雷の画像を作成する関数
	void ThunderCreate();
	//描画する関数
	void ThunderRender();
	//破棄する関数
	void ThunderDispose();

	////雷の向きの乱数を取得する変数
	//int ThunderRand = rand() % 4;

	//----------------------------------------------------------------
	//雷の構造体
	struct g_Thunder
	{
		CPicture* obj;			//画像管理用
		float Thunder_SIZE_X;	//サイズ
		float Thunder_SIZE_Y;
		int ThunderTime;		//雷発射タイミング用
		int flag;				//発射フラグビット
		int Cnt;				//個数
		int Phase;				//フェーズ
		int ThunderRand;		//乱数
		double DisThunder;		//雷が消えるまでの時間計測
		bool AnimFlag;
	};
	g_Thunder g_ThunderObj =
	{
		NULL,32.0f,88.0f,0,0b0000,0,0,0,0.0,false
	};
	//ボールの加速値
	float BallAcceleration = 0.5f;

	//雷の弾の処理を行う関数
	void ThunderBall();
	//弾の当たり判定の処理を行う関数
	void ThunderBallCollision();
	//弾の座標の関数
	void ThunderBall0Pos();
	void ThunderBall1Pos();

	//雷の弾の数
#define ThunderBallCnt (2)
	//雷の弾の構造体
	struct g_ThunderBall
	{
		CPicture* obj;			//画像管理用
		float Ball_SIZE_X;		//サイズ
		float Ball_SIZE_Y;
		float XMoveSpeed;		//移動速度
		float YMoveSpeed;
	};
	g_ThunderBall g_ThunderBallObj[ThunderBallCnt] =
	{
		{NULL,32.0f,32.0f,1.6f,3.0f},
		{NULL,32.0f,32.0f,1.6f,3.0f}
	};
	//加速値上限
	float MaxBallAcceleration = 30.0f;
	//雷の弾のデフォルトスピード
	float DefaultXSpeed = 1.6f;
	float DefaultYSpeed = 3.0f;

	//雷雲の処理に使う乱数
	int CloudThunderRand = 0;
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	//アニメーション関連
	//関数宣言
	void PlayerAnim();                                //プレイヤーのアニメーション
	void EnteringWaterCreate(CPicture* g_pPicture);   //入水時の画像作成
	void EnteringWaterAnim();                         //入水時のアニメーション
	void BubbleCreate(CPicture* g_pPicture);		  //泡の画像作成
	void BubbleAnim();								  //泡のアニメーション
	void FishAnim();								  //魚のアニメーション
	void ThunderAnim();								  //雷のアニメーション
	void EnemyAnim();								  //敵のアニメーション
	void DeathCoolTimeAnim();						  //死亡後のクールタイムアニメーション
	void BalloonAnim();                               //風船のアニメーション

	//アニメカウントの要素番号
#define AnimCountPlayer 0
#define AnimCountWater 1
#define AnimCountFish 7
#define AnimCountThunder 8
#define AnimCountThunderBall1 9
#define AnimCountThunderBall2 10
#define AnimCountEnemy 11
#define AnimCountCloud 21
#define AnimCntThunderDeath 24
#define AnimCntPlayerDeath 29
#define AnimCntDeathCoolTime 34
#define AnimCountBubble 35
#define AnimCountBack 42
#define AnimCountBalloon 46

	//変数宣言
#define BubbleCount 6
	CPicture* g_pBubble[BubbleCount] = { NULL ,NULL , NULL , NULL , NULL , NULL };
	float BubbleMove_x[BubbleCount] = { 0.0f ,0.0f,0.0f,0.0f,0.0f,0.0f };
	bool BubbleMove_xFlag[BubbleCount] = { true,true, true, true, true, true};
#define WaterCount 6
	CPicture* EnteringWater[WaterCount] = { NULL ,NULL , NULL , NULL , NULL , NULL };
	int AnimCount[67] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
	int JumpCount = 0;
	bool MoveAnim = false;
	bool NowBrake = false;
	bool BreakBalloon = false;
	bool ThunderAnimFlag = false;
	bool EnemyFallAnimFlag[ENEMY_OBJECT_COUNT] = { false ,false ,false ,false ,false ,false,false,false,false,false };
	bool BalloonReloadFlag[ENEMY_OBJECT_COUNT] = { true ,true,true,true,true,true,true,true,true,true };
	bool EnemyDeathFlag[ENEMY_OBJECT_COUNT] = { false ,false ,false ,false ,false ,false,false,false,false,false };
	bool EnemyDeathFallFlag[ENEMY_OBJECT_COUNT] = { false ,false ,false ,false ,false ,false,false,false,false,false };
	float EnemyDeathFallSpeed[ENEMY_OBJECT_COUNT] = { 3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f,3.0f };

	bool DeathFlag = false;
	bool DeathFishFlag = false;
	bool EnemyDeathFishFlag = false;
	int EnemyDeathFishLvel = 0;
	bool DeathFallFlag = false;
	bool DeathThunderFlag = false;
	bool DeathCoolFlag = true;

	bool pEnteringWaterFlag = false;

	//-----------------------------------------------------------------


	//-----------------------------------------------------------------
	//ゲームオーバー関連
	void DeathStatusSet();     //プレイヤーが死亡した時の処理
	void procOverBegin();
	void procOverMain();
	void procOverEnd();
	//ゲームオーバーの構造体
	struct GameOver
	{
		ePhase g_GameOverPhase;					//フェーズ管理
		CPicture* g_pGameOver;					//画像
		eGameStatus g_NextStatusFromGameOver;	//フロー管理
		float Text_SIZE_X;						//サイズ
		float Text_SIXE_Y;
		int Cnt;								//カウンター
	};
	GameOver g_GameOver
	{
		eBegin,NULL,eNone,320.0f,32.0f,0
	};
	//-----------------------------------------------------------------

	//----------------------------------------------------------------------------
	//ロード関係
	void doLoading();
	void procGameLoad();
	void BlackScreenCreate();
	//どのロード中か判別する変数
	int  IsLoad = 0b0000;
	//黒いスクリーンの画像を管理する変数
	CPicture* g_Black = NULL;
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	// ゲームクリア関連
	void procClearBegin();
	void procClearMain();
	void procClearEnd();
	//ゲームクリアの構造体
	struct GameClear
	{
		ePhase g_GameClearPhase;				//フェーズ管理
		CPicture* g_pGameClear;					//画像（デバッグで分かりやすいように作成、実装時は削除）
		eGameStatus g_NextStatusFromGameClear;	//フロー管理
		int Cnt;								//カウンター
	};
	GameClear g_GameClear
	{
		eBegin,NULL,eNone,0
	};

	//クリア判定用エネミーカウンタ
	int EnemyCount = 0;
	//----------------------------------------------------------------

	//サウンド変数定義------------------------------------------------
	void SoundPlay();
	void SoundDispose();
	void SoundCreate();

	//ボーナスステージBGM再生時間計測用
	double BGMCreateTimeCnt = 0;    //作成時
	double BGMNowTimeCnt = 0;       //今の
	
	//タイトル画面のフェーズを管理する変数
	ePhase g_TitlePhase = eBegin;
	//タイトル画面の画像を管理する変数
	CPicture* g_pTitle = NULL;
	//タイトルから次へ進む時のフローを管理する変数
	eGameStatus g_NextStatusFromTitle = eNone;
	// サウンド
	//ゲームスタート
	CSound* g_pPhaseStart = NULL;
	//エネミー降下
	CSound* g_pEnemyDown = NULL;
	//phaseクリア
	CSound* g_pPhaseCler = NULL;
	//エネミー死亡時
	CSound* g_pEnemyDeath = NULL;
	//プレイヤージャンプ
	CSound* g_pJump = NULL;
	//プレイヤージャンプ
	CSound* g_pStep = NULL;
	//プレイヤージャンプ
	CSound* g_pRespawn = NULL;
	//プレイヤージャンプ
	CSound* g_pHit = NULL;
	//プレイヤージャンプ
	CSound* g_pBalloonBom = NULL;
	//プレイヤージャンプ
	CSound* g_pEnemyJump[5] = { NULL,NULL,NULL,NULL,NULL };
	//プレイヤージャンプ
	CSound* g_pBuble = NULL;
	//プレイヤージャンプ
	CSound* g_pBubleBoom = NULL;
	//ゲームオーバー
	CSound* g_pGameOver = NULL;
	//入水
	CSound* g_pWater = NULL;
	//プレイヤー落下
	CSound* g_pFall = NULL;
	//感電死
	CSound* g_pThunderDeath = NULL;
	//魚出現
	CSound* g_pSFish = NULL;
	//魚死
	CSound* g_pSFishDeath = NULL;
	//雷出現
	CSound* g_pSThunder = NULL;
	//雷反射
	CSound* g_pThunderHit = NULL;
	//エネミーの着地
	CSound* g_pSEnemyLanding = NULL;
	//ボーナスステージのBGM
	CSound* g_pBonusBgm = NULL;
	//ボーナスポイント
	CSound* g_pPoint = NULL;
	//ボーナスパーフェクト
	CSound* g_pPerfect = NULL;
	
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	//ステージ管理関連
	// エネミー
	//変数宣言
	int iEnemyCount[3] = {6,10,10};
	XMFLOAT2 EnemybeginPos[3][10] =
	{
		{ {(0.0f - 112.0f),-32.0f},{(0.0f - 112.0f),-32.0f},{0.0f ,-32.0f},{0.0f ,-32.0f},{(0.0f + 112.0f),-32.0f},{(0.0f + 112.0f),-32.0f},{0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f} },
		{ {(0.0f - 112.0f),-32.0f},{(0.0f - 112.0f),-32.0f},{0.0f ,-32.0f},{0.0f ,-32.0f},{(0.0f + 112.0f),-32.0f},{(0.0f + 112.0f),-32.0f},{(-8.0f*32.0f),WINDOW_BOTTOM + (21.0f * 32.0f)},{(-8.0f * 32.0f),WINDOW_BOTTOM + (21.0f * 32.0f)},{(10.0f * 32.0f),WINDOW_BOTTOM + (22.0f * 32.0f)},{(10.0f * 32.0f),WINDOW_BOTTOM + (22.0f * 32.0f)} },
		{ {(0.0f * 32.0f),WINDOW_BOTTOM + (9.0f * 32.0f)},{(0.0f * 32.0f),WINDOW_BOTTOM + (9.0f * 32.0f)},{(-6.5f * 32.0f),WINDOW_BOTTOM + (15.0f * 32.0f)},{(-6.5f * 32.0f),WINDOW_BOTTOM + (15.0f * 32.0f)},{(1.5f * 32.0f),WINDOW_BOTTOM + (20.0f * 32.0f)},{(1.5f * 32.0f),WINDOW_BOTTOM + (20.0f * 32.0f)},{(-4.0f * 32.0f),WINDOW_BOTTOM + (25.0f * 32.0f)},{(-4.0f * 32.0f),WINDOW_BOTTOM + (25.0f * 32.0f)},{(10.5f * 32.0f),WINDOW_BOTTOM + (25.0f * 32.0f)},{(10.5f * 32.0f),WINDOW_BOTTOM + (25.0f * 32.0f)} },
	}; 
	int iEnemyLevel[3][10] = 
	{
		{ 0,0,0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,1,1,1,1},
		{ 0,0,1,1,1,1,2,2,2,2},
	};

	//-----------------------------------------------------------------

	//タイトル選択関数
	void procTitleSelect();
	//選択箇所を受け取る変数 
	//0…A　１…B　２…C		
	int TitleSelect;
	//タイトルバルーンの座標管理用構造体
	struct TitleBalloon
	{
		float PosX;
		float PosY;
	};
	TitleBalloon g_titleballoonPos[3] =
	{
		{-48.0f * 6.0f + (-48.0f / 2.0f),-64.0f * 1.0f + (-64.0f / 4.0f)},
		{-48.0f * 6.0f + (-48.0f / 2.0f),-64.0f * 2.0f + (-64.0f / 4.0f)},
		{-48.0f * 6.0f + (-48.0f / 2.0f),-64.0f * 3.0f + (-64.0f / 4.0f)},
	};
	//タイトル選択風船
	CPicture* g_pTitleBalloon = NULL;
	//-----------------------------------------------------------------
//ボーナスクリア関連
//関数宣言
	void doBonusClear();
	void procBonusClear();
	void procBonusClearBegin();
	void procBonusClearMain();
	void procBonusClearEnd();
	//変数宣言
	//フェーズ用変数
	ePhase g_BonusClearPhase = eBegin;
	//次のステータス移行するための変数
	eGameStatus g_NextStatusFromBonusClear = eNone;
	//背景画像管理用変数
	CPicture* g_BonusClearBack = NULL;
	//乗算マーク(×)
	CPicture* g_pMultiplicationMark = NULL;
	//等号マーク(＝)
	CPicture* g_pEqualSign = NULL;
	//ボーナスパーフェクト
	CPicture* g_pBounusPerfect = NULL;
	//PTS
	CPicture* g_pPTS = NULL;
	//ボーナスバルーン
	CPicture* g_pBBalloon = NULL;

	//バルーンのスコア画像管理
	CFont* g_BalloonScore = NULL;
	//獲得した風船の個数を表示する画像
	CFont* g_pGetBalloon = NULL;
	//合計スコア画像管理用変数
	CFont* g_pTotalScore = NULL;

	//シンボルのサイズ
	float Symbol_SIZE_X = 24.0f;
	float Symbol_SIZE_Y = 24.0f;
	//タイムカウンター
	int BonusTimeCnt = 0;
	//獲得スコア計算
	int TotalScore = 0;
	//スコア加算時の繰り返しに使う変数
	int getballoonCnt = 0;
	//バルーンのポイント
	int BalloonPoints = 300;

	//パーフェクト時を管理する変数
	bool PerfectFlag = false;
	//スコア計算が終わったかを確認するフラグ
	bool ScoreFlag = false;

	//-----------------------------------------------------------------
};

