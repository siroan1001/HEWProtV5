/*
InitSound�֐���LoadTexture�֐�����ɌĂяo���ƃG���[
��������COM�I�u�W�F�N�g�𗘗p���邽��

���X�i�[
���𕷂����߂́u���v�ɑ����B3D�T�E���h�ŕK�v�B
�\�[�X
���𔭂���u�����v�ɑ����B�X�s�[�J�[�BXAudio2�ł�Voice�ƌĂ΂��B
�o�b�t�@
���f�[�^���i�[���Ă����o�b�t�@�BWAV�t�@�C���AOGG�t�@�C���Ȃǂ��烍�[�h�B
 */
#ifndef __SOUND_H__
#define __SOUND_H__

#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

//----------
// �v���g�^�C�v�錾
//----------
//HRESULT InitSound(void);
//void UninitSound(void);

// �T�E���h�̓ǂݍ���
//XAUDIO2_BUFFER* CreateSound(const char *file, bool loop = false);
// �T�E���h�̍Đ�
//IXAudio2SourceVoice* StartSound(XAUDIO2_BUFFER* pSound);

class Sound
{
public:
	enum SoundKind
	{
		E_SOUND_KIND_BGM_TITLE = 0,
		E_SOUND_KIND_BGM_STAGESELECT,
		E_SOUND_KIND_BGM_CLEAR,
		E_SOUND_KIND_BGM_GAMEOVER,
		E_SOUND_KIND_SE_TITLE,
		E_SOUND_KIND_SE_SELECT,

		E_SOUND_KIND_MAX
	};

public:
	static HRESULT Init();
	static void Unitit();
	static IXAudio2SourceVoice* Start(SoundKind kind);

private:
	static XAUDIO2_BUFFER* m_Sound[E_SOUND_KIND_MAX];

};

#endif // __SOUND_H__