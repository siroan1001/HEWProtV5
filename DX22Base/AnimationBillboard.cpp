#include "AnimationBillboard.h"
#include "SceneGame.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"


AnimationBillboard::AnimationBillboard()
	:m_uvPos{ 0.0f,0.0f }
	,m_uvScale{1.0f,1.0f}
{
	
}

AnimationBillboard::~AnimationBillboard()
{
	Sprite::SetUVPos({ 0.0f,0.0f });
	Sprite::SetUVScale({ 1.0f,1.0f });
}

void AnimationBillboard::Update()
{
}

int AnimationBillboard::GetMaxFlame()
{
	return m_div.U * m_div.V;
}

AnimationBillboard::Division AnimationBillboard::GetDivision()
{
	return m_div;
}


