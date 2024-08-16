/**
* @file CActionGameApp.h
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"
#include "CApplication.h"
#include "CPicture.h"
#include "MediaResource.h"
#include "UVAnimation.h"
#include "CFont.h"
// --------------------------------------------
// �g���͍דc��K���L�q�i2021_09_29�j
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
	// �g���͍דc��K���L�q�i2021_09_29�j

	CSound* createSound(const char* filePath_, const bool loop_ = false);
	void PlaySourceSound(CSound* const objects);
	void disposeSound(CSound* const objects);
	void StopSourceSound(CSound* const objects);
	// --------------------------------------------

	// �ۑ�p�֐�
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
	//UI�֘A
private:
	//�ϐ��錾
	struct UI
	{
		int Score;
		CPicture* g_pCategory;
		CFont* g_pScore;
		float Size_X;
		float Size_Y;
	};

	//---------------------------------------------------
	//�v���C���[�Ɋւ���UI
	//�X�R�A
	UI PlayerScore
	{
		000000,
		NULL,
		NULL,
		32.0f,
		32.0f,
	};
	//�c�@
#define RemainCount 2
	CPicture* g_pRemain[RemainCount] = { NULL,NULL };
	int NowRemainCount = RemainCount;
	float RemainSize_X = 16.0f;
	float RemainSize_Y = 24.0f;
	//---------------------------------------------------

	//---------------------------------------------------
	//�g�b�v�X�R�A��UI
	UI TopScore
	{
		0,
		NULL,
		NULL,
		64.0f,
		32.0f,
	};
	//---------------------------------------------------

	//���Z�X�R�A
#define AddScoreIndex 6
	CFont* g_pAddScore[AddScoreIndex] = { NULL,NULL, NULL, NULL, NULL, NULL };
	const float AddScoreSize_X = 16.0f;
	const float AddScoreSize_Y = 32.0f;
	int AddScore[AddScoreIndex] = { 0,0,0,0,0,0 };
	int AddScoreCnt[AddScoreIndex] = { 0,0,0,0,0,0 };

	//---------------------------------------------------
	//�t�F�C�Y
	CPicture* Phase_UI = NULL;
	const float PhaseSize_X = 192.0f;
	const float PhaseSize_Y = 32.0f;
	CFont* PhaseNum_UI = NULL;
	int PhaseNum = 1;
	int PhaseRenderCnt = 0;

	//---------------------------------------------------
	//�֐��錾
	void UIcreate();       //UI�̉摜���쐬
	void UIrender();       //UI�̉摜��`��
	void UIdispose();      //UI�̉摜��j��
	void UIsetPos();       //UI�̔z�u
	void AddScoreSet(CPicture* g_pPicture, int getScore);    //���Z�X�R�A�̕\���E�ݒu
	void ScoreSet(int SetNum);       //�X�R�A�̏���
	void RemainSet();      //�c�@�̏���
	//---------------------------------------------------
//-----------------------------------------------------------



//�v���C���[�֘A-------------------------------------------
	//�v���C���[�̉摜���Ǘ�����ϐ�
	CPicture* g_pPlayer[2] = { NULL,NULL };

	//�v���C���[�̕\���T�C�Y
	const float PLAYER_SIZE_X = 64.0f;
	const float PLAYER_SIZE_Y = 128.0f;

	//�t���[���J�E���^
	int FlameCnt = 0;

	//���̕��D�̐�
	int BalloonCount = 2;

	void procPlayMain_movePlayer();     //�v���C���[�̈ړ�����
	void procPlayMain_BothEnds();		//��ʋ��̏���
//---------------------------------------------------------

//�v���C���[�̏c�ړ������֘A-------------------------------
	//�v���C���[�̃W�����v��
	float g_pJumpRise = 0.0f;
	//�v���C���[�̃W�����v�̗� �����Ă������т�0.1�������Ă���
	float g_pJumpPower = 0.0f;
	//�v���C���[�̍ő�㏸��
	float g_pMaxRise = 1.0f;

	//�v���C���[���n�ʂɒ��n���Ă��邩�̃t���O
	//true�Ȃ璅�n���Ă���Bfalse�Ȃ璅�n���Ă��Ȃ�
	bool PlayerLanding = false;

	//�v���C���[���ǂ�������Ɉړ����Ă�������ۑ����Ă����ϐ�
	//true�Ȃ�E�ړ��Afalse�Ȃ獶�ړ�
	bool WidthSwitch = NULL;

	//�������x
	float Gravity = 0.0f;

	//MAX�̏d�͗ʁi���~���x�j4.0f��葬���������Ȃ�
	const float MaxGravity = 4.0f;
	//---------------------------------------------------------

	//�v���C���[�̉��ړ������֘A-------------------------------
	//�v���C���[�̈ړ����x
	float g_playerMoveSpeed = 0.0f;
	float g_pRunSpeed = 0.0f;
	//�v���C���[�̋󒆈ړ����x
	float g_pPlayerFlySpeed = 0.0f;
	//---------------------------------------------------------


	//��ʒ[�̏����֘A-----------------------------------------

			//�ǂ���̉摜�̃v���C���[���\������Ă��邩��ۑ����邽�߂̕ϐ�
			//���C���̉摜�ɂȂ��Ă��邩
	int PlayerNum = 0;

	//---------------------------------------------------------


	private:
	//-------------------------------------------------------
	//Enemy�֘A
	//�֐��錾
	void procPlayMain_EnemyCreate(); //�G�l�~�[�̍쐬
	void procPlayMain_procEnemy();   //�G�l�~�[�̕`��
	void procPlayMain_EnemyDispose();//�G�l�~�[�̔j��
	void procPlayMain_EnemyBothEnd();//�G�l�~�[�̉�ʒ[����
	void procPlayMain_EnemyStatus();

	//�ϐ��錾
	//�G�l�~�[�̏���Z�߂�\����
	struct Enemy
	{
		//�摜�Ǘ��p
		CPicture* obj;
		//�G�l�~�[�̏������W
		XMFLOAT2 beginPos;
		//��ʒ[�̏����p�̃o�[�W�����@�O�F��ɉ�ʂɕ\������Ă�����@�P�F���Α��ɏo���
		int enemyVer = 0;
		//��ʒ[�ɂ��邩�̃t���O
		bool NowEdge = false;
		//�G�l�~�[�̈ړ��������W��
		float MovedPos = 0.0f;
		//�G�l�~�[�ƃv���C���[�̋�����ۑ�����ϐ�
		XMFLOAT4 PlayerDistance;
		//�G�l�~�[�̔�s���x
		float g_pEnemyFlySpeed_X = -1.5f;
		float g_pEnemyFlySpeed_Y = 1.5f;

		//�G�l�~�[�ƃv���C���[���q������
		float g_pPlayerEnemyLine;
		//�G�l�~�[���ړ����郉�C��
		float g_pEnemyMoveLine;

		//�G�l�~�[�̍s���p�^�[��
		int pattern;

		XMFLOAT4 enemyPos;

		XMFLOAT4 DirectionPos;

		//�������̓��������E���]����ۂɂ��g�p
		int EnemyCourse = 3;

		//�G�l�~�[���������ɂǂꂾ������̕����Ɉړ�������
		int EnemyFall = 0;

		//���ʈړ������痎������������t�ɂ���
		float EnemyFallSpeed = 0.0f;

		//�G�l�~�[�̃X�e�[�^�X���Ǘ�����ϐ�
		//�O���󒆁A�P���������A�Q�����n�A�R���Q�[�����n�܂��čŏ��ɕ��D������鎞�A�S������
		int EnemyStatus = 3;

		//�G�l�~�[�̃��x�����Ǘ�����ϐ��i�X�e�[�^�X���Q�̎��ɕ��D��c��܂��ĕ�������ۂɂP���₷�@�@���x���͂O�C�P�C�Q�̎O��ށj
		//�O�����i�G���j�A�P���΁i���ʁj�A�Q���ԁi�G�[�X�@�j
		//�ŏ�����G�l�~�[�̃��x�����O�ł͂Ȃ��G�l�~�[�Ɋւ��Ă͍쐬�̃^�C�~���O�Ƃ��ő������΂悢���낤
		int EnemyLevel = 0;

		//�G�l�~�[���ӂ������c��܂��ĕ�������܂łɂ����鎞�Ԃ̗�����ۑ����Ă����ϐ�
		float EnemyReturn_Num = 0.0;

		////�G�l�~�[�����n���Ă��邩
		//bool EnemyLanding = NULL;

		//�G�l�~�[�̍ō����x
		float  g_pEnemyMaxSpeed_X;
		float  g_pEnemyMaxSpeed_Y;

		//�G�l�~�[�̃��x���̂���đ��x�𒲐�����l
		double SpeedMagnification = 1.0;

		//�G�l�~�[�̍�����G���A���Ǘ�����ϐ�
		//0�F����@1�F������@2�F�E��@3�F�����@4�F�������@5�F�E��
		int EnemyArea;

		//�t���[���J�E���^
		int flameCnt[2] = {0, 0};
	};
	
	//�G�l�~�[�̃T�C�Y
	float ENEMY_SIZE_X = 64.0f;
	float ENEMY_SIZE_Y = 128.0f;
	
	//�G�l�~�[�̐�
	#define ENEMY_OBJECT_COUNT  10
	
	//�G�̏����Ǘ�����ϐ�
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
	
	//�G�l�~�[���������鎞�Ԃ��v������ϐ�
	int EnemyFallTime = 100;
	
	//�G�l�~�[�̍ō����x
	float g_pEnemyFlyMaxSpeed = 3.0f;
	
	//�G�l�~�[�����n�ɋ��邩�̔���
	//true�Ȃ璅�n���Ă���Bfalse�Ȃ畂�V���Ă���
	bool g_pEnemyLanding = NULL;

	//�G�l�~�[�̈ړ��ʂ����L�̒l�𒴂�����v���C���[�̍��W���擾����
	double GetPlayerPos = 1.0;

	XMFLOAT4 enemyPos = { 0.0f,300.0f,0.0f,0.0f };
	XMFLOAT4 PlayerPos = { 0.0f,0.0f,0.0f,0.0f };

	//���L�̃t���[�����𒴂�����v���C���[�̍��W���Ď擾����
	int GetPos = 180;
	//�G�l�~�[���������Ȃ��悤�ɒ�������ׂ̒l
	float EnemyNotInWater = -230.0f;


	//���݂̃G���A����̂��߂̒l
	float AreaLineLeft = WINDOW_WIDTH / 3 - WINDOW_WIDTH / 2;
	float AreaLineRight = -WINDOW_WIDTH / 3 + WINDOW_WIDTH / 2;
	float AreaLineUnder = WINDOW_HEIGHT / 3 - WINDOW_HEIGHT / 2;
	float AreaLineOver = -WINDOW_HEIGHT / 3 + WINDOW_HEIGHT / 2;
	//------------------------------------------------------------

	//------------------------------------------------------------
	//Fish�֘A
	//�֐��錾
	void procPlayMain_moveFish();     //���̈ړ�����
	void procPlayMain_AlgorithmFish(); //���̃A���S���Y��
	//�ϐ��錾
	CPicture* g_pFish = NULL;
	//���ƃv���C���[�̓����蔻���ς���ϐ�
	float ActiveArea_Num = 8.0f;		//�����o�����镝��ς��邽�߂̕ϐ�
	float KillArea_Num = 16.0f;			//�����v���C���[���E���镝��ς��邽�߂̕ϐ�
	float FishPos = 0.0f;
	const float FISH_SIZE_X = 64.0f;
	const float FISH_SIZE_Y = 128.0f;
	//���̉��ړ��𔽓]�����邽�߂̕ϐ�(true�Ȃ獶�Ɉړ��Afalse�Ȃ�E�Ɉړ�)
	bool Movewhich = true;
	//�������ɂ��邩�ǂ����̕ϐ�(true�Ȃ牺�ɂ���Afalse�Ȃ牺�ɂ��Ȃ�)
	bool FishLanding = true;
	//�����ߐH�s�������邩�ǂ����̕ϐ�
	//�v���C���[��_���Ă���ꍇ�i1�̎���0�Ԗڂ̉摜��_���̂��A2�̎���1�Ԗڂ̉摜��_���̂��j
	//0�̎��͉����_���Ă��Ȃ���
	//�v���C���[
	int AimPlayer = 0;
	//�G
	int AimEnemy = 0;
	//--------------------------------------------------------



	//---------------------------------------------------------
	//ObjSet�֘A
	//�֐��錾
	void ObjCreate();  //�I�u�W�F�N�g�̍쐬
	void Objrender();  //�I�u�W�F�N�g�̕`��
	void Backrender(); //�w�i�̕`��
	void ObjDispose(); //�I�u�W�F�N�g�̔j��
	void ObjSetPos();  //�I�u�W�F�N�g�̐ݒu
	//�ȉ��{�[�i�X�X�e�[�W�֘A
	void BObjCreate();  //�I�u�W�F�N�g�̍쐬
	void BObjrender();  //�I�u�W�F�N�g�̕`��
	void BBackrender(); //�w�i�̕`��
	void BObjDispose(); //�I�u�W�F�N�g�̔j��
	void BObjSetPos();  //�I�u�W�F�N�g�̐ݒu
	void BonusStage();
	void BBalloonCollision();
	void BonusCollision();
	void balloonSet();

	//�w�i�֘A�̐錾
	CPicture* g_pBackground = NULL;
	CPicture* g_pBackAnim = NULL;
	//�I�u�W�F�N�g�̍\���̐錾
	//�摜�ʒu
	//����
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

	//����(��)
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


	//�_
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


	//�摜���
	//�g(����)
	Obj Wave
	{
		4,
		128.0f,
		128.0f
	};
	CPicture* g_pWave[8] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
	//�g(���[)
	Obj EndWave
	{
		4,
		128.0f,
		128.0f
	};
	CPicture* g_pEndWave[4] = { NULL,NULL,NULL,NULL };
	//�n��(����)
	Obj Ground
	{
		14,
		64.0f,
		72.0f
	};
	CPicture* g_pGround[14] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
	//�n��(�E�[)
	Obj RightGround
	{
		1,
		32.0f,
		72.0f
	};
	CPicture* g_pRightGround = NULL;
	//�n��(���[)
	Obj LeftGround
	{
		1,
		32.0f,
		72.0f
	};
	CPicture* g_pLeftGround = NULL;
	//����(����)
	Obj Block
	{
		BlockPos[PhaseNum - 1].ConnectCount[0] + BlockPos[PhaseNum - 1].ConnectCount[1] + BlockPos[PhaseNum - 1].ConnectCount[2] + BlockPos[PhaseNum - 1].ConnectCount[3] + BlockPos[PhaseNum - 1].ConnectCount[4],
		64.0f,
		32.0f
	};
	CPicture* g_pBlock[12] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
	//����(�E�[)
	Obj RightBlock
	{
		BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count,
		32.0f,
		32.0f
	};
	CPicture* g_pRightBlock[5] = { NULL,NULL,NULL,NULL,NULL };
	//����(���[)
	Obj LeftBlock
	{
		(BlockPos[PhaseNum - 1].Count + BlockBerPos[PhaseNum - 1].Count),
		32.0f,
		32.0f
	};
	CPicture* g_pLeftBlock[5] = { NULL,NULL,NULL,NULL,NULL };
	//�_
	Obj Cloud
	{
		CloudPos[PhaseNum - 1].Count,
		128.0f,
		128.0f
	};
	CPicture* g_pCloud[4] = { NULL,NULL,NULL,NULL };
	//����(��)
	Obj BlockBer
	{
		(BlockBerPos[PhaseNum - 1].ConnectCount[0] + BlockBerPos[PhaseNum - 1].ConnectCount[1] + BlockBerPos[PhaseNum - 1].ConnectCount[2] + BlockBerPos[PhaseNum - 1].ConnectCount[3] + BlockBerPos[PhaseNum - 1].ConnectCount[4]),
		32.0f,
		32.0f
	};
	CPicture* g_pBlockBer[12] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };

	//�{�[�i�X�X�e�[�W�֘A
	//�n��
	Obj BGround
	{
		//�A�����������ɕK�v�Ȑ�
		20,
		//X�T�C�Y
		64.0f,
		//Y�T�C�Y
		64.0f
	};
	//�{�[�i�X�X�e�[�W�̒n�ʂ̉摜���Ǘ�����ϐ�
	CPicture* g_pBGround[20] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,NULL, NULL, NULL, NULL, };
	//�y��
	Obj Pipe
	{
		//�A���������ۂ̐�
		16,
		//X�T�C�Y
		64.0f,
		//Y�T�C�Y
		32.0f
	};
	//�y�ǂ̉摜���Ǘ�����ϐ�
	CPicture* g_pPipe[16] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,  NULL,  NULL,  NULL,  NULL, };
	//���D
	Obj Balloon
	{
		//�A���������ۂ̐�
		20,
		//X�T�C�Y
		64.0f,
		//Y�T�C�Y
		64.0f
	};
	//���D�֘A�̍\����
	struct BalloonData
	{
		CPicture* Obj;
		//���D���ŏ��ɓ��������������_���Ō��߂邽�߂̕ϐ�(1�Ȃ獶�Ɉړ��A2�Ȃ�E�Ɉړ�)
		//���D���y�ǂɓ������Ă���Ԃ͍��E�ɓ����Ȃ��l�ɂ��邽�߂ɂ��g�p����(3�̎��͍��E�ɓ����Ȃ�)
		int BalloonCourse = 3;
		//���D�����E�ɓ����X�s�[�h
		float BalloonSpeed = 0.0f;
		//���D�����E�ɓ����ʂ����߂�ϐ�
		float BalloonMove = 0.0f;
		//�p�C�v�Ȃ�����t���O
		bool inPipe = true;
		bool HIt = false;
	};

	//���D�̐�
	#define BALLOON_OBJECT_COUNT  20
	//���o�������D�̐�
	int NowballoonCnt = 0;
	//���D
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
	//���������D�̐����Ǘ�����ϐ�
	int BreakBallonCnt = 0;
	
	//���D���o�^�C�~���O�p�J�E���^
	int balloonCnt = 0;

	//�w�i
	CPicture* g_pBBackGround = NULL;
	CPicture* g_pBBackAnim = NULL;

	bool BonusON = false;		//�{�[�i�X�X�e�[�W���J�n���邩�̕ϐ�
	//----------------------------------------------------------

	
	
	//----------------------------------------------------------
	//�����蔻��֘A�̍\���̒�`
	struct CollisionData
	{
		XMFLOAT4 Pos;
		XMFLOAT2 Size;
	};

	//-----------------------------------------
	//�v���C���[�Ɋ֘A�̐錾
	//�O��̃t���[���ł̍ŏI���W
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

	//�v���C���[�̓����蔻��f�[�^
	CollisionData EntityToObjCollisionData
	{
		{0.0f,-16.0f,0.0f,0.0f},                       //���ݍ��W����̓����蔻��̈ړ���
		{(20.0f / PLAYER_SIZE_X),(50.0f / PLAYER_SIZE_Y)}//�����蔻��̃T�C�Y�䗦
	};
	//-----------------------------------------
	//�ϐ��錾
	bool CollisionFlag = true;

	//�֐��錾
	void UnderCollision(CPicture* Getg_pPicture,XMFLOAT4 GetBeforePos, int i);   //�����蔻��i��j
	void SideCollision(CPicture* Getg_pPicture,int i);    //�����蔻��i���ʁj
	void OverCollision(CPicture* Getg_pPicture, int i);    //�����蔻��i���j
	void EntityCplision(CPicture* My, CPicture* Target,int i,int j);
	
	void PlayerCollision();							//�v���C���[�̓����蔻��̏�����S�Ă܂Ƃ߂�����
	void EnemyCollision();							//�G�l�~�[�̓����蔻��̏�����S�Ă܂Ƃ߂�����
	//-----------------------------------------------------------



//�L�q:���{----------------------------------------------------------------------------------------------------------------------------

private:
	//-----------------------------------------------------------
	//���̏������s���֐�
	void Thunder();
	//���̍��W�̊֐�
	void ThunderPos();
	//���̉摜���쐬����֐�
	void ThunderCreate();
	//�`�悷��֐�
	void ThunderRender();
	//�j������֐�
	void ThunderDispose();

	////���̌����̗������擾����ϐ�
	//int ThunderRand = rand() % 4;

	//----------------------------------------------------------------
	//���̍\����
	struct g_Thunder
	{
		CPicture* obj;			//�摜�Ǘ��p
		float Thunder_SIZE_X;	//�T�C�Y
		float Thunder_SIZE_Y;
		int ThunderTime;		//�����˃^�C�~���O�p
		int flag;				//���˃t���O�r�b�g
		int Cnt;				//��
		int Phase;				//�t�F�[�Y
		int ThunderRand;		//����
		double DisThunder;		//����������܂ł̎��Ԍv��
		bool AnimFlag;
	};
	g_Thunder g_ThunderObj =
	{
		NULL,32.0f,88.0f,0,0b0000,0,0,0,0.0,false
	};
	//�{�[���̉����l
	float BallAcceleration = 0.5f;

	//���̒e�̏������s���֐�
	void ThunderBall();
	//�e�̓����蔻��̏������s���֐�
	void ThunderBallCollision();
	//�e�̍��W�̊֐�
	void ThunderBall0Pos();
	void ThunderBall1Pos();

	//���̒e�̐�
#define ThunderBallCnt (2)
	//���̒e�̍\����
	struct g_ThunderBall
	{
		CPicture* obj;			//�摜�Ǘ��p
		float Ball_SIZE_X;		//�T�C�Y
		float Ball_SIZE_Y;
		float XMoveSpeed;		//�ړ����x
		float YMoveSpeed;
	};
	g_ThunderBall g_ThunderBallObj[ThunderBallCnt] =
	{
		{NULL,32.0f,32.0f,1.6f,3.0f},
		{NULL,32.0f,32.0f,1.6f,3.0f}
	};
	//�����l���
	float MaxBallAcceleration = 30.0f;
	//���̒e�̃f�t�H���g�X�s�[�h
	float DefaultXSpeed = 1.6f;
	float DefaultYSpeed = 3.0f;

	//���_�̏����Ɏg������
	int CloudThunderRand = 0;
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	//�A�j���[�V�����֘A
	//�֐��錾
	void PlayerAnim();                                //�v���C���[�̃A�j���[�V����
	void EnteringWaterCreate(CPicture* g_pPicture);   //�������̉摜�쐬
	void EnteringWaterAnim();                         //�������̃A�j���[�V����
	void BubbleCreate(CPicture* g_pPicture);		  //�A�̉摜�쐬
	void BubbleAnim();								  //�A�̃A�j���[�V����
	void FishAnim();								  //���̃A�j���[�V����
	void ThunderAnim();								  //���̃A�j���[�V����
	void EnemyAnim();								  //�G�̃A�j���[�V����
	void DeathCoolTimeAnim();						  //���S��̃N�[���^�C���A�j���[�V����
	void BalloonAnim();                               //���D�̃A�j���[�V����

	//�A�j���J�E���g�̗v�f�ԍ�
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

	//�ϐ��錾
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
	//�Q�[���I�[�o�[�֘A
	void DeathStatusSet();     //�v���C���[�����S�������̏���
	void procOverBegin();
	void procOverMain();
	void procOverEnd();
	//�Q�[���I�[�o�[�̍\����
	struct GameOver
	{
		ePhase g_GameOverPhase;					//�t�F�[�Y�Ǘ�
		CPicture* g_pGameOver;					//�摜
		eGameStatus g_NextStatusFromGameOver;	//�t���[�Ǘ�
		float Text_SIZE_X;						//�T�C�Y
		float Text_SIXE_Y;
		int Cnt;								//�J�E���^�[
	};
	GameOver g_GameOver
	{
		eBegin,NULL,eNone,320.0f,32.0f,0
	};
	//-----------------------------------------------------------------

	//----------------------------------------------------------------------------
	//���[�h�֌W
	void doLoading();
	void procGameLoad();
	void BlackScreenCreate();
	//�ǂ̃��[�h�������ʂ���ϐ�
	int  IsLoad = 0b0000;
	//�����X�N���[���̉摜���Ǘ�����ϐ�
	CPicture* g_Black = NULL;
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	// �Q�[���N���A�֘A
	void procClearBegin();
	void procClearMain();
	void procClearEnd();
	//�Q�[���N���A�̍\����
	struct GameClear
	{
		ePhase g_GameClearPhase;				//�t�F�[�Y�Ǘ�
		CPicture* g_pGameClear;					//�摜�i�f�o�b�O�ŕ�����₷���悤�ɍ쐬�A�������͍폜�j
		eGameStatus g_NextStatusFromGameClear;	//�t���[�Ǘ�
		int Cnt;								//�J�E���^�[
	};
	GameClear g_GameClear
	{
		eBegin,NULL,eNone,0
	};

	//�N���A����p�G�l�~�[�J�E���^
	int EnemyCount = 0;
	//----------------------------------------------------------------

	//�T�E���h�ϐ���`------------------------------------------------
	void SoundPlay();
	void SoundDispose();
	void SoundCreate();

	//�{�[�i�X�X�e�[�WBGM�Đ����Ԍv���p
	double BGMCreateTimeCnt = 0;    //�쐬��
	double BGMNowTimeCnt = 0;       //����
	
	//�^�C�g����ʂ̃t�F�[�Y���Ǘ�����ϐ�
	ePhase g_TitlePhase = eBegin;
	//�^�C�g����ʂ̉摜���Ǘ�����ϐ�
	CPicture* g_pTitle = NULL;
	//�^�C�g�����玟�֐i�ގ��̃t���[���Ǘ�����ϐ�
	eGameStatus g_NextStatusFromTitle = eNone;
	// �T�E���h
	//�Q�[���X�^�[�g
	CSound* g_pPhaseStart = NULL;
	//�G�l�~�[�~��
	CSound* g_pEnemyDown = NULL;
	//phase�N���A
	CSound* g_pPhaseCler = NULL;
	//�G�l�~�[���S��
	CSound* g_pEnemyDeath = NULL;
	//�v���C���[�W�����v
	CSound* g_pJump = NULL;
	//�v���C���[�W�����v
	CSound* g_pStep = NULL;
	//�v���C���[�W�����v
	CSound* g_pRespawn = NULL;
	//�v���C���[�W�����v
	CSound* g_pHit = NULL;
	//�v���C���[�W�����v
	CSound* g_pBalloonBom = NULL;
	//�v���C���[�W�����v
	CSound* g_pEnemyJump[5] = { NULL,NULL,NULL,NULL,NULL };
	//�v���C���[�W�����v
	CSound* g_pBuble = NULL;
	//�v���C���[�W�����v
	CSound* g_pBubleBoom = NULL;
	//�Q�[���I�[�o�[
	CSound* g_pGameOver = NULL;
	//����
	CSound* g_pWater = NULL;
	//�v���C���[����
	CSound* g_pFall = NULL;
	//���d��
	CSound* g_pThunderDeath = NULL;
	//���o��
	CSound* g_pSFish = NULL;
	//����
	CSound* g_pSFishDeath = NULL;
	//���o��
	CSound* g_pSThunder = NULL;
	//������
	CSound* g_pThunderHit = NULL;
	//�G�l�~�[�̒��n
	CSound* g_pSEnemyLanding = NULL;
	//�{�[�i�X�X�e�[�W��BGM
	CSound* g_pBonusBgm = NULL;
	//�{�[�i�X�|�C���g
	CSound* g_pPoint = NULL;
	//�{�[�i�X�p�[�t�F�N�g
	CSound* g_pPerfect = NULL;
	
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	//�X�e�[�W�Ǘ��֘A
	// �G�l�~�[
	//�ϐ��錾
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

	//�^�C�g���I���֐�
	void procTitleSelect();
	//�I���ӏ����󂯎��ϐ� 
	//0�cA�@�P�cB�@�Q�cC		
	int TitleSelect;
	//�^�C�g���o���[���̍��W�Ǘ��p�\����
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
	//�^�C�g���I�𕗑D
	CPicture* g_pTitleBalloon = NULL;
	//-----------------------------------------------------------------
//�{�[�i�X�N���A�֘A
//�֐��錾
	void doBonusClear();
	void procBonusClear();
	void procBonusClearBegin();
	void procBonusClearMain();
	void procBonusClearEnd();
	//�ϐ��錾
	//�t�F�[�Y�p�ϐ�
	ePhase g_BonusClearPhase = eBegin;
	//���̃X�e�[�^�X�ڍs���邽�߂̕ϐ�
	eGameStatus g_NextStatusFromBonusClear = eNone;
	//�w�i�摜�Ǘ��p�ϐ�
	CPicture* g_BonusClearBack = NULL;
	//��Z�}�[�N(�~)
	CPicture* g_pMultiplicationMark = NULL;
	//�����}�[�N(��)
	CPicture* g_pEqualSign = NULL;
	//�{�[�i�X�p�[�t�F�N�g
	CPicture* g_pBounusPerfect = NULL;
	//PTS
	CPicture* g_pPTS = NULL;
	//�{�[�i�X�o���[��
	CPicture* g_pBBalloon = NULL;

	//�o���[���̃X�R�A�摜�Ǘ�
	CFont* g_BalloonScore = NULL;
	//�l���������D�̌���\������摜
	CFont* g_pGetBalloon = NULL;
	//���v�X�R�A�摜�Ǘ��p�ϐ�
	CFont* g_pTotalScore = NULL;

	//�V���{���̃T�C�Y
	float Symbol_SIZE_X = 24.0f;
	float Symbol_SIZE_Y = 24.0f;
	//�^�C���J�E���^�[
	int BonusTimeCnt = 0;
	//�l���X�R�A�v�Z
	int TotalScore = 0;
	//�X�R�A���Z���̌J��Ԃ��Ɏg���ϐ�
	int getballoonCnt = 0;
	//�o���[���̃|�C���g
	int BalloonPoints = 300;

	//�p�[�t�F�N�g�����Ǘ�����ϐ�
	bool PerfectFlag = false;
	//�X�R�A�v�Z���I����������m�F����t���O
	bool ScoreFlag = false;

	//-----------------------------------------------------------------
};

