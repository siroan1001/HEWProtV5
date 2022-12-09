#include "Main.h"
#include "WinUtil.h"
#include "Timer.h"


//--- 定数定義
const char* APP_TITLE = "DX2D";
const Frame DEFAULT_FPS = 60;

/*
* エントリポイント
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (FAILED(InitWindow(APP_TITLE, GetAppWidth(), GetAppHeight())))
	{
		Error("window initialize faield");
	}
	InitTimer(DEFAULT_FPS);
	Init();


	//--- ウィンドウの管理
	AppState state = APP_STATE_MESSAGE;
	while (state != APP_STATE_QUIT)
	{
		state = UpdateWindow();
		if (state == APP_STATE_WAIT && UpdateTimer())
		{
			Update(GetDeltaTime());
			Draw();
		}
	}

	// 終了時
	Uninit();
	UninitTimer();
	UninitWindow();
	return 0;
}
