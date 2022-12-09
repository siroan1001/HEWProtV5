#ifndef __TIMER_H__
#define __TIMER_H__

//--- 型宣言
using Frame = unsigned short;
using Time = float;

//--- プロトタイプ宣言
void InitTimer(Frame fps);
void UninitTimer();
bool UpdateTimer();

void SetFPS(Frame fps);
Frame GetFPS();

Time GetDeltaTime();

Time ConvertFrameToTime(Frame frame);
Frame ConvertTimeToFrame(Time time);

#endif // __TIMER_H__