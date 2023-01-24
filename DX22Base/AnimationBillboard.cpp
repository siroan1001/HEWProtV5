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


