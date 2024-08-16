/**
* @file GamePGUtil.h
* @brief define�}�N���A�֐�
* @author �D�ˁ@�엲
* @date ���t�i2018.08.09�j
*/
#pragma once

#include "stdafx.h"

/**
 * define�}�N��
 */
 /** @def
 * DirectX���\�[�X�̉��
 */
#define SAFE_RELEASE(x)			{ if(x)	{ x->Release();	x = NULL;	}	}

 /** @def
 * �C���X�^���X�̉��
 */
#define SAFE_release(x)			{ if(x)	{ x->release();	x = NULL;	}	}

 /** @def
 * �C���X�^���X�̍폜
 */
#define SAFE_DELETE(x)			{ if(x)	{ delete x;		x = NULL;	}	}

 /** @def
 * DirectX���\�[�X�z��̉��
 */
#define SAFE_DELETE_ARRAY(x)	{ if(x)	{ delete[] x;	x = NULL;	}	}

 /** @def
 * �폜�Ɖ��
 */
#define SAFE_release_DELETE(x)	{ if(x)	{ x->release(); delete x;	x = NULL;	}	}

 /**
 * �֐�
 */
XMFLOAT4 ComputePosByDirectionZ(XMFLOAT4 old_, FLOAT direction_);
HRESULT PutMessage(LPCTSTR lpString_);
void debugString(HWND hWnd_, int nXStart_, int nYStart_, LPCTSTR lpString_);