/**
* @file GamePGUtil.cpp
* @brief DirectXMath.h -- SIMD C++ Math library, etc
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#include "stdafx.h"
#include "GamePGUtil.h"

/**
* @fn XMFLOAT4 ComputePosByDirectionZ(XMFLOAT4 old_, FLOAT direction_)
* @brief Z�̌�������ʒu�����߂�
* @param old_				�ړ��O�̈ʒu
* @param direction_	����
* @return					�ړ���̈ʒu
*/
XMFLOAT4 ComputePosByDirectionZ(XMFLOAT4 old_, FLOAT direction_)
{
	XMFLOAT4 resultVector;
	XMMATRIX tempMat = XMMatrixRotationZ(XMConvertToRadians(direction_));

	XMStoreFloat4(
		&resultVector,
		XMVector3TransformCoord(XMLoadFloat4(&old_), tempMat));

	return resultVector;
}

/**
 * @fn void debugString(HWND hWnd_, int nXStart_, int nYStart_, LPCTSTR lpString_)
 * @brief Z�̌�������ʒu�����߂�
 * @param hWnd_		WindowsAPI�E�C���h�E�n���h��
 * @param nXStart_	x�ʒu
 * @param nYStart_	y�ʒu
 * @param lpString_	�\�����镶����
 * @return			����
 */
void debugString(HWND hWnd_, int nXStart_, int nYStart_, LPCTSTR lpString_)
{
	HDC hdc = GetDC(hWnd_);
	TextOut(hdc, nXStart_, nYStart_, lpString_, sizeof(lpString_));
	ReleaseDC(hWnd_, hdc);
}

/**
 * @fn HRESULT PutMessage(LPCTSTR lpString_)
 * @brief Z�̌�������ʒu�����߂�
 * @param lpString_	�\�����镶����
 * @return			����
 */
HRESULT PutMessage(LPCTSTR lpString_)
{
	std::cout << lpString_ << std::endl;
	MessageBox(0, lpString_, NULL, MB_OK);
	return GetLastError();
}