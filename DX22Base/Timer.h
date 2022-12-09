#ifndef __TIMER_H__
#define __TIMER_H__

//--- �^�錾
using Frame = unsigned short;
using Time = float;

//--- �v���g�^�C�v�錾
void InitTimer(Frame fps);
void UninitTimer();
bool UpdateTimer();

void SetFPS(Frame fps);
Frame GetFPS();

Time GetDeltaTime();

Time ConvertFrameToTime(Frame frame);
Frame ConvertTimeToFrame(Time time);

#endif // __TIMER_H__