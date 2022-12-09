#ifndef __WIN_UTIL_H__
#define __WIN_UTIL_H__

#include <windows.h>

//--- 定義
enum AppState
{
	APP_STATE_MESSAGE,
	APP_STATE_WAIT,
	APP_STATE_QUIT
};

//--- プロトタイプ宣言
HRESULT InitWindow(LPCSTR appName, LONG width, LONG height);
void UninitWindow();
AppState UpdateWindow();
HWND GetHWND();
void Error(const char* mes);

#endif // __WIN_UTIL_H__