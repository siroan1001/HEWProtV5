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
		FADE_SKIP,

		FADE_MAX
	};
public:
	Fade();
	~Fade();
	void Update();
	void Draw();
	void StartOut();
	void SetFrame(float frame);
	void Skip();

private:
	DirectX::XMFLOAT4 m_color;
	PixelShader* m_pFadePS;
	FADESTATE m_state;
	float m_frame;
	bool m_skipflag;

};

#endif	// __FADE_H__