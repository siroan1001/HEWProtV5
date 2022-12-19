#include "controller.h"

XINPUT_STATE state;
XINPUT_STATE oldstate;
XINPUT_VIBRATION vibration;
DWORD result;

void InitCtrl()
{
}

void UninitCtrl()
{
}

void UpdateCtrl()
{
	oldstate = state;
	//コントローラーの状態を取得
	//resultがERROR_SUCCESSなら接続成功
	result = XInputGetState(
		0,       //DWORD  dwUserIndex  コントローラーの番号:0～3
		&state); //XINPUT_STATE* pState コントローラーの状態を格納するXINPUT_STATE構造体のポインタを渡す
}

//コントローラーが接続されているかの確認
//成功していればtrueを返す
bool CheckCtrl()
{
	if (result == ERROR_SUCCESS)return true;
	return false;
}

//ボタンが押されている間trueを返す
//引数にはボタンマスクを入れる
bool IsButtonPress(int button)
{
	if (state.Gamepad.wButtons & button)
	{
		return true;
	}
	return false;
}

//ボタンが押された時trueを返す
//引数にはボタンマスクを入れる
bool IsButtonTrigger(int button)
{
	if ((oldstate.Gamepad.wButtons ^ state.Gamepad.wButtons) & (state.Gamepad.wButtons & button))
	{
		return true;
	}
	return false;
}

//LTの数値を返す(0.0～1.0)
float GetLT()
{
	float LT;
	LT = round(((float)state.Gamepad.bLeftTrigger / 255) * 100) / 100;
	return LT;
}

//RTの数値を返す(0.0～1.0)
float GetRT()
{
	float RT;
	RT = round(((float)state.Gamepad.bRightTrigger / 255) * 100) / 100;
	return RT;
}

//LTが押されている間trueを返す
bool IsLTPress()
{
	if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return true;
	}
	return false;
}

//RTが押されている間trueを返す
bool IsRTPress()
{
	if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return true;
	}
	return false;
}

//LTが押された時trueを返す
bool IsLTTrigger()
{
	if ((oldstate.Gamepad.bLeftTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD) && (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD))
	{
		return true;
	}
	return false;
}

//RTが押された時trueを返す
bool IsRTTrigger()
{
	if ((oldstate.Gamepad.bRightTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD) && (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD))
	{
		return true;
	}
	return false;
}


//左ジョイスティックの状態を返す(-1.0～1.0)
DirectX::XMFLOAT2 GetLStick()
{
	DirectX::XMFLOAT2 stick;
	stick.x = round((float)state.Gamepad.sThumbLX / 32768 * 100)/100;
	stick.y = round((float)state.Gamepad.sThumbLY / 32768 * 100)/100;
	return stick;
}

//右ジョイスティックの状態を返す(-1.0～1.0)
DirectX::XMFLOAT2 GetRStick()
{
	DirectX::XMFLOAT2 stick;
	stick.x = round((float)state.Gamepad.sThumbRX / 32768 * 100)/100;
	stick.y = round((float)state.Gamepad.sThumbRY / 32768 * 100)/100;
	return stick;
}

//左モーターを振動
//引数は(0.0～1.0)
void SetLVibration(float MotorSP)
{
	if (MotorSP > 1.0f)MotorSP = 1.0f;
	if (MotorSP < 0.0f)MotorSP = 0.0f;
	vibration.wLeftMotorSpeed = int(MotorSP * 65535);
	XInputSetState(0, &vibration);
}

//右モーターを振動
//引数は(0.0～1.0)
void SetRVibration(float MotorSP)
{
	if (MotorSP > 1.0f)MotorSP = 1.0f;
	if (MotorSP < 0.0f)MotorSP = 0.0f;
	vibration.wRightMotorSpeed = (int)(MotorSP * 65535);
	XInputSetState(0, &vibration);
}

