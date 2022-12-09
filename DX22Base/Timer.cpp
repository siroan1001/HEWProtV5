#include "Timer.h"
#include "WinUtil.h"

#pragma comment(lib, "winmm.lib")

//--- ƒOƒ[ƒoƒ‹•Ï”
Frame g_fps;
Time g_deltaTime;
DWORD g_preExec;

void InitTimer(Frame fps)
{
	SetFPS(fps);
	timeBeginPeriod(1);
	g_preExec = timeGetTime();
}
void UninitTimer()
{
	timeEndPeriod(1);
}
bool UpdateTimer()
{
	DWORD time = timeGetTime();
	DWORD diff = time - g_preExec;
	if (diff >= 1000 / 60)
	{
		g_deltaTime = diff / 1000.f;
		g_preExec = time;
		return true;
	}
	return false;
}

void SetFPS(Frame fps)
{
	g_fps = fps;
}
Frame GetFPS()
{
	return g_fps;
}


Time GetDeltaTime()
{
	return g_deltaTime;
}

Time ConvertFrameToTime(Frame frame)
{
	return static_cast<float>(frame) / g_fps;
}
Frame ConvertTimeToFrame(Time time)
{
	return static_cast<Frame>(time * g_fps);
}