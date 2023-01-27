#include "LayerResult.h"
#include "SceneGame.h"
#include "Game3D.h"
#include "Input.h"

LayerResult::LayerResult()
{
	m_pResultBill = new ResultBillboard;
	m_pClearBill = new ClearBillboard;
}

LayerResult::~LayerResult()
{
	delete m_pClearBill;
	delete m_pResultBill;
}

void LayerResult::Update()
{
	switch (SceneGame::GetGameStatus())
	{
	case SceneGame::E_GAME_STATUS_GAMEOVER:
		m_pResultBill->Update();
		if (m_pResultBill->GetFlag())
		{
			//スペースキーが押された時リトライ(未実装)
			if (IsKeyTrigger(VK_SPACE))
			{
				SceneGame::SetGameStatus(SceneGame::E_GAME_STATUS_START);
				m_pResultBill->ResetAnim();
			}
			//エンターキーが押された時タイトルへ(ステージセレクト実装後差し替え)
			if (IsKeyTrigger(VK_RETURN))
			{
				Game3D::SetScene(Game3D::E_SCENE_KIND_TITLE);
				m_pResultBill->ResetAnim();
			}
		}
		break;
	case SceneGame::E_GAME_STATUS_GOAL:
		m_pClearBill->Update();
		if (m_pClearBill->GetFlag())
		{
			//スペースキーが押された時次のステージへ(未実装)
			if (IsKeyTrigger(VK_SPACE))
			{
				SceneGame::SetGameStatus(SceneGame::E_GAME_STATUS_START);
				m_pClearBill->ResetAnim();
			}
			//エンターキーが押された時タイトルへ(ステージセレクト実装後差し替え)
			if (IsKeyTrigger(VK_RETURN))
			{
				Game3D::SetScene(Game3D::E_SCENE_KIND_TITLE);
				m_pClearBill->ResetAnim();
			}
		}
		break;
	default:
		break;
	}
}

void LayerResult::Draw()
{
	switch (SceneGame::GetGameStatus())
	{
	case SceneGame::E_GAME_STATUS_GAMEOVER:
		m_pResultBill->Draw();
		break;
	case SceneGame::E_GAME_STATUS_GOAL:
		m_pClearBill->Draw();
		break;
	default:
		break;
	}
}

void LayerResult::Reset()
{
}
