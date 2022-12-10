//#pragma once
#ifndef _____LIGHT_H____
#define _____LIGHT_H____

#include "Stage.h"

class Light
{
public:
	Light();
	~Light();
	void Update();
	void Draw();

	float GetRadius();
	Stage::Info GetInfo();
	float GetPower();

private:
	Stage::Info m_Info;
	float m_Power;

};

#endif // !_____LIGHT_H____
