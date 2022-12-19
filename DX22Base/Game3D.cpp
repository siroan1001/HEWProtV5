#include "Game3D.h"
#include "Geometory.h"
#include "Input.h"
#include "CameraBase.h"
#include "CameraDebug.h"
#include "CameraMain.h"
#include "Stage.h"
#include "ShadowBlock.h"
#include "Light.h"
#include "Collision.h"
#include "Layer.h"
#include "LayerGame.h"

Game3D::Game3D()
{
	m_mainCamera = E_CAM_MAIN;
	m_pCamera[E_CAM_MAIN] = new CameraMain;
	m_pCamera[E_CAM_DEBUG] = new CameraDebug;

	m_pLayer[E_LAYER_GAME] = new LayerGame(m_pCamera[m_mainCamera]);

	LayerGame* layer = reinterpret_cast<LayerGame*>(m_pLayer[E_LAYER_GAME]);
	CameraMain* camera = reinterpret_cast<CameraMain*>(m_pCamera[E_CAM_MAIN]);
	camera->SetPlayer(layer->GetPlayer());
}

Game3D::~Game3D()
{
	//レイヤーの終了
	delete m_pLayer[E_LAYER_GAME];

	//カメラの終了
	for (int i = 0; i < E_CAM_MAX; i++)
	{
		delete m_pCamera[i];
	}

}

void Game3D::Update()
{
	//カメラの更新
	m_pCamera[m_mainCamera]->Update();

	m_pLayer[E_LAYER_GAME]->Update();

	//カメラの切り替え
	CameraKind camera = m_mainCamera;
	if (IsKeyPress('C'))
	{
		if (IsKeyTrigger('1'))	camera = E_CAM_DEBUG;
		if (IsKeyTrigger('2'))	camera = E_CAM_MAIN;
	}
	if (m_mainCamera != camera)
	{
		m_mainCamera = camera;
		LayerGame* temp = reinterpret_cast<LayerGame*>(m_pLayer[0]);
		temp->SetCamera(m_pCamera[m_mainCamera]);
		m_pLayer[E_LAYER_GAME] = temp;
	}
}

void Game3D::Draw()
{
	//ジオメトリーのビュー行列とプロジェクション行列を設定する
	SetGeometoryVPMatrix(m_pCamera[m_mainCamera]->GetViewMatrix(), m_pCamera[m_mainCamera]->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV));
	
	m_pLayer[E_LAYER_GAME]->Draw();
}