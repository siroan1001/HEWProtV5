#include "SceneGame.h"
#include "Geometory.h"
#include "Input.h"
#include "CameraBase.h"
#include "CameraDebug.h"
#include "CameraMain.h"
#include "CameraEvent.h"
#include "CameraDelay.h"
#include "Stage.h"
#include "ShadowBlock.h"
#include "Light.h"
#include "Collision.h"
#include "Layer.h"
#include "LayerGame.h"
#include "LayerBG.h"
#include "controller.h"
#include "LayerResult.h"
#include "Effect.h"
#include "SceneStageSelect.h"

SceneGame::GameStatus SceneGame::m_GameStatus;
SceneGame::StageNumber SceneGame::m_StageNuber;
Layer* SceneGame::m_pLayer[E_LAYER_MAX];

SceneGame::SceneGame(StageNumber stagenum)
{
	m_StageNuber = stagenum;

	//画像合成方法の設定
	m_pBlend = new BlendState;
	D3D11_RENDER_TARGET_BLEND_DESC blend = {};
	blend.BlendEnable = TRUE;
	blend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blend.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blend.SrcBlendAlpha = D3D11_BLEND_ONE;
	blend.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend.DestBlendAlpha = D3D11_BLEND_ONE;
	blend.BlendOp = D3D11_BLEND_OP_ADD;
	blend.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	m_pBlend->Create(blend);
	m_pBlend->Bind();



	switch (stagenum)
	{
	case E_STAGE_NUMBER_STAGE_1:
		Stage1();
		break;
	default:
		break;
	}


	m_GameStatus = E_GAME_STATUS_START;
}

SceneGame::~SceneGame()
{
	//レイヤーの終了
	for (int i = 0; i < E_LAYER_MAX; i++)
	{
		if (!m_pLayer[i])	continue;
		delete m_pLayer[i];
	}


}

void SceneGame::Update()
{


	//switch (m_GameStatus)
	//{
	//case SceneGame::E_GAME_STATUS_GAMEOVER:
	//	if (!m_pLayer[E_LAYER_RESULT]) break;
	//	m_pLayer[E_LAYER_RESULT]->Update();
	//	break;
	//case SceneGame::E_GAME_STATUS_GOAL:
	//	if (!m_pLayer[E_LAYER_RESULT]) break;
	//	m_pLayer[E_LAYER_RESULT]->Update();
	//	break;
	//default:
	//	for (int i = 0; i < E_LAYER_MAX; i++)
	//	{
	//		if (!m_pLayer[i])	continue;
	//		m_pLayer[i]->Update();
	//	}
	//	break;
	//}
	
	for (int i = 0; i < E_LAYER_MAX; i++)
	{
		if (!m_pLayer[i])	continue;
		m_pLayer[i]->Update();
	}

	if (m_GameStatus == E_GAME_STATUS_GAMEOVER || m_GameStatus == E_GAME_STATUS_GOAL)
	{
		m_pLayer[E_LAYER_RESULT]->Update();
	}

	if (m_GameStatus == E_GAME_STATUS_GAMEOVER)
	{
		//Game3D::SetScene(Game3D::E_SCENE_KIND_RESULT);
		if (IsButtonTrigger(BUTTON_A) || IsKeyTrigger(VK_SPACE))
		{
			Game3D::SetScene(Game3D::E_SCENE_KIND_STAGESELECT);
		}
		if (IsButtonTrigger(BUTTON_B) || IsKeyTrigger(VK_SHIFT))
		{
			ReStart();
		}
	}
	if (m_GameStatus == E_GAME_STATUS_GOAL)
	{
		if (IsButtonTrigger(BUTTON_A) || IsKeyTrigger(VK_SPACE))
		{
			Game3D::SetScene(Game3D::E_SCENE_KIND_STAGESELECT);
		}
		if (IsButtonTrigger(BUTTON_B) || IsKeyTrigger(VK_SHIFT))
		{
			SceneStageSelect::SetNextStage();
			ReStart();
		}
	}
	
}

void SceneGame::Draw()
{
	CameraBase* cam = Game3D::GetCamera();

	//ジオメトリーのビュー行列とプロジェクション行列を設定する
	SetGeometoryVPMatrix(cam->GetViewMatrix(), cam->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV), cam->GetPos());
	for (int i = 0; i < E_LAYER_MAX; i++)
	{
		if (!m_pLayer[i])	continue;
		m_pLayer[i]->Draw();
	}

}

void SceneGame::ReStart()
{
	Game3D::GetCamera()->SetLook(XMFLOAT3(-5.48f, 4.05f, 0.0f));

	m_GameStatus = E_GAME_STATUS_START;

	m_pLayer[E_LAYER_BG]->Reset();
	m_pLayer[E_LAYER_GAME]->Reset();
}



SceneGame::GameStatus SceneGame::GetGameStatus()
{
	return m_GameStatus;
}

void SceneGame::SetGameStatus(GameStatus status)
{
	m_GameStatus = status;
}
SceneGame::StageNumber* SceneGame::GetStageNum()
{
	return &m_StageNuber;
}

Layer * SceneGame::GetLayer(LayerKind kind)
{
	return m_pLayer[kind];
}

void SceneGame::StageTutoRial()
{
}

void SceneGame::Stage1()
{
	//CameraMain* pMain = new CameraMain;
	//pMain->SetLook(XMFLOAT3(-5.0f, 4.05f, 0.0f));
	//m_pCamera[E_CAM_MAIN] = pMain;
	//CameraEvent* pEvent = new CameraEvent();
	//pEvent->SetEvent(XMFLOAT3(-3.0f, 4.25f, 3.0f), XMFLOAT3(-3.0f, 4.25f, 3.0f), 3.0f);
	//m_pCamera[E_CAM_EVENT] = pEvent;
	//CameraDelay* pDelay = new CameraDelay;
	//pDelay->SetCamera(XMFLOAT3(-4.3f, 4.25f, 0.0f), 3.0f, 1.0f);
	//m_pCamera[E_CAM_DELAY] = pDelay;
	//m_pCamera[E_CAM_DEBUG] = new CameraDebug;

	m_pLayer[E_LAYER_BG] = new LayerBG;		//これ
	m_pLayer[E_LAYER_BUCK_OBJECT] = NULL;
	m_pLayer[E_LAYER_GAME] = new LayerGame(Game3D::GetCamera(), &m_GameStatus, E_STAGE_NUMBER_STAGE_1);		//これ
	m_pLayer[E_LAYER_UI] = NULL;
	m_pLayer[E_LAYER_RESULT] = new LayerResult;

	EffectManager::SetCamera(Game3D::GetCamera());

	LayerGame* layer = reinterpret_cast<LayerGame*>(m_pLayer[E_LAYER_GAME]);
	CameraMain* camera = reinterpret_cast<CameraMain*>(Game3D::GetCamera());
	camera->SetPlayer(layer->GetPlayer());
}

void SceneGame::Stage2()
{
}

void SceneGame::Stage3()
{
}

void SceneGame::Stage4()
{
}
