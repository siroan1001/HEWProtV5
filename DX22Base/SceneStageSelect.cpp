#include "SceneStageSelect.h"
#include "Input.h"
#include "controller.h"

SceneGame::StageNumber SceneStageSelect::m_StageNumber;

SceneStageSelect::SceneStageSelect(CameraBase * camera, SceneGame::StageNumber stagenumber)
{
	m_pCamera = camera;
	m_StageNumber = stagenumber;
	m_pBG = new BG(BG::E_BG_KIND_STAGESELECT);
	m_pCursor = new StageSelectCursor;
}


SceneStageSelect::~SceneStageSelect()
{
	delete m_pCursor;
	delete m_pBG;
}

void SceneStageSelect::Update()
{
	if (IsKeyTrigger(VK_SPACE))
	{
		Game3D::SetScene(Game3D::E_SCENE_KIND_GAME);
		m_StageNumber = SceneGame::E_STAGE_NUMBER_STAGE_1;
	}
	if (IsButtonTrigger(BUTTON_A))
	{
		Game3D::SetScene(Game3D::E_SCENE_KIND_GAME);
		m_StageNumber = SceneGame::E_STAGE_NUMBER_STAGE_1;
	}
	if (IsButtonTrigger(BUTTON_X))
	{
		Game3D::SetScene(Game3D::E_SCENE_KIND_GAME);
		m_StageNumber = SceneGame::E_STAGE_NUMBER_STAGE_2;
	}
	if (IsButtonTrigger(BUTTON_Y))
	{
		Game3D::SetScene(Game3D::E_SCENE_KIND_GAME);
		m_StageNumber = SceneGame::E_STAGE_NUMBER_STAGE_3;
	}

	m_pCursor->Update();

	if (IsButtonTrigger(BUTTON_B))
	{
		m_StageNumber = m_pCursor->GetStageNum();
		Game3D::SetScene(Game3D::E_SCENE_KIND_GAME);
	}
}

void SceneStageSelect::Draw()
{
	m_pBG->Draw();
	m_pCursor->Draw();
}

void SceneStageSelect::ReStart()
{
}

void SceneStageSelect::SetCamera(CameraBase * camera)
{
	m_pCamera = camera;
}

SceneGame::StageNumber* SceneStageSelect::GetStageNumber()
{
	return &m_StageNumber;
}


