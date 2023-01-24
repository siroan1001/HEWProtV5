#include "ResultBillboard.h"
#include "DirectXTex/Texture.h"
#include "Sprite.h"
#include "SceneGame.h"


ResultBillboard::ResultBillboard()
{
	LoadTextureFromFile("Assets/FailedSprite.png", &m_pTex);
	/*LoadTextureFromFile("Assets/1SecondFailedSprite.png", &m_pTex);*/

	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, 1.0f);
	m_Info.Size = XMFLOAT2(5.2f, 3.9f);
	m_uvScale = { 1.0f / m_uv.U, 1.0f / m_uv.V };
	AnimFlame = 0;
}

void ResultBillboard::Update(int flame)
{
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, -1.0f);
	AnimFlame = flame;
}

void ResultBillboard::Draw()
{
	Sprite::SetUVPos({ 1.0f / m_uv.U * (AnimFlame % m_uv.U), 1.0f / m_uv.V * (AnimFlame / m_uv.U) });
	Sprite::SetUVScale(m_uvScale);
	AnimationBillboard::Draw();
}

int ResultBillboard::GetMaxFlame()
{
	return m_uv.U * m_uv.V;
}
