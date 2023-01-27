#include "ResultBillboard.h"
#include "DirectXTex/Texture.h"
#include "Sprite.h"
#include "SceneGame.h"


ResultBillboard::ResultBillboard()
{
	m_div = { 4,4 };
	LoadTextureFromFile("Assets/FailedSprite.png", &m_pTex);
	/*LoadTextureFromFile("Assets/1SecondFailedSprite.png", &m_pTex);*/

	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, 1.0f);
	m_Info.Size = XMFLOAT2(0.7f, 0.7f);
	m_uvScale = { 1.0f / m_div.U, 1.0f / m_div.V };
	m_AnimFlame = 0;
	m_IsAnimFin = false;
}

void ResultBillboard::Update()
{
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, 1.0f);
	if (!m_IsAnimFin)m_AnimFlame++;
	if(m_AnimFlame >= m_div.U * m_div.V - 1)m_IsAnimFin = true;
}

void ResultBillboard::Draw()
{
	Sprite::SetUVPos({ 1.0f / m_div.U * (m_AnimFlame % m_div.U), 1.0f / m_div.V * (m_AnimFlame / m_div.U) });
	Sprite::SetUVScale(m_uvScale);
	AnimationBillboard::Draw();
}

bool ResultBillboard::GetFlag()
{
	return m_IsAnimFin;
}

void ResultBillboard::ResetAnim()
{
	m_AnimFlame = 0;
	m_IsAnimFin = false;
}

