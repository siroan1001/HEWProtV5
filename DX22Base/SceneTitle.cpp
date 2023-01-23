#include "SceneTitle.h"
#include "Input.h"
#include "DirectXTex/Texture.h"

SceneTitle::SceneTitle()
{
	//m_TitleUI = new TitleUI;
	m_pBG = new BG;
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

	if (IsKeyPress(VK_RETURN))
	{
		//ƒGƒ“ƒ^[‚ð‰Ÿ‚µ‚½‚çØ‚è‘Ö‚¦
		Game3D::SetScene(Game3D::E_SCENE_KIND_GAME);
	}
}

void SceneTitle::Draw()
{
	//EnableDepth(false);
	//m_TitleUI->Draw();
	//EnableDepth(true);

	m_pBG->Draw();
}
