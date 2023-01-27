#include "SceneTitle.h"
#include "Input.h"
#include "DirectXTex/Texture.h"
#include "controller.h"

SceneTitle::SceneTitle()
{
	//m_TitleUI = new TitleUI;
	m_pBG = new BG(BG::E_BG_KIND_TITLE);
}

SceneTitle::~SceneTitle()
{
	//delete m_TitleUI;
	//m_TitleUI = nullptr;

	delete m_pBG;
}

void SceneTitle::Update()
{
	m_pBG;

	if (IsKeyPress(VK_SPACE) || IsButtonTrigger(BUTTON_B))
	{
		//エンターを押したら切り替え
		Game3D::SetScene(Game3D::E_SCENE_KIND_STAGESELECT);
	}
}

void SceneTitle::Draw()
{
	//EnableDepth(false);
	//m_TitleUI->Draw();
	//EnableDepth(true);

	m_pBG->Draw();
}

void SceneTitle::ReStart()
{
	Game3D::GetCamera()->SetLook(XMFLOAT3(-5.48f, 4.05f, 0.0f));
}
