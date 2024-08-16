/**
* @file GameConst.h
* @brief �萔
*
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"

/**
 * �萔
 */
#define APP_NAME L"GameProgramming1 2D Action"

 /*! @name ��`�O���[�v �E�C���h�E
 �E�C���h�E�Ɋւ���萔
 */
 /* @{ */
#define WINDOW_WIDTH	1024 //! �E�B���h�E��
#define WINDOW_HEIGHT	960 //! �E�B���h�E����
const bool kFullScreen = FALSE;	//! �t���X�N���[�����[�h

#define	ASPECT			((FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT)
#define WINDOW_LEFT		(-WINDOW_WIDTH / 2)
#define WINDOW_RIGHT	( WINDOW_WIDTH / 2)
#define WINDOW_TOP		( WINDOW_HEIGHT / 2)
#define WINDOW_BOTTOM	(-WINDOW_HEIGHT / 2)
const XMFLOAT2 kSpriteScreenkSize	= { WINDOW_WIDTH , WINDOW_HEIGHT - 4 };
const FLOAT k1_1	= 1.0f;
const FLOAT k1_2	= 1.0f /  2;
const FLOAT k1_3	= 1.0f /  3;
const FLOAT k1_4	= 1.0f /  4;
const FLOAT k1_5	= 1.0f /  5;
const FLOAT k1_8	= 1.0f /  8;
const FLOAT k1_26	= 1.0f / 26;
/* @} */

/*! @name ��`�O���[�v Shooting
�V���[�e�B���O�Ŏg�p����萔
*/
/* @{ */
const int kMaxHP					= 7;
const XMFLOAT2 kCharSpriteSize	= { 48.0f , 48.0f };
const XMFLOAT2 kBulletSize		= { 16.0f , 16.0f };
const XMFLOAT2 kExplosionSize	= { 80.0f , 80.0f };
const FLOAT kBullet_Left	= -7.0f;
const FLOAT kBullet_Right	= -7.0f + 12.0f;
const FLOAT kEnemyQuantity			= 0.25f * 1.5;
const FLOAT kPlayerQuantity			= 15.25f;
const int kTexelIntervalFrames			= 15;
const int kIntervalShot				= 64*4;
const int kExplosionTexelPauseFrames	= 8;
const int kTexelPlayerBulletIndex	= 0;
const int kTexelEnemyBulletIndex	= 1;
/* @} */

/*! @name ��`�O���[�v DotEat
�h�b�g�C�[�g�Ŏg�p����萔
*/
/* @{ */
const int kMapVertical = 9;		//! �}�b�v�̍s��
const int kMapHorizontal = 12;	//! �}�b�v�̗�
const int kChipWidth = 32;		//! �}�b�v�`�b�v
const int kChipHeight = 32;
const XMFLOAT2 kBlockSize	= { 32.0f , 32.0f };
const XMFLOAT2 kDotSize		= { 16.0f , 16.0f };
const XMFLOAT2 kPlayerSize	= { 32.0f , 32.0f };
const XMFLOAT2 kEnemySize	= { 32.0f , 32.0f };
/* @} */

/**
 * �^
 */

 /**
 * @enum eGameStatus
 * �Q�[���̐i�s��
 */
typedef enum eGameStatus
{
	eNone,
	eOpening,
	ePlaying,
	eGameClear,
	eGameOver,
	eBonusClear,
	eEnding
}eGameStatus;

/**
* @enum ePhase
* �t���[�̐i�s���
*/
typedef enum ePhase
{
	eBegin = 0,
	eMain,
	eEnd,
}ePhase;

/**
* @enum eScrollMode
* �X�N���[������
*/
typedef enum eScrollMode
{
	eHorizontal,
	eVirtical
}eScrollMode;

/**
* @enum eObjectState
* �L�����N�^�̏��
*/
typedef enum eObjectState
{
	eWaiting,
	eMoving
}eObjectStatus;
