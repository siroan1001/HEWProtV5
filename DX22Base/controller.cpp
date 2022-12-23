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
	//�R���g���[���[�̏�Ԃ��擾
	//result��ERROR_SUCCESS�Ȃ�ڑ�����
	result = XInputGetState(
		0,       //DWORD  dwUserIndex  �R���g���[���[�̔ԍ�:0�`3
		&state); //XINPUT_STATE* pState �R���g���[���[�̏�Ԃ��i�[����XINPUT_STATE�\���̂̃|�C���^��n��
}

//�R���g���[���[���ڑ�����Ă��邩�̊m�F
//�������Ă����true��Ԃ�
bool CheckCtrl()
{
	if (result == ERROR_SUCCESS)return true;
	return false;
}

//�{�^����������Ă����true��Ԃ�
//�����ɂ̓{�^���}�X�N������
bool IsButtonPress(int button)
{
	if (state.Gamepad.wButtons & button)
	{
		return true;
	}
	return false;
}

//�{�^���������ꂽ��true��Ԃ�
//�����ɂ̓{�^���}�X�N������
bool IsButtonTrigger(int button)
{
	if ((oldstate.Gamepad.wButtons ^ state.Gamepad.wButtons) & (state.Gamepad.wButtons & button))
	{
		return true;
	}
	return false;
}

//LT�̐��l��Ԃ�(0.0�`1.0)
float GetLT()
{
	float LT;
	LT = round(((float)state.Gamepad.bLeftTrigger / 255) * 100) / 100;
	return LT;
}

//RT�̐��l��Ԃ�(0.0�`1.0)
float GetRT()
{
	float RT;
	RT = round(((float)state.Gamepad.bRightTrigger / 255) * 100) / 100;
	return RT;
}

//LT��������Ă����true��Ԃ�
bool IsLTPress()
{
	if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return true;
	}
	return false;
}

//RT��������Ă����true��Ԃ�
bool IsRTPress()
{
	if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return true;
	}
	return false;
}

//LT�������ꂽ��true��Ԃ�
bool IsLTTrigger()
{
	if ((oldstate.Gamepad.bLeftTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD) && (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD))
	{
		return true;
	}
	return false;
}

//RT�������ꂽ��true��Ԃ�
bool IsRTTrigger()
{
	if ((oldstate.Gamepad.bRightTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD) && (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD))
	{
		return true;
	}
	return false;
}


//���W���C�X�e�B�b�N�̏�Ԃ�Ԃ�(-1.0�`1.0)
DirectX::XMFLOAT2 GetLStick()
{
	DirectX::XMFLOAT2 stick;
	stick.x = round((float)state.Gamepad.sThumbLX / 32768 * 100)/100;
	stick.y = round((float)state.Gamepad.sThumbLY / 32768 * 100)/100;
	return stick;
}

//�E�W���C�X�e�B�b�N�̏�Ԃ�Ԃ�(-1.0�`1.0)
DirectX::XMFLOAT2 GetRStick()
{
	DirectX::XMFLOAT2 stick;
	stick.x = round((float)state.Gamepad.sThumbRX / 32768 * 100)/100;
	stick.y = round((float)state.Gamepad.sThumbRY / 32768 * 100)/100;
	return stick;
}

//�����[�^�[��U��
//������(0.0�`1.0)
void SetLVibration(float MotorSP)
{
	if (MotorSP > 1.0f)MotorSP = 1.0f;
	if (MotorSP < 0.0f)MotorSP = 0.0f;
	vibration.wLeftMotorSpeed = int(MotorSP * 65535);
	XInputSetState(0, &vibration);
}

//�E���[�^�[��U��
//������(0.0�`1.0)
void SetRVibration(float MotorSP)
{
	if (MotorSP > 1.0f)MotorSP = 1.0f;
	if (MotorSP < 0.0f)MotorSP = 0.0f;
	vibration.wRightMotorSpeed = (int)(MotorSP * 65535);
	XInputSetState(0, &vibration);
}

