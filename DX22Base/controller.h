#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <Windows.h>
#include <Xinput.h>
#include <cmath>
#include <DirectXMath.h>
#pragma comment (lib, "xinput.lib")

//�{�^���}�X�N
#define BUTTON_UP      0x0001	//�\���L�[��
#define BUTTON_DOWN    0x0002	//�\���L�[��
#define BUTTON_LEFT    0x0004	//�\���L�[��
#define BUTTON_RIGHT   0x0008	//�\���L�[�E
#define BUTTON_START   0x0010	//START�{�^��
#define BUTTON_BACK    0x0020	//BACK�{�^��
#define LSTICK_THUMB   0x0040	//���X�e�B�b�N��������
#define RSTICK_THUMB   0x0080	//�E�X�e�B�b�N��������
#define BUTTON_L       0x0100	//L�{�^��
#define BUTTON_R       0x0200	//R�{�^��
#define BUTTON_A       0x1000	//A�{�^��
#define BUTTON_B       0x2000	//B�{�^��
#define BUTTON_X       0x4000	//X�{�^��
#define BUTTON_Y       0x8000	//Y�{�^��

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