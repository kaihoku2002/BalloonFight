/**
* @file CQuadPolygon.cpp
* @brief �|���S���E�N���X
* @author �D�ˁ@�엲
* @date ���t�i2018.07.27�j
*/

#include "stdafx.h"
#include "CQuadPolygon.h"

/**
* @fn std::unique_ptr<CQuadPolygon> CQuadPolygon::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
* @brief �C���X�^���X�𐶐��������� �y�N���X���\�b�h�z
* @param pDevice_			�f�o�C�X
* @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
* @param viewPort_[]		�r���[�|�[�g
* @param shaderName_		�V�F�[�_�[�v���O����
* @param position_			�E�B���h�E�̈ʒu
* @param size_				�X�v���C�g�̑傫��
* @param texels			�e�N�Z���̔z��
* @return					CQuadPolygon�̃��j�[�N�|�C���^
*/
std::unique_ptr<CQuadPolygon> CQuadPolygon::create(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	std::unique_ptr<CQuadPolygon> object = unique_ptr<CQuadPolygon>(new CQuadPolygon());
	object->init(pDevice_, pDeviceContext_, viewPort_, shaderName_, position_, size_, texels);
	return object;
}

/**
* @fn void CQuadPolygon::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel> texels)
* @brief �C���X�^���X��������
* @param pDevice_			�f�o�C�X
* @param pDeviceContext_	�f�o�C�X�R���e�L�X�g
* @param viewPort_[]		�r���[�|�[�g
* @param shaderName_		�V�F�[�_�[�v���O����
* @param position_			�E�B���h�E�̈ʒu
* @param size_				�X�v���C�g�̑傫��
* @param texels			�e�N�Z���̔z��
* @return					����
*/
void CQuadPolygon::init(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_, D3D11_VIEWPORT viewPort_[], LPCWSTR shaderName_, XMFLOAT4 position_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	m_damage = FALSE;
	m_pDeviceContext = pDeviceContext_;	//!< �����_�����O�ɕK�v�@�����s���ɕω����Ȃ���
	m_viewPort[0] = viewPort_[0];		//!< �����_�����O�ɕK�v�@�����s���ɕω����Ȃ���
	m_originalSize = size_;
	m_VBSize = size_;
	m_active = TRUE;
	m_state = eWaiting;
	m_position.setup({ position_.x, position_.y, position_.z, 0.0f }, 0.0f, 0.0f, 0.0f, XMFLOAT3(1.0f, 1.0f, 1.0f));	//!< �ʒu

	createVertexShader(pDevice_, shaderName_);		//!<���_�E�V�F�[�_�̍쐬
	createVertexInputLayout(pDevice_);					//!<���_�C���v�b�g���C�A�E�g���쐬
	createPixelShader(pDevice_, shaderName_);		//!<�s�N�Z���E�V�F�[�_�̍쐬
	createVertexBuffer(pDevice_, size_, texels);	//!<���_�o�b�t�@�[�쐬
	createConstBuffer(pDevice_);								//!<�萔�o�b�t�@�쐬
}

void CQuadPolygon::createVertexShader(ID3D11Device* pDevice_, LPCWSTR shaderName_)
{
	HRESULT hr;
	ID3DBlob *pErrors = NULL;
	/**
	* hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��
	*/
	hr = D3DCompileFromFile(
		shaderName_,	 //!< �t�@�C����
		NULL,			 //!< �}�N����`(�Ȃ�)
		NULL,			 //!< �C���N���[�h�E�t�@�C����`(�Ȃ�)
		"VS",			 //!< �uVS�֐��v���V�F�[�_������s�����
		"vs_5_0",		 //!< ���_�V�F�[�_
		0,				 //!< �R���p�C���E�I�v�V����
		0,				 //!< �G�t�F�N�g�̃R���p�C���E�I�v�V����(�Ȃ�)
		&m_pBlobVS,		 //!< �R���p�C�����ꂽ�o�C�g�E�R�[�h
		&pErrors);		 //!< �G���[���b�Z�[�W

	SAFE_RELEASE(pErrors);
	if (FAILED(hr))
	{
		TCHAR   str[256];
		wsprintf(str, L"CQuadPolygon::init HLSL (VS)�ǂݍ��ݎ��s %s", shaderName_);
		throw str;
	}
	/**
	* �u���u���璸�_�V�F�[�_�[�쐬
	*/
	hr = pDevice_->CreateVertexShader(
		m_pBlobVS->GetBufferPointer(),	//!< �o�C�g�E�R�[�h�ւ̃|�C���^
		m_pBlobVS->GetBufferSize(),		//!< �o�C�g�E�R�[�h�̒���
		NULL,
		&m_pVertexShader);				//!< ���_�V�F�[�_���󂯎��ϐ�
	if (FAILED(hr))
	{
		SAFE_RELEASE(m_pBlobVS);			//!< �o�C�g�E�R�[�h�����
		throw L"CQuadPolygon::init ���_�V�F�[�_�[�쐬���s";
	}
}

void CQuadPolygon::createVertexInputLayout(ID3D11Device* pDevice_)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//!< �V�O�l�`��
			0,								//!< �����̃Z�}���e�B�b�N�E�C���f�b�N�X�ԍ�
			DXGI_FORMAT_R32G32B32_FLOAT,	//!< �G�������g�̃t�H�[�}�b�g
			0,								//!< ���̓X���b�g�ԍ�
			0,								//!< �擪�܂ł̃I�t�Z�b�g�l�i�o�C�g���j
			D3D11_INPUT_PER_VERTEX_DATA,	//!< ���̓f�[�^�͊e���_�̃f�[�^
			0								//!< �C���X�^���X���̌J��Ԃ���
		},
		{
			"TEXCOORD",						//!< �V�O�l�`��
			0,								//!< �����̃Z�}���e�B�b�N�E�C���f�b�N�X�ԍ�
			DXGI_FORMAT_R32G32_FLOAT,		//!< �G�������g�̃t�H�[�}�b�g
			0,								//!< ���̓X���b�g�ԍ�
			sizeof(XMFLOAT3),				//!< �擪�܂ł̃I�t�Z�b�g�l�i�o�C�g���j
			D3D11_INPUT_PER_VERTEX_DATA,	//!< ���̓f�[�^�͊e���_�̃f�[�^
			0								//!< �C���X�^���X���̌J��Ԃ���
		}
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	/**
	* ���_�C���v�b�g���C�A�E�g���쐬
	*/
	if (FAILED(pDevice_->CreateInputLayout(layout, numElements, m_pBlobVS->GetBufferPointer(), m_pBlobVS->GetBufferSize(), &m_pInputLayout)))
		throw L"CQuadPolygon::init ���_�C���v�b�g���C�A�E�g�쐬���s";
}

void CQuadPolygon::createPixelShader(ID3D11Device* pDevice_, LPCWSTR shaderName_)
{
	HRESULT hr;
	ID3DBlob *pErrors = NULL;
	/**
	* �u���u����s�N�Z���V�F�[�_�[�쐬
	*/
	hr = D3DCompileFromFile(
		shaderName_,	//!< �t�@�C����
		NULL,			//!< �}�N����`(�Ȃ�)
		NULL,			//!< �C���N���[�h�E�t�@�C����`(�Ȃ�)
		"PS",			//!< �uPS�֐��v���V�F�[�_������s�����
		"ps_5_0",		//!< �s�N�Z���E�V�F�[�_
		0,				//!< �R���p�C���E�I�v�V����
		0,				//!< �G�t�F�N�g�̃R���p�C���E�I�v�V����(�Ȃ�)
		&m_pBlobVS,		//!< �R���p�C�����ꂽ�o�C�g�E�R�[�h
		&pErrors);		//!< �G���[���b�Z�[�W

	SAFE_RELEASE(pErrors);
	if (FAILED(hr))
	{
		TCHAR   str[256];
		wsprintf(str, L"CQuadPolygon::init HLSL (PS)�ǂݍ��ݎ��s %s", shaderName_);
		throw str;
	}
	hr = pDevice_->CreatePixelShader(
		m_pBlobVS->GetBufferPointer(),	//!< �o�C�g�E�R�[�h�ւ̃|�C���^
		m_pBlobVS->GetBufferSize(),		//!< �o�C�g�E�R�[�h�̒���
		NULL,
		&m_pPixelShader);				//!< �s�N�Z���E�V�F�[�_���󂯎��ϐ�
	SAFE_RELEASE(m_pBlobVS);				//!< �o�C�g�E�R�[�h�����
	if (FAILED(hr))
		throw L"CQuadPolygon::init �s�N�Z���V�F�[�_�[�쐬���s";
}

void CQuadPolygon::createVertexBuffer(ID3D11Device* pDevice_, XMFLOAT2 size_, std::vector<QuadrangleTexel>	texels)
{
	m_VBLeftTop = { 0.0f - (size_.x / 2.0f), 0.0f - (size_.y / 2.0f) };
	m_VBRightBottom = { 0.0f + (size_.x / 2.0f), 0.0f + (size_.y / 2.0f) };
	m_texels = texels;
	for (size_t i = 0; i < texels.size(); i++)
	{
		VertexWithTex<XMFLOAT3> vertices[] =
		{
		{ XMFLOAT3(m_VBLeftTop.x,		m_VBLeftTop.y,		0),texels[i].v1 },	//!<���_1
		{ XMFLOAT3(m_VBLeftTop.x,		m_VBRightBottom.y,	0),texels[i].v2 },	//!<���_2
		{ XMFLOAT3(m_VBRightBottom.x,	m_VBLeftTop.y,		0),texels[i].v3 },	//!<���_3
		{ XMFLOAT3(m_VBRightBottom.x,	m_VBRightBottom.y,	0),texels[i].v4 }		//!<���_4	
		};

		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DYNAMIC; //!< D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VertexWithTex<XMFLOAT3>) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		ID3D11Buffer*		pVB;
		initData.pSysMem = vertices;
		if (FAILED(pDevice_->CreateBuffer(&bd, &initData, &pVB)))
		{
			throw L"CQuadPolygon::init ���_�o�b�t�@�쐬���s";
		}
		m_pVertexBuffer.push_back(pVB);
	}

}
void CQuadPolygon::createConstBuffer(ID3D11Device* pDevice_)
{
	D3D11_BUFFER_DESC cb;
	cb.Usage = D3D11_USAGE_DYNAMIC;				 //!< ���I(�_�C�i�~�b�N)�g�p�@
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	 //!< �萔�o�b�t�@
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	 //!< CPU���珑������
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	cb.ByteWidth = sizeof(ShaderGlobal_0);						//!< �o�b�t�@�E�T�C�Y
	if (FAILED(pDevice_->CreateBuffer(&cb, NULL, &m_pConstantBuffer))) //!< �萔�o�b�t�@�̍쐬�@�����ł͕ϊ��s��n���p
	{
		throw L"CQuadPolygon::init �萔�o�b�t�@�쐬���s";
	}
}

CQuadPolygon::CQuadPolygon()
{
}

CQuadPolygon::~CQuadPolygon()
{
}

/**
* @fn void CQuadPolygon::computeMatrixFromPos (void)
* @brief ���[���h�s������߂�
* @param					����
* @param					����
* @return					����
*/
void CQuadPolygon::computeMatrixFromPos(void)
{
	XMMATRIX scale = XMMatrixScaling(m_position.scale.x, m_position.scale.y, m_position.scale.z);
	XMMATRIX pitch = XMMatrixRotationX(XMConvertToRadians(m_position.pitch));
	XMMATRIX yaw = XMMatrixRotationY(XMConvertToRadians(m_position.yaw));
	XMMATRIX roll = XMMatrixRotationZ(XMConvertToRadians(m_position.roll));
	XMMATRIX trans = XMMatrixTranslation(getPos().x, getPos().y, getPos().z);
	XMMATRIX finalWorld = scale * pitch * yaw * roll * trans;

	XMStoreFloat4x4(&m_matScale, scale);
	XMStoreFloat4x4(&m_matPitch, pitch);
	XMStoreFloat4x4(&m_matYaw, yaw);
	XMStoreFloat4x4(&m_matRoll, roll);
	XMStoreFloat4x4(&m_matTran, trans);
	XMStoreFloat4x4(&m_mFinalWorld, finalWorld);
}

/**
* @fn void CQuadPolygon::render(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_, size_t texelIndex_, XMFLOAT4 diffuse_)
* @brief �����_�����O
* @param matView_	�r���[�s��
* @param matProj_	�v���W�F�N�V�����s��
* @param texelIndex_	�e�N�Z���E�C���f�b�N�X
* @param diffuse_	�f�B�t���[�Y
* @return			����
*/
void CQuadPolygon::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, std::function<void(ID3D11DeviceContext* pDeviceContext_)> callbackTextureProc_, size_t texelIndex_, XMFLOAT4 diffuse_) {
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
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer[texelIndex_], &stride, &offset);//!< ���_�o�b�t�@�[���Z�b�g
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);							//!< �g�p����V�F�[�_�[�̓o�^�@�ieffect�́h�e�N�j�b�N�h�ɑ����j
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);					//!< VS�ɒ萔�o�b�t�@��ݒ�
	m_pDeviceContext->RSSetViewports(1, m_viewPort);									//!< RS�Ƀr���[�|�[�g��ݒ�
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);								//!< PS�Ƀs�N�Z���E�V�F�[�_��ݒ�
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);					//!< PS�ɒ萔�o�b�t�@��ݒ�
																						//! �T���v���[�ƃe�N�X�`���[�̐ݒ�
	callbackTextureProc_(m_pDeviceContext);												//! �T���v���[�ƃe�N�X�`���[�͗��p�҂ŗp�ӂ���
	m_pDeviceContext->Draw(4, 0);														//!<  �v���~�e�B�u�������_�����O
}

/**
* @fn BOOL CQuadPolygon::collision(XMFLOAT4 pos_, FLOAT range_)
* @brief �Փ�
* @param pos_	�ʒu
* @param range_	�Փ˂͈̔�
* @return		�Փ�
*/
BOOL CQuadPolygon::collision(XMFLOAT4 pos_, FLOAT range_)
{
	return collision(pos_, getPos(), range_);
}

BOOL CQuadPolygon::collision(XMFLOAT2 pos_, FLOAT range_)
{
	XMFLOAT4 pos = getPos();
	FLOAT dist2 =
		(pos_.x - pos.x) * (pos_.x - pos.x) +
		(pos_.y - pos.y) * (pos_.y - pos.y);
	return dist2 <= (range_ * range_);
}

BOOL CQuadPolygon::collision( XMFLOAT2 pos_)
{
	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	float myLeft = myPos.x - (mySize.x / 2.0f);
	float myTop = myPos.y + (mySize.y / 2.0f);
	float myRight = myPos.x + (mySize.x / 2.0f);
	float myBottom = myPos.y - (mySize.y / 2.0f);

	bool ret = (myLeft <= pos_.x && pos_.x <= myRight) && (myBottom <= pos_.y && pos_.y <= myTop);
	return ret;
}

/**
* @fn BOOL CQuadPolygon::collision(XMFLOAT4 pos1_, XMFLOAT4 pos2_, FLOAT range_)
* @brief �Փ�
* @param pos1_	�ʒu
* @param pos2_	�ʒu
* @param range_	�Փ˂͈̔�
* @return		�Փ�
*/
BOOL CQuadPolygon::collision(XMFLOAT4 pos1_, XMFLOAT4 pos2_, FLOAT range_)
{
	FLOAT dist2 =
		(pos1_.x - pos2_.x) * (pos1_.x - pos2_.x) +
		(pos1_.y - pos2_.y) * (pos1_.y - pos2_.y) +
		(pos1_.z - pos2_.z) * (pos1_.z - pos2_.z);

	return dist2 <= (range_ * range_);
}
BOOL CQuadPolygon::collision(CQuadPolygon* target_)
{
	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	float myLeft	= myPos.x - (mySize.x / 2.0f);
	float myTop		= myPos.y + (mySize.y / 2.0f);
	float myRight	= myPos.x + (mySize.x / 2.0f);
	float myBottom	= myPos.y - (mySize.y / 2.0f);
	XMFLOAT4 targetPos = target_->getPos();
	XMFLOAT2 targetSize = target_->getSize();
	float targetLeft	= targetPos.x - (targetSize.x / 2.0f);
	float targetTop		= targetPos.y + (targetSize.y / 2.0f);
	float targetRight	= targetPos.x + (targetSize.x / 2.0f);
	float targetBottom	= targetPos.y - (targetSize.y / 2.0f);

	return (myLeft < targetRight && myTop > targetBottom && myRight > targetLeft && myBottom < targetTop);
}

BOOL CQuadPolygon::collisionOffset(CQuadPolygon* target_, XMFLOAT4 offset_, XMFLOAT2 scale_)
{

	XMFLOAT4 myPos = getPos();
	XMFLOAT2 mySize = getSize();
	myPos.x += offset_.x;
	myPos.y += offset_.y;
	myPos.z += offset_.z;
	myPos.w += offset_.w;
	float myLeft = myPos.x - (mySize.x * scale_.x);
	float myTop = myPos.y + (mySize.y * scale_.y);
	float myRight = myPos.x + (mySize.x * scale_.x);
	float myBottom = myPos.y - (mySize.y * scale_.y);
	XMFLOAT4 targetPos = target_->getPos();
	XMFLOAT2 targetSize = target_->getSize();
	float targetLeft = targetPos.x - (targetSize.x / 2.0f);
	float targetTop = targetPos.y + (targetSize.y / 2.0f);
	float targetRight = targetPos.x + (targetSize.x / 2.0f);
	float targetBottom = targetPos.y - (targetSize.y / 2.0f);

	return (myLeft < targetRight && myTop > targetBottom && myRight > targetLeft&& myBottom < targetTop);
}


/**
* @fn void CQuadPolygon::release()
* @brief �����[�X
* @param	����
* @return	����
*/
void CQuadPolygon::release()
{
	/**
	*  �K�����������̂Ƌt�̏��ԂŃ����[�X
	*/
	SAFE_RELEASE(m_pConstantBuffer);
	for (size_t i = 0; i < m_pVertexBuffer.size(); i++)
	{
		SAFE_RELEASE(m_pVertexBuffer[i]);
	}
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexShader);
}
