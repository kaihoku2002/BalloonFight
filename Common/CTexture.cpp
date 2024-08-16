/**
* @file CTexture.cpp
* @brief �e�N�Z���E�N���X
* @author �D�ˁ@�엲
* @date ���t�i2018.07.27�j
*/
#include "stdafx.h"
#include "CTexture.h"
#include "GamePGUtil.h"

/**
* @fn std::unique_ptr<CTexture> CTexture::create(ID3D11Device* pDevice_, LPCWSTR textureName_)
* @brief �C���X�^���X�𐶐��������� �y�N���X���\�b�h�z
* @param pDevice_			�f�o�C�X
* @param textureName_		PNG�t�@�C��
* @return					CTexture�̃��j�[�N�|�C���^
*/
std::unique_ptr<CTexture> CTexture::create(ID3D11Device* pDevice_, LPCWSTR textureName_)
{
	std::unique_ptr<CTexture> object = unique_ptr<CTexture>(new CTexture());
	object->init(pDevice_, textureName_);
	return object;
}


/**
* @fn void CTexture::init(ID3D11Device* pDevice_, LPCWSTR textureName_)
* @brief �C���X�^���X��������
* @param pDevice_			�f�o�C�X
* @param textureName_		PNG�t�@�C��
* @return					����
*/
void CTexture::init(ID3D11Device* pDevice_, LPCWSTR textureName_)
{
	/**
	* �e�N�X�`���[�쐬(�T���v���[���܂�) DirectXTex <WindowsSDK 10>
	*/
	if (textureName_ == NULL)
		return;

	/**
	* �e�N�X�`���[�p�T���v���[�쐬
	*/
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC; //!< D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 2;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = -FLT_MAX;
	samplerDesc.MaxLOD = FLT_MAX;

	pDevice_->CreateSamplerState(&samplerDesc, &m_pSampleLinear);
	/**
	* �e�N�X�`���[�쐬 DirectXTex <WindowsSDK 10>
	*/
	if (FAILED(CreateWICTextureFromFile(pDevice_, textureName_, NULL, &m_pTexture)))
	{
		TCHAR   str[256];
		wsprintf(str, L"CTexture::init <CreateWICTextureFromFile>�e�N�X�`���[�쐬���s %s", textureName_);	//!< �e�N�X�`���t�@�C������t������
		throw str;
	}
}

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
}

/**
* @fn BOOL CTexture::setup()
* @brief �e�N�X�`���[
* @param		����
* @return		����
*/
void CTexture::setup(ID3D11DeviceContext*	pDeviceContext_)
{
	pDeviceContext_->PSSetSamplers(0, 1, &m_pSampleLinear);	//!< PS�ɃT���v���[��ݒ�
	pDeviceContext_->PSSetShaderResources(					//!< �e�N�X�`���[���V�F�[�_�[�ɓn��
		0, //!< �ݒ肷��ŏ��̃X���b�g�ԍ�
		1, //!< �ݒ肷��V�F�[�_�E���\�[�X�E�r���[�̐�
		&m_pTexture);	//!< �ݒ肷��V�F�[�_�E���\�[�X�E�r���[�̔z��
}

/**
* @fn void CTexture::release()
* @brief �����[�X
* @param	����
* @return	����
*/
void CTexture::release()
{
	/**
	*  �K�����������̂Ƌt�̏��ԂŃ����[�X
	*/
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSampleLinear);
}