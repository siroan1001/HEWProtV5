#include "SceneClear.h"
#include "Input.h"

SceneClear::ClearStatus SceneClear::m_ClearStatus;


SceneClear::SceneClear()
	:m_flame(0)
{
	m_pClearBill = new ClearBillboard;
	m_pBG = new BG(BG::E_BG_KIND_FOREST);

	m_ClearStatus = E_CLEAR_STATUS_START;
}

SceneClear::~SceneClear()
{
	delete m_pBG;
	delete m_pClearBill;
}

void SceneClear::Update()
{
	switch (m_ClearStatus)
	{
	case SceneClear::E_CLEAR_STATUS_NOME:
		break;
	case SceneClear::E_CLEAR_STATUS_START:
		m_pClearBill->Update(/*m_flame*/);
		m_flame++;
		if (m_flame == m_pClearBill->GetMaxFlame())
		{
			m_ClearStatus = E_CLEAR_STATUS_NORMAL;
			m_flame = 0;
		}
		break;
	case SceneClear::E_CLEAR_STATUS_NORMAL:
		if (IsKeyTrigger(VK_SPACE))
		{
			//スペースキーを押したらゲームへ(実装後次のステージへ)
			Game3D::SetScene(Game3D::E_SCENE_KIND_GAME);
			m_ClearStatus = E_CLEAR_STATUS_START;
		}
		if (IsKeyTrigger(VK_RETURN))
		{
			//エンターを押したらタイトルへ(実装後ステージセレクトへ)
			Game3D::SetScene(Game3D::E_SCENE_KIND_TITLE);
			m_ClearStatus = E_CLEAR_STATUS_START;
		}
		break;
	case SceneClear::E_CLEAR_STATUS_MAX:
		break;
	default:
		break;
	}

	m_pBG->Update();
}

void SceneClear::Draw()
{
	m_pClearBill->Draw();
	m_pBG->Draw();
}

void SceneClear::ReStart()
{
}
