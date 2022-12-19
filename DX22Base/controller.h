#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <Windows.h>
#include <Xinput.h>
#include <cmath>
#include <DirectXMath.h>
#pragma comment (lib, "xinput.lib")

//ボタンマスク
#define BUTTON_UP      0x0001	//十字キー上
#define BUTTON_DOWN    0x0002	//十字キー下
#define BUTTON_LEFT    0x0004	//十字キー左
#define BUTTON_RIGHT   0x0008	//十字キー右
#define BUTTON_START   0x0010	//STARTボタン
#define BUTTON_BACK    0x0020	//BACKボタン
#define LSTICK_THUMB   0x0040	//左スティック押し込み
#define RSTICK_THUMB   0x0080	//右スティック押し込み
#define BUTTON_L       0x0100	//Lボタン
#define BUTTON_R       0x0200	//Rボタン
#define BUTTON_A       0x1000	//Aボタン
#define BUTTON_B       0x2000	//Bボタン
#define BUTTON_X       0x4000	//Xボタン
#define BUTTON_Y       0x8000	//Yボタン

void InitCtrl();
void UninitCtrl();
void UpdateCtrl();

bool CheckCtrl();

bool IsButtonPress(int button);
bool IsButtonTrigger(int button);

float GetLT();
float GetRT();

bool IsLTPress();
bool IsRTPress();

bool IsLTTrigger();
bool IsRTTrigger();

DirectX::XMFLOAT2 GetLStick();
DirectX::XMFLOAT2 GetRStick();

void SetLVibration(float MotorSP);
void SetRVibration(float MotorSP);

#endif // __CONTROLLER_H__