/*
InitSound関数をLoadTexture関数より後に呼び出すとエラー
※内部でCOMオブジェクトを利用するため

リスナー
音を聞くための「耳」に相当。3Dサウンドで必要。
ソース
音を発する「音源」に相当。スピーカー。XAudio2ではVoiceと呼ばれる。
バッファ
音データを格納しておくバッファ。WAVファイル、OGGファイルなどからロード。
 */
#ifndef __SOUND_H__
#define __SOUND_H__

#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

//----------
// プロトタイプ宣言
//----------
//HRESULT InitSound(void);
//void UninitSound(void);

// サウンドの読み込み
//XAUDIO2_BUFFER* CreateSound(const char *file, bool loop = false);
// サウンドの再生
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