#include "BG.h"
#include "DirectXTex/Texture.h"
#include "Sprite.h"
#include "SceneGame.h"
#include "Game3D.h"

using namespace DirectX;

BG::BG(BG::BGKind bg)
	: m_bgKind(bg)
{
	switch (m_bgKind)
	{
	case E_BG_KIND_TITLE:
		LoadTextureFromFile("Assets/TitleBG.jpg", &m_pTex);
		m_Info.Size = XMFLOAT2(7.0f, 3.938f);
		break;
	case E_BG_KIND_STAGESELECT:
		LoadTextureFromFile("Assets/StageSelect.png", &m_pTex);
		m_Info.Size = XMFLOAT2(5.1f, 2.618f);
		break;
	case E_BG_KIND_FOREST:
		LoadTextureFromFile("Assets/ForestBG.jpg", &m_pTex);
		m_Info.Size = XMFLOAT2(7.0f, 3.938f);
		break;
	default:
		break;
	}
	
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, -0.25f);
	
}

void BG::Update()
{
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, -1.0f);
}

void BG::Draw()
{
	Sprite::SetUVPos({ 0.0f,0.0f });
	switch (m_bgKind)
	{
	case BG::E_BG_KIND_TITLE:
		Sprite::SetUVScale({ 1.0f,1.0f });
		break;
	case BG::E_BG_KIND_STAGESELECT:
		Sprite::SetUVScale({ 1.0f,1.0f });
		break;
	case BG::E_BG_KIND_FOREST:
		Sprite::SetUVScale({ 1.0f,1.0f });
		break;	
	}

	Billboard::Draw();
}

void BG::SetInfo(XMFLOAT3 pos)
{
	m_Info.Pos = pos;
}
