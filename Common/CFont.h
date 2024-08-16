
#pragma once 

#include "stdafx.h"
#include "CPicture.h"

class CFont
{
private:
	CPicture**	objects;
	int			digits;

public:
	static CFont* create(
		ID3D11Device* pDevice_,		//!< �f�o�C�X
		ID3D11DeviceContext* pDeviceContext_,//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],	//!< �r���[�|�[�g
		LPCWSTR					shaderName_,	//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,	//!< �摜�t�@�C��
		XMFLOAT4				position_,		//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,			//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels,	//!< �e�N�Z���̔z��
		int						digits_);		//!< ����

	void init(
		ID3D11Device* pDevice_,		//!< �f�o�C�X
		ID3D11DeviceContext* pDeviceContext_,//!< �f�o�C�X�R���e�L�X�g
		D3D11_VIEWPORT			viewPort_[],	//!< �r���[�|�[�g
		LPCWSTR					shaderName_,	//!< �V�F�[�_�[�v���O����
		LPCWSTR					textureName_,	//!< �摜�t�@�C��
		XMFLOAT4				position_,		//!< �E�B���h�E�̈ʒu
		XMFLOAT2				size_,			//!< �X�v���C�g�̑傫��
		std::vector<QuadrangleTexel>	texels,	//!< �e�N�Z���̔z��
		int						digits_
	);

	CFont();
	~CFont();

	void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, int num_, size_t texelIndex_ = 0, XMFLOAT4 diffuse_ = { 0, 0, 0, 0 });
	void release();

	void setPos(float x, float y);
};
