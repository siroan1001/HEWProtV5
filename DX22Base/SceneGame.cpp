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

//SceneGame::CameraKind SceneGame::m_mainCamera;
//CameraBase* SceneGame::m_pCamera[];
SceneGame::GameStatus SceneGame::m_GameStatus;
SceneGame::StageNumber SceneGame::m_StageNuber;

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

	//m_pEffect = new EffectManager;

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

	//m_pLayer[E_LAYER_BG] = new LayerBG;		//これ
	//m_pLayer[E_LAYER_BUCK_OBJECT] = NULL;
	//m_pLayer[E_LAYER_GAME] = new LayerGame(m_pCamera[m_mainCamera], &m_GameStatus);		//これ
	//m_pLayer[E_LAYER_UI] = NULL;

	//EffectManager::SetCamera(m_pCamera[m_mainCamera]);

	//LayerGame* layer = reinterpret_cast<LayerGame*>(m_pLayer[E_LAYER_GAME]);
	//CameraMain* camera = reinterpret_cast<CameraMain*>(m_pCamera[E_CAM_MAIN]);
	//camera->SetPlayer(layer->GetPlayer());

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

	//カメラの終了
	//for (int i = 0; i < E_CAM_MAX; i++)
	//{
	//	delete m_pCamera[i];
	//}

	//delete m_pEffect;
}

void SceneGame::Update()
{
	//m_pEffect->Update();

	//if (m_mainCamera == E_CAM_EVENT)
	//{
	//	CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[m_mainCamera]);
	//	if (!pEvent->IsEvent())
	//	{
	//		m_mainCamera = E_CAM_MAIN;
	//		LayerGame* game = reinterpret_cast<LayerGame*>(m_pLayer[E_LAYER_GAME]);
	//		game->SetCamera(m_pCamera[m_mainCamera]);
	//		m_pLayer[E_LAYER_GAME] = game;
	//	}
	//}
	//else if (m_mainCamera == E_CAM_DELAY)
	//{
	//	CameraDelay* pDelay = reinterpret_cast<CameraDelay*>(m_pCamera[m_mainCamera]);
	//	if (!pDelay->IsDelay())
	//	{
	//		m_mainCamera = E_CAM_MAIN;
	//		CameraMain* cam = reinterpret_cast<CameraMain*>(m_pCamera[E_CAM_MAIN]);
	//		cam->SetLook(pDelay->GetLook());
	//		m_pCamera[E_CAM_MAIN] = cam;
	//		LayerGame* game = reinterpret_cast<LayerGame*>(m_pLayer[E_LAYER_GAME]);
	//		game->SetCamera(m_pCamera[m_mainCamera]);
	//		m_pLayer[E_LAYER_GAME] = game;
	//	}
	//}

	////カメラの更新
	//if (m_GameStatus == E_GAME_STATUS_NORMAL)
	//	m_pCamera[m_mainCamera]->Update();

	for (int i = 0; i < E_LAYER_MAX; i++)
	{
		if (!m_pLayer[i])	continue;
		m_pLayer[i]->Update();
	}

	//カメラの切り替え
	//CameraKind camera = m_mainCamera;
	//if (IsKeyPress('C'))
	//{
	//	if (IsKeyTrigger('1'))	camera = E_CAM_DEBUG;
	//	if (IsKeyTrigger('2'))	camera = E_CAM_MAIN;
	//}
	//if (m_mainCamera != camera)
	//{
	//	m_mainCamera = camera;
	//	LayerGame* temp = reinterpret_cast<LayerGame*>(m_pLayer[E_LAYER_GAME]);
	//	temp->SetCamera(m_pCamera[m_mainCamera]);
	//	m_pLayer[E_LAYER_GAME] = temp;
	//}

	//if (IsKeyPress('Z'))
	//{
	//	m_pEffect->AtkEffect(EffectManager::E_EFFECT_KIND_ATK, -7.6f, 3.25f, 0.0f);
	//}

	//ゴールならフラグをtrueにする
	//if (m_GameStatus == E_GAME_STATUS_GOAL)
	//{
	//	if (IsKeyPress('R'))
	//	{
	//		//次のステージが作られたら下を書き換える
	//		//今は次のステージがないのでNORMALになっている
	//		m_GameStatus = E_GAME_STATUS_NORMAL;
	//		CameraReset();//カメラリセット関数
	//	}
	//}
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

	//m_pEffect->Draw();
}



SceneGame::GameStatus SceneGame::GetGameStatus()
{
	return m_GameStatus;
}

void SceneGame::SetGameStatus(GameStatus status)
{
	m_GameStatus = status;
}
SceneGame::StageNumber SceneGame::GetStageNum()
{
	return m_StageNuber;
}

//void SceneGame::CameraReset()
//{
//	CameraMain* pMain = new CameraMain;
//	pMain->SetLook(XMFLOAT3(-5.0f, 4.25f, 0.0f));
//	m_pCamera[E_CAM_MAIN] = pMain;
//
//	LayerGame* layer = reinterpret_cast<LayerGame*>(m_pLayer[E_LAYER_GAME]);
//	CameraMain* camera = reinterpret_cast<CameraMain*>(m_pCamera[E_CAM_MAIN]);
//	camera->SetPlayer(layer->GetPlayer());
//
//}

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
