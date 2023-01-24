//#pragma once
#ifndef _____ANIMATION_BILLBOARD_H____
#define _____ANIMATION_BILLBOARD_H____

#include "DirectXTex/Texture.h"
#include "Billboard.h"

class AnimationBillboard : public Billboard
{
public:
	AnimationBillboard();
	~AnimationBillboard();
	void Update();

protected:
	DirectX::XMFLOAT2 m_uvPos;
	DirectX::XMFLOAT2 m_uvScale;

};

#endif // !_____BILLBOARD_H____
