#include "BG.h"
#include "DirectXTex/Texture.h"
#include "Sprite.h"
#include "SceneGame.h"

using namespace DirectX;

BG::BG(BG::BGKind bg)
{
	switch (bg)
	{
	case E_BG_KIND_TITLE:
		LoadTextureFromFile("Assets/TitleBG.jpg", &m_pTex);
		break;
	case E_BG_KIND_FOREST:
		LoadTextureFromFile("Assets/ForestBG.jpg", &m_pTex);
		break;
	default:
		break;
	}
	
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, -2.7f);
	m_Info.Size = XMFLOAT2(10.0f, 5.625f);
}

void BG::Update()
{
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, -1.0f);
}

void BG::Draw()
{
	Sprite::SetUVPos({ 0.0f,0.0f });
	Sprite::SetUVScale({ 1.0f,1.0f });
	Billboard::Draw();
}
