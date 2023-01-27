#include "StageSelectCursor.h"
#include "controller.h"

StageSelectCursor::StageSelectCursor()
{
	LoadTextureFromFile("Assets/StageSelectCursor.png", &m_pTex);
	m_Info.Size = XMFLOAT2(1.778f, 1.0f);
	m_Info.Pos = XMFLOAT3(-4.20f, 3.55f, 0.0f);

	m_TargetPos[SceneGame::E_STAGE_NUMBER_STAGE_1] = XMFLOAT3(-4.15f, 3.55f, 0.0f);
	m_TargetPos[SceneGame::E_STAGE_NUMBER_STAGE_2] = XMFLOAT3(-5.48f, 4.10f, 0.0f);
	m_TargetPos[SceneGame::E_STAGE_NUMBER_STAGE_3] = XMFLOAT3(-6.74f, 3.57f, 0.0f);

	m_StageNum = SceneGame::E_STAGE_NUMBER_STAGE_1;

	m_MoveFlag = false;
}

void StageSelectCursor::Update()
{
	if (GetLStick().x >= 0.8f)
	{
		if (!m_MoveFlag)
		{
			switch (m_StageNum)
			{
			case SceneGame::E_STAGE_NUMBER_STAGE_1:
				m_StageNum = SceneGame::E_STAGE_NUMBER_STAGE_2;
				m_Info.Pos = m_TargetPos[m_StageNum];
				break;
			case SceneGame::E_STAGE_NUMBER_STAGE_2:
				m_StageNum = SceneGame::E_STAGE_NUMBER_STAGE_3;
				m_Info.Pos = m_TargetPos[m_StageNum];
				break;
			default:
				break;
			}
			m_MoveFlag = true;
		}
	}
	else if (GetLStick().x <= -0.8f)
	{
		if (!m_MoveFlag)
		{
			switch (m_StageNum)
			{
			case SceneGame::E_STAGE_NUMBER_STAGE_2:
				m_StageNum = SceneGame::E_STAGE_NUMBER_STAGE_1;
				m_Info.Pos = m_TargetPos[m_StageNum];
				break;
			case SceneGame::E_STAGE_NUMBER_STAGE_3:
				m_StageNum = SceneGame::E_STAGE_NUMBER_STAGE_2;
				m_Info.Pos = m_TargetPos[m_StageNum];
				break;
			default:
				break;
			}
			m_MoveFlag = true;
		}
	}
	else
	{
		m_MoveFlag = false;
	}
}

SceneGame::StageNumber StageSelectCursor::GetStageNum()
{
	return m_StageNum;
}
