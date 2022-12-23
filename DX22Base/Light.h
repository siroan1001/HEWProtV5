//#pragma once
#ifndef _____LIGHT_H____
#define _____LIGHT_H____

#include "Stage.h"

#include "CameraBase.h"

class Light
{
public:
	Light();
	~Light();
	void Update();
	void Draw();

	float GetRadius();
	Object::Info GetInfo();
	float GetPower();


	void SetCamera(CameraBase* pCamera);
private:
	Object::Info m_Info;
	float m_Power;

	CameraBase* m_pCamera;
};

#endif // !_____LIGHT_H____
