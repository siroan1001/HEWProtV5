#pragma once
#ifndef __FADE_H__
#define __FADE_H__

#include "DirectX.h"
#include <DirectXMath.h>
#include "Shader.h"


class Fade
{
public:
	enum FADESTATE
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT,

		FADE_MAX
	};
public:
	Fade();
	~Fade();
	void Update();
	void Draw();
	void StartOut();

private:
	DirectX::XMFLOAT4 m_color;
	PixelShader* m_pFadePS;
	FADESTATE m_state;

};

#endif	// __FADE_H__