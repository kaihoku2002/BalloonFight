/**
 * @file Common3DType.h
 * @brief DirectX11���x�[�X�ɂ���3D�̊�{�I�ȍ\��
 * @author �D�ˁ@�엲
 * @date ���t�i2017.02.14�j
 */
#pragma once

#include "stdafx.h"
#include "GameConst.h"
#include "GamePGUtil.h"


/**
 * �e�N�Z��
 */

/*! @struct QuadrangleTexel
@brief  �l�p�`�̃e�N�Z��
*/
typedef struct QuadrangleTexel {
	XMFLOAT2 v1 = { 0, 1 };	//!< ���_1
	XMFLOAT2 v2 = { 0, 0 };	//!< ���_2
	XMFLOAT2 v3 = { 1, 1 };	//!< ���_3
	XMFLOAT2 v4 = { 1, 0 };	//!< ���_4
	QuadrangleTexel(XMFLOAT2 v1_, XMFLOAT2 v2_, XMFLOAT2 v3_, XMFLOAT2 v4_){
		v1 = v1_;
		v2 = v2_;
		v3 = v3_;
		v4 = v4_;
	}


}QuadrangleTexel;

/**
 * ���_�̍\���� XMFLOAT3 XMFLOAT4
 */
/*! @struct VertexWithTex
@brief  ���_ <3D/4D�ʒu �e�N�Z��>
*/
template < typename XMFLOAT_X >
struct VertexWithTex
{
	XMFLOAT_X	pos;	//!< �ʒu
	XMFLOAT2	texel;	//!< �e�N�Z��
};

/*! @struct VertexWithNormal
@brief  ���_ <3D/4D�ʒu �@��>
*/
template < typename XMFLOAT_X >
struct VertexWithNormal
{
	XMFLOAT_X	pos;	//!< �ʒu
	XMFLOAT_X	normal;	//!< �@���@�V�F�[�f�B���O�i�A�e�v�Z�j�ɂ͖@���͕K�{
};

/*! @struct Vertex3DWithNormalTexel
@brief  ���_ <3D�ʒu �@�� �e�N�Z��>
*/
template < typename XMFLOAT_X >
struct VertexWithNormalTex
{
	XMFLOAT_X	pos;	//!< �ʒu
	XMFLOAT_X	normal;	//!< �@���@�V�F�[�f�B���O�i�A�e�v�Z�j�ɂ͖@���͕K�{
	XMFLOAT2	texel;	//!< �e�N�Z��
};

/*! @struct VertexBone
@brief  ���_�̍\����
*/
template < typename XMFLOAT_X >
struct VertexBone {
	XMFLOAT_X	pos;			//!< ���_�ʒu
	XMFLOAT_X	normal;			//!< ���_�@��
	XMFLOAT2	texel;			//!< �e�N�Z��	
	UINT		boneIndex[4];	//!< �{�[���@�ԍ�
	FLOAT		boneWeight[4];	//!< �{�[���@�d��
	VertexBone()
	{
//		ZeroMemory (this, sizeof (Vertex3DBone));
	}
};


/**
 * �p���̍\���� XMFLOAT3 XMFLOAT4
 */
/*! @struct Position
@brief  �p��
*/
template < typename XMFLOAT_X >
struct Position
{
	XMFLOAT_X	pos;	//!< �ʒu		
	FLOAT		pitch;	//!< �s�b�`	<X>
	FLOAT		yaw;	//!< ���[	<Y>
	FLOAT		roll;	//!< ���[��	<Z>
	XMFLOAT3	scale;	//!< �X�P�[��

	void setup(XMFLOAT_X pos_, FLOAT pitchDegree_, FLOAT yawDegree_, FLOAT rollDegree_, XMFLOAT3 scale_)
	{
		pos		= pos_;
		pitch	= pitchDegree_;
		yaw		= yawDegree_;
		roll	= rollDegree_;
		scale	= scale_;
	}
	void offset(XMFLOAT4 alpha_)
	{
		pos.x += alpha_.x;
		pos.y += alpha_.y;
		pos.z += alpha_.z;
		pos.w += alpha_.w;
	}
	void normalize(void)
	{
		if (pitch >= 360.0f || pitch < 0.0f) {
			pitch = fmodf((pitch), 360.0f);
		}
		if (yaw >= 360.0f || yaw < 0.0f) {
			yaw = fmodf((yaw), 360.0f);
		}
		if (roll >= 360.0f || roll < 0.0f) {
			roll = fmodf((roll), 360.0f);
		}
	}

	void setAngle(XMFLOAT3 degrees_) {
		pitch	= degrees_.x;
		yaw		= degrees_.y;
		roll	= degrees_.z;
		normalize();		//!< ���K��
	}
};

/**
 * �V�F�[�_�[�ɓn���l
 */

/*! @struct ShaderGlobal_0
@brief  �V�F�[�_�[�ɓn���l
*/
typedef struct ShaderGlobal_0 {
	XMFLOAT4X4	matWVP;		//!< ���[���h����ˉe�܂ł̕ϊ��s��
	XMFLOAT4	diffuse;	//!< �f�B�t���[�Y�F				
}ShaderGlobal_0;

/*! @struct ShaderGlobal_1
@brief  �V�F�[�_�[�E�O���[�o��
*/
typedef struct ShaderGlobal_1 {
	XMFLOAT4X4	matWorld;	//!< ���[���h�s��					
	XMFLOAT4X4	matWVP;		//!< ���[���h����ˉe�܂ł̕ϊ��s��
	XMFLOAT4	lightDir;	//!< ���C�g����					
	XMFLOAT4	diffuse;	//!< �f�B�t���[�Y�F				
}ShaderGlobal_1;

/*! @struct ShaderGlobal_2
@brief  �V�F�[�_�[�ɓn���l
*/
typedef struct ShaderGlobal_2 {
	XMFLOAT4X4	matWorld;		//!< ���[���h�s��					
	XMFLOAT4X4	matWVP;			//!< ���[���h����ˉe�܂ł̕ϊ��s��
	XMFLOAT4	lightDir;		//!< ���C�g����					
	XMFLOAT4	diffuse;		//!< �f�B�t���[�Y�F				
	XMVECTORF32	eye;			//!< �J�����ʒu�i���_�ʒu�j		
}ShaderGlobal_2;

/*! @struct ShaderGlobal_3
@brief  �V�F�[�_�[�E�O���[�o��
*/
typedef struct ShaderGlobal_3 {
	XMFLOAT4X4	matWorld;	//!< ���[���h�s��					
	XMFLOAT4X4	matWVP;		//!< ���[���h����ˉe�܂ł̕ϊ��s��
	XMFLOAT4	ambient;	//!< �A���r�G���g��				
	XMFLOAT4	diffuse;	//!< �f�B�t���[�Y�F				
	XMFLOAT4	specular;	//!< ���ʔ���					
} ShaderGlobal_3;

/*! @struct ShaderGlobal_Bones
@brief  �V�F�[�_�[�ɓn���{�[���s��z��
*/
typedef struct ShaderGlobal_Bones {
	XMFLOAT4X4 matBone[256];
	ShaderGlobal_Bones ()
	{
		for (int i = 0; i < 256; i++)
		{
			XMStoreFloat4x4 (&matBone[i], XMMatrixIdentity ());
		}
	}
}ShaderGlobalBones;

/**
 * �V�F�[�_�[�ɓn���l�@�萔�o�b�t�@
 */

/*! @struct ShaderConstantBufferLE
@brief  �萔�o�b�t�@(���C�g�����ƃJ�����ʒu)
*/
typedef struct ShaderConstantBufferLE  {
	XMFLOAT4 lightDir;	//!< ���C�g����
	XMFLOAT4 eye;		//!< �J�����ʒu
} ShaderConstantBufferLE;

/**
 * FBX
 */

/*! @struct Material
@brief  �}�e���A��
*/
typedef struct Material {
	XMFLOAT4 ambient;				//!< �A���r�G���g	
	XMFLOAT4 diffuse;				//!< �f�B�t���[�Y	
	XMFLOAT4 specular;				//!< �X�y�L�����[	
	CHAR textureName[100];			//!< �e�N�X�`���[�t�@�C����		
	ID3D11ShaderResourceView* pTexture;	//!< �e�N�X�`���[�t�@�C����		
	DWORD numOfFace;					//!< ���̃}�e���A���ł���|���S����
	Material ()
	{
		ZeroMemory(this, sizeof(Material));
	}
	~Material ()
	{
		SAFE_RELEASE(pTexture);
	}
} Material;

/**
 * �{�[��
 */

/*! @struct Bone
@brief  �{�[���\����
*/
typedef struct Bone {
	XMFLOAT4X4 matBindPose;	//!< �����|�[�Y�i�����ƕς��Ȃ��j
	XMFLOAT4X4 matNewPose;	//!< ���݂̃|�[�Y�i���̓s�x�ς��j
	Bone ()
	{
		ZeroMemory (this, sizeof (Bone));
	}
}Bone;

/*! @struct PolyTable
@brief  �P���_�̋��L�@�ő�20�|���S���܂�
*/
typedef struct PolyTable {
	int polyIndex[20];	//!< �|���S���ԍ�			
	int index123[20];	//!< 3�̒��_�̂����A���Ԗڂ�
	int numOfRef;		//!< �����Ă���|���S����	
	PolyTable ()
	{
		ZeroMemory (this, sizeof (PolyTable));
	}
}PolyTable;