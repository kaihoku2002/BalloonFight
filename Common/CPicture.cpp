/**
* @file CPicture.cpp
* @brief �e�N�Z���t���̃s�N�`���[�E�N���X
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/

#include "stdafx.h"
#include "CPicture.h"
#include "UVAnimation.h"

/**
* @fn std::unique_ptr<CPicture> CPicture::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
* @brief �C���X�^���X�𐶐��������� �y�N���X���\�b�h�z
* @param pDevice_			�f�o�C�X
* @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
* @param viewPort_[]		�r���[�|�[�g
* @param shaderName_		�V�F�[�_�[�v���O����
* @param textureName_		PNG�t�@�C��
* @param position_			�E�B���h�E�̈ʒu
* @param size_				�X�v���C�g�̑傫��
* @param texels			�e�N�Z���̔z��
* @return					CPicture�̃��j�[�N�|�C���^
*/
/*
std::unique_ptr<CPicture> CPicture::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	std::unique_ptr<CPicture> object = unique_ptr<CPicture>(new CPicture());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, position_, size_, texels);
	return object;
}
*/

CPicture* CPicture::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	CPicture* object = new CPicture ();
	if( object != NULL)
	{
		object->init (pDevice_, pDeviceContext_, viewPort_, shaderName_, textureName_, position_, size_, texels);
	}
	return object;
}

/**
* @fn void CPicture::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
* @brief �C���X�^���X��������
* @param pDevice_			�f�o�C�X
* @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
* @param viewPort_[]		�r���[�|�[�g
* @param shaderName_		�V�F�[�_�[�v���O����
* @param textureName_		PNG�t�@�C��
* @param position_			�E�B���h�E�̈ʒu
* @param size_				�X�v���C�g�̑傫��
* @param texels			�e�N�Z���̔z��
* @return					����
*/
void CPicture::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, LPCWSTR textureName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	super::init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, texels);

	if (textureName_ != NULL)
	{
		/**
		* �e�N�X�`���[�쐬(�T���v���[���܂�) DirectXTex <WindowsSDK 10>
		*/
		m_pPolygonTex = CTexture::create(pDevice_, textureName_);
	}
}

CPicture::CPicture()
{
}

CPicture::~CPicture()
{
	m_pPolygon.reset();
	m_pPolygonTex.reset();
}

/**
* @fn void CPicture::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, size_t texelIndex_, XMFLOAT4 diffuse_)
* @brief �����_�����O
* @param matView_	�r���[�s��
* @param matProj_	�v���W�F�N�V�����s��
* @param texelIndex_	�e�N�Z���E�C���f�b�N�X
* @param diffuse_	�f�B�t���[�Y
* @return			����
*/
void CPicture::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, size_t texelIndex_, XMFLOAT4 diffuse_)
{
	if (!m_active)
	{
		return;
	}

	computeMatrixFromPos();

	//! �V�F�[�_�[�@�萔�o�b�t�@
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(m_pDeviceContext->Map(
		m_pConstantBuffer,			//!< �}�b�v���郊�\�[�X
		0, 							//!< �T�u���\�[�X�̃C���f�b�N�X�ԍ�
		D3D11_MAP_WRITE_DISCARD,	//!< �������݃A�N�Z�X
		0,
		&pData)))					//!< �f�[�^�̏������ݐ�|�C���^
	{
		ShaderGlobal_0 sg;
		XMStoreFloat4x4(&sg.matWVP, XMLoadFloat4x4(&m_mFinalWorld) * XMLoadFloat4x4(&matView_) * XMLoadFloat4x4(&matProj_));
		XMStoreFloat4x4(&sg.matWVP, XMMatrixTranspose(XMLoadFloat4x4(&sg.matWVP)));
		sg.diffuse = diffuse_;
		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(ShaderGlobal_0));

		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	m_pDeviceContext->IASetInputLayout(m_pInputLayout);									//!< ���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//!< �v���~�e�B�u�E�g�|���W�[���Z�b�g
	UINT stride = sizeof(VertexWithTex<XMFLOAT3>);
	UINT offset = 0;
//	m_pDeviceContext->IASetVertexBuffers (0, 1, &m_pVertexBuffer[texelIndex_], &stride, &offset);//!< ���_�o�b�t�@�[���Z�b�g
	m_pDeviceContext->IASetVertexBuffers (0, 1, &m_pVertexBuffer[m_animIndex], &stride, &offset);//!< ���_�o�b�t�@�[���Z�b�g
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);							//!< �g�p����V�F�[�_�[�̓o�^�@�ieffect�́h�e�N�j�b�N�h�ɑ����j
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);					//!< VS�ɒ萔�o�b�t�@��ݒ�
	m_pDeviceContext->RSSetViewports(1, m_viewPort);									//!< RS�Ƀr���[�|�[�g��ݒ�
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);								//!< PS�Ƀs�N�Z���E�V�F�[�_��ݒ�
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);					//!< PS�ɒ萔�o�b�t�@��ݒ�
	//! �T���v���[�ƃe�N�X�`���[�̐ݒ�
	m_pPolygonTex->setup(m_pDeviceContext);
	m_pDeviceContext->Draw(4, 0);														//!<  �v���~�e�B�u�������_�����O
}

/**
* @fn void CPicture::release()
* @brief �����[�X
* @param	����
* @return	����
*/
void CPicture::release()
{
	/**
	*  �K�����������̂Ƌt�̏��ԂŃ����[�X
	*/
	super::release();
	m_pPolygonTex->release();
}

/**
 * @fn		void CPicture::stepAnimation()
 * @brief	�A�j���[�V�����J��
 * @param	����
 * @return	����
 */
void CPicture::stepAnimation ()
{
	m_animIndex++;
	if( m_animBeginIndex == m_animEndIndex)
	{
		m_animIndex = m_animIndex >= m_texels.size () ? 0 : m_animIndex;
	}
	else
	{
		m_animIndex = m_animIndex > m_animEndIndex ? m_animBeginIndex : m_animIndex;
	}
}

/**
 * @fn		void CPicture::setAnimation( int animIndex_)
 * @brief	�A�j���[�V�������C���f�b�N�X�Őݒ�
 * @param	animIndex_		�A�j���[�V�����̃C���f�b�N�X�ԍ�(kTexelXXX�̗v�f�ԍ�)
 * @return	����
 */
void CPicture::setAnimation( int animIndex_)
{
	m_animIndex = animIndex_;
}

/**
 * @fn		void CPicture::setAnimationRange( int animBeginIndex_, int animEndIndex_)
 * @brief	�A�j���[�V�����J�ڂ̃C���f�b�N�X�͈͂�ݒ�(stepAnimation()�Ŏ����I�A�j���[�V�������s����͈�)
 * @note	�ݒ肵�����_�ł̃A�j���[�V�����C���f�b�N�X���͈͊O�������ꍇ�͊J�n�C���f�b�N�X�Ƀ��Z�b�g���܂��B
 * @note	animBeginIndex_ > animEndIndex_ �̏ꍇ�͖����ł��B
 * @param	animBeginIndex_		�J�n�C���f�b�N�X
 * @param	animEndIndex_		�I���C���f�b�N�X
 * @return	����
 */

void CPicture::setAnimationRange( int animBeginIndex_, int animEndIndex_)
{
	if( animBeginIndex_ > animEndIndex_)
	{
		return;
	}

	m_animBeginIndex = animBeginIndex_;
	m_animEndIndex = animEndIndex_;
	if( m_animIndex < m_animBeginIndex || m_animEndIndex < m_animIndex)
	{
		m_animIndex = m_animBeginIndex;
	}
}
