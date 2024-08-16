/**
* @file CTexture.h
* @brief �e�N�X�`���E�N���X
* @author �D�ˁ@�엲
* @date ���t�i2018.07.27�j
*/
#pragma once

#include "stdafx.h"

class CTexture
{
private:
	ID3D11SamplerState*			m_pSampleLinear = NULL;	//!< �e�N�X�`���[�̃T���v���[
	ID3D11ShaderResourceView*	m_pTexture		= NULL;	//!< �e�N�X�`���[

public:
	static std::unique_ptr<CTexture> create(
		ID3D11Device*			pDevice_,		//!< �f�o�C�X
		LPCWSTR					textureName_);	//!< �摜�t�@�C��
	void init(
		ID3D11Device*			pDevice_,		//!< �f�o�C�X
		LPCWSTR					textureName_);	//!< �摜�t�@�C��
	
	CTexture();
	~CTexture();
	void setup(ID3D11DeviceContext*	pDeviceContext_);
	void release();
};