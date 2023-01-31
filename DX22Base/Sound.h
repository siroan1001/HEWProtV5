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
HRESULT InitSound(void);
void UninitSound(void);

// サウンドの読み込み
XAUDIO2_BUFFER* CreateSound(const char *file, bool loop = false);
// サウンドの再生
IXAudio2SourceVoice* StartSound(XAUDIO2_BUFFER* pSound);

#endif // __SOUND_H__