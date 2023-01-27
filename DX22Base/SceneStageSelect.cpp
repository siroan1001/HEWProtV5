#include "SceneStageSelect.h"
#include "Input.h"
#include "controller.h"

SceneGame::StageNumber SceneStageSelect::m_StageNumber;

SceneStageSelect::SceneStageSelect(CameraBase * camera, SceneGame::StageNumber stagenumber)
{
	m_pCamera = camera;
	m_StageNumber = stagenumber;
	m_pBG = new BG(BG::E_BG_KIND_STAGESELECT);
}


SceneStageSelect::~SceneStageSelect()
{
	delete m_pBG;
}

void SceneStageSelect::Update()
{
	if (IsKeyTrigger(VK_SPACE))
	{
		Game3D::SetScene(Game3D::E_SCENE_KIND_GAME);
		m_StageNumber = SceneGame::E_STAGE_NUMBER_STAGE_1;
	}
	if (IsButtonTrigger(BUTTON_B))
	{
		Game3D::SetScene(Game3D::E_SCENE_KIND_GAME);
		m_StageNumber = SceneGame::E_STAGE_NUMBER_STAGE_1;
	}
}

void SceneStageSelect::Draw()
{
	m_pBG->Draw();
}

void SceneStageSelect::ReStart()
{
}

void SceneStageSelect::SetCamera(CameraBase * camera)
{
	m_pCamera = camera;
}

SceneGame::StageNumber SceneStageSelect::GetStageNumber()
{
	return m_StageNumber;
}


