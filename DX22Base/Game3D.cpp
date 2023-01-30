#include "Game3D.h"
#include "SceneGame.h"
#include "SceneTitle.h"
//#include "SceneResult.h"
//#include "SceneClear.h"
#include "SceneStageSelect.h"
#include "CameraMain.h"
#include "CameraEvent.h"
#include "CameraDelay.h"
#include "CameraDebug.h"

SceneBace* Game3D::m_pScene[];
Game3D::SceneKind Game3D::m_SceneKind;
CameraBase* Game3D::m_pCamera[];
Game3D::CameraKind Game3D::m_mainCamera;

Fade* g_pFade;
Game3D::SceneKind g_PrevScene;
Game3D::Game3D()
{
	CameraMain* pMain = new CameraMain;
	pMain->SetLook(XMFLOAT3(-5.48f, 4.05f, 0.0f));
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
	m_pScene[E_SCENE_KIND_STAGESELECT] = new SceneStageSelect(Game3D::GetCamera(), SceneGame::E_STAGE_NUMBER_STAGE_1);
	
	g_pFade = new Fade;
	m_SceneKind = E_SCENE_KIND_TITLE;
	g_PrevScene = m_SceneKind;
}

Game3D::~Game3D()
{
	delete g_pFade;
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


	//ƒJƒƒ‰‚ÌXV
	m_pCamera[m_mainCamera]->Update();

	m_pScene[m_SceneKind]->Update();
	
	g_pFade->Update();
}

void Game3D::Draw()
{
	m_pScene[m_SceneKind]->Draw();
	
	g_pFade->Draw();
}

SceneBace * Game3D::GetScene()
{
	return m_pScene[m_SceneKind];
}

Game3D::SceneKind Game3D::GetSceneKind()
{
	return m_SceneKind;
}

void Game3D::SetScene(SceneKind nextScene)
{
	g_PrevScene = nextScene;
	
	g_pFade->StartOut();
}

CameraBase * Game3D::GetCamera()
{
	return m_pCamera[m_mainCamera];
}

void Game3D::StartSceneChange()
{
	m_SceneKind = g_PrevScene;
	m_pScene[m_SceneKind]->ReStart();
}
