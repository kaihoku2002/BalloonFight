/**
* �t�@�C����	�FCSound.cpp
* �T�v		�F�T�E���h�̍쐬��Đ����s��
* �쐬��		�F2021_08_18_�דc��K
*/

#include "stdafx.h"


#include "CSound.h"

CSound::CSound()
	: m_pXaudio2(NULL)
	, m_pSourcevoice(NULL)
	, m_iVolume(100)
	, m_pBuffer(NULL)
	, m_dataSize()
{}



CSound::~CSound()
{}




/// <summary>
/// wav�t�@�C������g�`�f�[�^��ǂݍ���
/// </summary>
/// <param name="filePath_">�Fwav�t�@�C���ւ̃p�X</param>
/// <param name="loop_">�F���[�v���邩�ǂ����̃t���O�i�f�t�H���g��false�Ȃ̂ŁA���[�v����Ƃ�����true��ǉ��œn���j</param>
void CSound::LoadSound(IXAudio2* pXAudio2_, const char* filePath_, const bool loop_ )
{
	m_pXaudio2 = pXAudio2_;	// �����o�ϐ��Ƃ��ĕێ�

	// �I�[�f�B�I�t�@�C���̓ǂݍ���
	FILE* pFile = NULL;

	// errno_t�F�����Ȃ�0���Ԃ��Ă���
	// 0���Ԃ��Ă��Ȃ���΁A���s���Ă���̂Ŗ߂�
	if (fopen_s(&pFile, filePath_, "rb") != 0) { throw; }

	// RIFF�w�b�_�̓ǂݍ���
	RIFFHeader riff;
	fread(&riff, sizeof(riff), 1, pFile);

	// Format�`�����N�̓ǂݍ���
	FormatChunk format;
	fread(&format, sizeof(format), 1, pFile);

	// Data�`�����N�̓ǂݍ���
	Chunk data;
	fread(&data, sizeof(data), 1, pFile);
	// Data�`�����N�̃f�[�^�i�g�`�f�[�^�j������ǂݍ���
	m_pBuffer = (char*)malloc(data.size);
	if (!m_pBuffer) { return; }
	fread(m_pBuffer, data.size, 1, pFile);
	m_dataSize = data.size;
	fclose(pFile);

	WAVEFORMATEX wfex = {};
	// �g�`�t�H�[�}�b�g�̐ݒ�
	memcpy(&wfex, &format.fmt, sizeof(format.fmt));
	wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;

	// �g�`�t�H�[�}�b�g�����Ƀ\�[�X�{�C�X�̍쐬
	HRESULT result = m_pXaudio2->CreateSourceVoice(&m_pSourcevoice, &wfex);
	if (FAILED(result))
	{
		free(m_pBuffer);
		return;
	}

	// �Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buf = {};
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.AudioBytes = m_dataSize;
	buf.pAudioData = (BYTE*)m_pBuffer;
	// ���[�v��true�Ȃ�A�����Ƀ��[�v����ݒ�������킦��
	// IXAudio2SourceVoice::ExitLoop���Ăяo���܂ł͍Đ����ꑱ����
	if (loop_ == true)
	{
		buf.LoopBegin = 0;
		buf.LoopLength = 0;
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	// �ݒ肵���g�`�f�[�^�̃Z�b�g
	m_pSourcevoice->SubmitSourceBuffer(&buf);
}



/// <summary>
/// ���̉������Đ�����
/// </summary>
void CSound::PlaySourcevoice()
{
	m_pSourcevoice->Start();
}



/// <summary>
/// ���̉����̍Đ����~�߂�
/// </summary>
void CSound::StopSourcevoice()
{
	m_pSourcevoice->Stop();
}



/// <summary>
/// ���̉������Đ������ǂ���
/// </summary>
/// <returns>�Đ����Ȃ�ture�A�Đ����łȂ����false</returns>
bool CSound::isPlayed()
{
	if (!m_pSourcevoice) { return false; }

	XAUDIO2_VOICE_STATE state;
	m_pSourcevoice->GetState(&state); 
	// BuffersQueued�F�Đ�����~����Ă���Ȃ玟�ɏ����\��̃o�b�t�@�ւ̃|�C���^������
	// ���ɏ����\��̃o�b�t�@���Ȃ����NULL
	// NULL�Ȃ�Đ�����~���Ă��邱�Ƃ�����
	if (!state.BuffersQueued)	
	{
		return false;
	}

	return true;
}



/// <summary>
/// �T�E���h�̔j��
/// </summary>
void CSound::DeleteSourcevoice()
{
	if (!m_pSourcevoice) { return; }
	m_pSourcevoice->Stop();
	free(m_pBuffer);
	m_pSourcevoice->FlushSourceBuffers();
	m_pSourcevoice->DestroyVoice();
	m_pSourcevoice = NULL;
}




void CSound::ChangeVolume(const __int8 vol_)
{
	// ���ʐݒ�̍ő�l
	constexpr float MAX_VOLUME = 100.f;
	m_iVolume = vol_;
	// 0.f�`1.f�œn���K�v����̂ŁA����Z������
	m_pSourcevoice->SetVolume(static_cast<float>(vol_) / MAX_VOLUME);
}



/// <summary>
/// ���������ēx�Đ��������Ƃ��Ɏg��
/// </summary>
void CSound::ReLoadSource()
{
	if (!m_pSourcevoice) { return; }
	if (!m_pBuffer) { return; }
	// �����Đ����Ȃ��~
	m_pSourcevoice->Stop();
	// �\�[�X�{�C�X�̃o�b�t�@���Y���
	m_pSourcevoice->FlushSourceBuffers();

	// �\�[�X�{�C�X�ɍēx�ۑ�����Ă���o�b�t�@����f�[�^���Z�b�g����
	// �Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buf = {};
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.AudioBytes = m_dataSize;
	buf.pAudioData = (BYTE*)m_pBuffer;

	// �ݒ肵���g�`�f�[�^�̃Z�b�g
	m_pSourcevoice->SubmitSourceBuffer(&buf);
}





CSound* CSound::Create(IXAudio2* pXAudio2_, const char* filePath_, const bool loop_)
{

	CSound* object = new CSound();
	if (object != NULL)
	{
		object->LoadSound(pXAudio2_, filePath_, loop_);
	}
	return object;
}