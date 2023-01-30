#include "SceneResult.h"
#include "Input.h"

SceneResult::ResultStatus SceneResult::m_ResultStatus;


SceneResult::SceneResult()
	:m_flame(0)
{
	m_pResultBill = new ResultBillboard;
	m_pBG = new BG(BG::E_BG_KIND_FOREST);

	m_ResultStatus = E_RESULT_STATUS_START;
}

SceneResult::~SceneResult()
{
	delete m_pBG;
	delete m_pResultBill;
}

void SceneResult::Update()
{
	switch (m_ResultStatus)
	{
	case SceneResult::E_RESULT_STATUS_NOME:
		break;
	case SceneResult::E_RESULT_STATUS_START:
		m_pResultBill->Update(/*m_flame*/);
		m_flame++;
		if (m_flame == m_pResultBill->GetMaxFlame())
		{
			m_ResultStatus = E_RESULT_STATUS_NORMAL;
			m_flame = 0;
		}
		break;
	case SceneResult::E_RESULT_STATUS_NORMAL:
		if (IsKeyTrigger(VK_SPACE))
		{
			//�X�y�[�X�L�[���������烊�g���C
			Game3D::SetScene(Game3D::E_SCENE_KIND_GAME);
			m_ResultStatus = E_RESULT_STATUS_START;
		}
		if (IsKeyTrigger(VK_RETURN))
		{
			//�G���^�[����������^�C�g����(������X�e�[�W�Z���N�g��)
			Game3D::SetScene(Game3D::E_SCENE_KIND_TITLE);
			m_ResultStatus = E_RESULT_STATUS_START;
		}
		break;
	case SceneResult::E_RESULT_STATUS_MAX:
		break;
	default:
		break;
	}
	
	m_pBG->Update();
}

void SceneResult::Draw()
{
	m_pResultBill->Draw();
	m_pBG->Draw();
}

void SceneResult::ReStart()
{
}
