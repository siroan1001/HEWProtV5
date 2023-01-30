#pragma once


#include "Def.h"
#include "Object.h"

class SmallShadowBlock : public Object
{
public:
	SmallShadowBlock(Def::Info);
	void Update();
	void Reset();
	bool GetUse();
	float GetLife();
	void SetUse(bool);
	void SetLife(float);
private:
	bool m_Use;				//�g���Ă��邩�̃t���O
	float m_Life;
};
