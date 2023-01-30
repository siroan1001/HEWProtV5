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
	bool m_Use;				//Žg‚Á‚Ä‚¢‚é‚©‚Ìƒtƒ‰ƒO
	float m_Life;
};
