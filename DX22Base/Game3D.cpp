#include "Game3D.h"
#include "Geometory.h"
#include "Input.h"
#include "CameraBase.h"
#include "CameraDebug.h"
//#include "CameraPlayer.h"
//#include "CameraEvent.h"
#include "CameraMain.h"
#include "Stage.h"
#include "ShadowBlock.h"
#include "Light.h"
#include "Collision.h"

Game3D::Game3D()
	:m_cylinderFlag(false)
{
	//ステージの生成
	m_pStage = new Stage;

	//プレイヤーの生成
	m_pPlayer = new Player;

	//カメラの生成
	//m_mainCamera = E_CAM_EVENT;
	//m_pCamera[E_CAM_PLAYER] = new CameraPlayer(m_pPlayer);
	//m_pCamera[E_CAM_DEBUG] = new CameraDebug();
	//CameraEvent* pEvent = new CameraEvent();
	//pEvent->SetEvent(XMFLOAT3(4.0f, 5.0f, 9.0f), XMFLOAT3(0.0f, 1.5f, 0.0f), 3.0f);
	//m_pCamera[E_CAM_EVENT] = pEvent;

	//m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);

	//m_pPlayer = new Player;

	m_mainCamera = E_CAM_MAIN;
	m_pCamera[E_CAM_MAIN] = new CameraMain(m_pPlayer);
	m_pCamera[E_CAM_DEBUG] = new CameraDebug;

	m_pShadowBlock = new ShadowBlock;
	Stage::Info info = { {0.0f, 0.5f, 0.0f}, {1.0f, 1.5f, 1.0f}, {0.0f, 0.0f, 0.0f} };
	m_pShadowBlock->SetShadowBlock(info);

	m_pLight = new Light;

	m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
}
Game3D::~Game3D()
{
	//ステージの終了
	//delete m_pStage;
	delete m_pPlayer;
	delete m_pLight;
	delete m_pShadowBlock;

	//カメラの終了
	for (int i = 0; i < E_CAM_MAX; i++)
	{
		delete m_pCamera[i];
	}

}
void Game3D::Update()
{
	//カメラの切り替え
	//if (m_mainCamera == E_CAM_EVENT)
	//{
	//	CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[m_mainCamera]);
	//	if (!pEvent->IsEvent())
	//	{
	//		m_mainCamera = E_CAM_PLAYER;
	//		m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
	//	}
	//}

	//カメラの更新
	m_pCamera[m_mainCamera]->Update();

	m_pShadowBlock->Update();
	m_pLight->Update();
	m_pShadowBlock->Update();


	//プレイヤーの更新
	//カメラがPlayerCameraの場合のみ処理する
	/*if(m_mainCamera == E_CAM_MAIN)*/	m_pPlayer->Update();

	//カメラの切り替え
	CameraKind camera = m_mainCamera;
	if (IsKeyPress('C'))
	{
		if (IsKeyTrigger('1'))	camera = E_CAM_DEBUG;
		if (IsKeyTrigger('2'))	camera = E_CAM_MAIN;
		//if (IsKeyTrigger('3'))
		//{
		//	CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[E_CAM_EVENT]);
		//	pEvent->SetEvent(XMFLOAT3(4.0f, 5.0f, 9.0f), XMFLOAT3(0.0f, 1.5f, 0.0f), 3.0f);
		//	camera = E_CAM_EVENT;
		//}
		
	}
	if (m_mainCamera != camera)
	{
		m_mainCamera = camera;
		m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
	}

	if (IsKeyTrigger('P'))
	{
		m_cylinderFlag ^= 1;
	}

	CheckCollision();
}
void Game3D::Draw()
{
	//ジオメトリーのビュー行列とプロジェクション行列を設定する
	SetGeometoryVPMatrix(m_pCamera[m_mainCamera]->GetViewMatrix(), m_pCamera[m_mainCamera]->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV));
	
	//箱の描画
	//DrawBox();

	//ステージの描画
	m_pStage->Draw();

	//プレイヤーの描画
	m_pPlayer->Draw();


	//DrawCylinder();

	//if(m_cylinderFlag)
	//m_pLight->GetRadius();

	m_pShadowBlock->Draw();
	m_pLight->Draw();

	
}

void Game3D::CheckCollision()
{
	std::vector<std::vector<ShadowBlock::SmallBlockTemp>>* block = m_pShadowBlock->GetInfo();

	//ShadowBlockとLigthの判定
	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
	{
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			//if (!init->use)	continue;

			bool flag = Collision::RectAndCircle(init->Info, m_pLight->GetInfo(), m_pLight->GetRadius());

			if (flag)
			{
				//printf("あたり");
				//m_pShadowBlock->SetUse(i, false);
				init->life -= m_pLight->GetPower();
				if (init->life <= 0.0f)
				{
					init->life = 0.0f;
					init->use = false;
				}
			}
		}
	}

	//PlayerとStageの当たり判定
	for (int i = 0; i < m_pStage->GetNum(); i++)
	{
		//当たり判定に使う要素
		Stage::Info stage = m_pStage->GetInfo(i);
		Stage::Info player = m_pPlayer->GetInfo();
		player.pos.y += player.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

		//Obj同士が当たっているか
		if (Collision::RectAndRect(stage, player))
		{
			//どの方向に当たっているか
			Collision::Direction dire = Collision::LineAndLine(stage, player);

			//補正用pos
			XMFLOAT3 pos = m_pPlayer->GetInfo().pos;

			switch (dire)
			{
			case Collision::E_DIRECTION_L:
				pos.x = stage.pos.x + stage.size.x / 2.0f + player.size.x / 2.0f;
				break;
			case Collision::E_DIRECTION_R:
				pos.x = stage.pos.x - stage.size.x / 2.0f - player.size.x / 2.0f;
				break;
			case Collision::E_DIRECTION_U:
				pos.y = stage.pos.y + stage.size.y / 2.0f;
				m_pPlayer->ResetMove();
				break;
			case Collision::E_DIRECTION_D:
				pos.y = stage.pos.y - stage.size.y / 2.0f;
				break;
			default:
				break;
			}
			m_pPlayer->SetPos(pos);
			player.pos = pos;
			
			
		}
	}

	//PlayerとShadowBloackの当たり判定
	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
	{
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			if (!init->use)	continue;

			Stage::Info shadow = init->Info;
			Stage::Info player = m_pPlayer->GetInfo();
			player.pos.y += player.size.y / 2.0f;

			if (Collision::RectAndRect(shadow, player))
			{
				float pos = shadow.pos.y + shadow.size.y / 2.0f;
				m_pPlayer->SetPos(XMFLOAT3(player.pos.x, pos, player.pos.z));
				m_pPlayer->ResetMove();
			}
		}
	}
}
