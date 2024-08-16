/**
* @file CPicture.h
* @brief �e�N�Z���t���̃s�N�`���[�E�E�N���X
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"
#include "CQuadPolygon.h"
#include "CTexture.h"

/*! @class CPicture
@brief  �|���S���E�N���X
*/
class CPicture :
	public CQuadPolygon
{
	typedef CQuadPolygon super;
private:
	std::unique_ptr<CQuadPolygon>	m_pPolygon = NULL;
	std::unique_ptr<CTexture>				m_pPolygonTex = NULL;
//	int								m_animIndex = 0;
public:
	/*
	static std::unique_ptr<CPicture> create (
		ID3D11Device*			pDevice_,		//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],	//!< �r���[�|�[�g
		LPCWSTR					shaderName_,	//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,	//!< �摜�t�@�C��
		XMFLOAT4				position_,		//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,			//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels);		//!< �e�N�Z���̔z��
	*/
	static CPicture* create (
		ID3D11Device*			pDevice_,		//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],	//!< �r���[�|�[�g
		LPCWSTR					shaderName_,	//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,	//!< �摜�t�@�C��
		XMFLOAT4				position_,		//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,			//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels);		//!< �e�N�Z���̔z��

	CPicture();
	virtual ~CPicture();
	virtual void init(
		ID3D11Device*			pDevice_,		//!< �f�o�C�X
		ID3D11DeviceContext*	pDeviceContext_,//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],	//!< �r���[�|�[�g
		LPCWSTR					shaderName_,	//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,	//!< �摜�t�@�C��
		XMFLOAT4				position_,		//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,			//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels);		//!< �e�N�Z���̔z��
	virtual void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, size_t texelIndex_ = 0, XMFLOAT4 diffuse_ = { 0, 0, 0, 0 });
	void release();
	void stepAnimation ();
	void setAnimation ( int animIndex);
	void setAnimationRange( int animBeginIndex_, int animEndIndex_);
};
