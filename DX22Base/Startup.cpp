#include "Main.h"
#include "WinUtil.h"
#include "Timer.h"


//--- �萔��`
const char* APP_TITLE = "DX2D";
const Frame DEFAULT_FPS = 60;

/*
* �G���g���|�C���g
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (FAILED(InitWindow(APP_TITLE, GetAppWidth(), GetAppHeight())))
	{
		Error("window initialize faield");
	}
	InitTimer(DEFAULT_FPS);
	Init();


	//--- �E�B���h�E�̊Ǘ�
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

	// �I����
	Uninit();
	UninitTimer();
	UninitWindow();
	return 0;
}
