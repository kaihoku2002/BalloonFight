/**
* �t�@�C����	�FCSound.h
* �T�v		�F�T�E���h�̍쐬��Đ����s��
* �쐬��		�F2021_08_18_�דc��K
*/

#pragma once


//using Microsoft::WRL::ComPtr;

class CSound
{
	IXAudio2* m_pXaudio2;	// CXAudio2�N���X��m_pXaudio2�̃|�C���^���擾����

	IXAudio2SourceVoice* m_pSourcevoice;	// �\�[�X�{�C�X
	__int8 m_iVolume;	// ���̉����̉��ʁF�O�`�P�O�O�Őݒ�

	char* m_pBuffer;	// �g�`�f�[�^�̃o�b�t�@

	// �`�����N�f�[�^�̊�{�\��
	struct Chunk
	{
		char id[4];	// �`�����N����ID
		uint32_t size;	// �`�����N�T�C�Y
	};
	// RIFF�w�b�_
	struct RIFFHeader
	{
		Chunk chunk;	// "RIFF"
		char type[4];	// "WAVE"�FWAVE�t�@�C���̓ǂݍ��݂�����̂�WAVE������
	};
	// FMT�`�����N
	struct FormatChunk
	{
		Chunk chunk;	// "fmt"
		WAVEFORMAT fmt;	// �g�`�t�H�[�}�b�g
	};

	uint32_t m_dataSize;	// �`�����N�T�C�Y
public:
	CSound();
	~CSound();

	void LoadSound(IXAudio2* pXAudio2_, const char* filePath_, const bool loop_ = false);
	void PlaySourcevoice();
	void StopSourcevoice();
	void DeleteSourcevoice();


	void ExitLoopSource() { m_pSourcevoice->ExitLoop(); }	// ���[�v�����̂Ƃ��A���݂̍Đ����I������烋�[�v�Đ����~����
	void ReLoadSource();	// �ēx�������𗬂������Ƃ��p�̊֐�

	bool isPlayed();	// ���̉������Đ������ǂ���
	IXAudio2SourceVoice* getSourcevoice()const { if (m_pSourcevoice) { return m_pSourcevoice; } else { return NULL; } }

	void ChangeVolume(const __int8 vol_);	// ���ʂ̕ύX
	void setVolumeMute() { m_pSourcevoice->SetVolume(0.f); }	// ���̉����̃{�����[����0�ɂ���

	static CSound* Create(IXAudio2* pXAudio2_, const char* filePath_, const bool loop_ = false);
};