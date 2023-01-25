#include "Game3D.h"
#include "SceneGame.h"
#include "SceneTitle.h"
//#include "SceneResult.h"
//#include "SceneClear.h"
#include "CameraMain.h"
#include "CameraEvent.h"
#include "CameraDelay.h"
#include "CameraDebug.h"

SceneBace* Game3D::m_pScene[];
Game3D::SceneKind Game3D::m_SceneKind;
CameraBase* Game3D::m_pCamera[];
Game3D::CameraKind Game3D::m_mainCamera;

Game3D::Game3D()
{
	CameraMain* pMain = new CameraMain;
	pMain->SetLook(XMFLOAT3(-5.0f, 4.05f, 0.0f));
	m_pCamera[E_CAM_MAIN] = pMain;
	CameraEvent* pEvent = new CameraEvent();
	pEvent->SetEvent(XMFLOAT3(-3.0f, 4.25f, 3.0f), XMFLOAT3(-3.0f, 4.25f, 3.0f), 3.0f);
	m_pCamera[E_CAM_EVENT] = pEvent;
	CameraDelay* pDelay = new CameraDelay;
	pDelay->SetCamera(XMFLOAT3(-4.3f, 4.25f, 0.0f), 3.0f, 1.0f);
	m_pCamera[E_CAM_DELAY] = pDelay;
	m_pCamera[E_CAM_DEBUG] = new CameraDebug;

	m_mainCamera = E_CAM_MAIN;

	m_pScene[E_SCENE_KIND_TITLE] = new SceneTitle;
	m_pScene[E_SCENE_KIND_GAME] = new SceneGame(SceneGame::E_STAGE_NUMBER_STAGE_1);
	/*m_pScene[E_SCENE_KIND_RESULT] = new SceneResult;
	m_pScene[E_SCENE_KIND_CLEAR] = new SceneClear;*/

	m_SceneKind = E_SCENE_KIND_TITLE;
}

Game3D::~Game3D()
{
	for (int i = 0; i < E_CAM_MAX; i++)
	{
		delete m_pCamera[i];
	}

	for (int i = 0; i < E_SCENE_KIND_MAX; i++)
	{
		delete m_pScene[i];
	}
}

void Game3D::Update()
{
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

	//ƒJƒƒ‰‚ÌXV
	m_pCamera[m_mainCamera]->Update();

	m_pScene[m_SceneKind]->Update();
}

void Game3D::Draw()
{
	m_pScene[m_SceneKind]->Draw();
}

void Game3D::SetScene(SceneKind nextScene)
{
	m_SceneKind = nextScene;
}

CameraBase * Game3D::GetCamera()
{
	return m_pCamera[m_mainCamera];
}
