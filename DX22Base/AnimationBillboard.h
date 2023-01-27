//#pragma once
#ifndef _____ANIMATION_BILLBOARD_H____
#define _____ANIMATION_BILLBOARD_H____

#include "DirectXTex/Texture.h"
#include "Billboard.h"

class AnimationBillboard : public Billboard
{
public:
	struct Division
	{
		int U;
		int V;
	};
	AnimationBillboard();
	~AnimationBillboard();
	void Update();
	int GetMaxFlame();
	Division GetDivision();

protected:
	DirectX::XMFLOAT2 m_uvPos;
	DirectX::XMFLOAT2 m_uvScale;
	Division m_div;
};

#endif // !_____BILLBOARD_H____
