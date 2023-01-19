#include "BG.h"
#include "DirectXTex/Texture.h"
#include "Sprite.h"
#include "SceneGame.h"

using namespace DirectX;

BG::BG()
{
	LoadTextureFromFile("Assets/ForestBG.jpg", &m_pTex);
	CameraBase* cam = SceneGame::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, 1.0f);
	m_Info.Size = XMFLOAT2(10.0f, 5.625f);
}

void BG::Update()
{
	CameraBase* cam = SceneGame::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, -1.0f);
}