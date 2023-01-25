#include "ClearBillboard.h"
#include "DirectXTex/Texture.h"
#include "Sprite.h"
#include "SceneGame.h"


ClearBillboard::ClearBillboard()
{
	m_div = { 4,4 };
	LoadTextureFromFile("Assets/ClearSprite.png", &m_pTex);
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, 1.0f);
	m_Info.Size = XMFLOAT2(1.2f, 1.2f);
	m_uvScale = { 1.0f / m_div.U, 1.0f / m_div.V };
	m_AnimFlame = 0;
	m_IsAnimFin = false;
}

void ClearBillboard::Update()
{
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, 1.0f);
	if (!m_IsAnimFin)m_AnimFlame++;
	if (m_AnimFlame >= m_div.U * m_div.V - 1)m_IsAnimFin = true;
}

void ClearBillboard::Draw()
{
	Sprite::SetUVPos({ 1.0f / m_div.U * (m_AnimFlame % m_div.U), 1.0f / m_div.V * (m_AnimFlame / m_div.U) });
	Sprite::SetUVScale(m_uvScale);
	AnimationBillboard::Draw();
}

bool ClearBillboard::GetFlag()
{
	return m_IsAnimFin;
}

void ClearBillboard::ResetAnim()
{
	m_AnimFlame = 0;
	m_IsAnimFin = false;
}
