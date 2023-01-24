#include "ClearBillboard.h"
#include "DirectXTex/Texture.h"
#include "Sprite.h"
#include "SceneGame.h"


ClearBillboard::ClearBillboard()
{
	LoadTextureFromFile("Assets/ClearSprite.png", &m_pTex);
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, 1.0f);
	m_Info.Size = XMFLOAT2(2.0f, 2.0f);
	m_uvScale = { 1.0f / m_uv.U, 1.0f / m_uv.V };
	AnimFlame = 0;
}

void ClearBillboard::Update(int flame)
{
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, -1.0f);
	AnimFlame = flame;
}

void ClearBillboard::Draw()
{
	Sprite::SetUVPos({ 1.0f / m_uv.U * (AnimFlame % m_uv.U), 1.0f / m_uv.V * (AnimFlame / m_uv.U) });
	Sprite::SetUVScale(m_uvScale);
	AnimationBillboard::Draw();
}

int ClearBillboard::GetMaxFlame()
{
	return m_uv.U * m_uv.V;
}
