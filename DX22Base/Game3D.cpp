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
	//�X�e�[�W�̐���
	m_pStage = new Stage;

	//�v���C���[�̐���
	m_pPlayer = new Player;

	//�J�����̐���
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
	//�X�e�[�W�̏I��
	//delete m_pStage;
	delete m_pPlayer;
	delete m_pLight;
	delete m_pShadowBlock;

	//�J�����̏I��
	for (int i = 0; i < E_CAM_MAX; i++)
	{
		delete m_pCamera[i];
	}

}
void Game3D::Update()
{
	//�J�����̐؂�ւ�
	//if (m_mainCamera == E_CAM_EVENT)
	//{
	//	CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[m_mainCamera]);
	//	if (!pEvent->IsEvent())
	//	{
	//		m_mainCamera = E_CAM_PLAYER;
	//		m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
	//	}
	//}

	//�J�����̍X�V
	m_pCamera[m_mainCamera]->Update();

	m_pShadowBlock->Update();
	m_pLight->Update();
	m_pShadowBlock->Update();


	//�v���C���[�̍X�V
	//�J������PlayerCamera�̏ꍇ�̂ݏ�������
	/*if(m_mainCamera == E_CAM_MAIN)*/	m_pPlayer->Update();

	//�J�����̐؂�ւ�
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
	//�W�I���g���[�̃r���[�s��ƃv���W�F�N�V�����s���ݒ肷��
	SetGeometoryVPMatrix(m_pCamera[m_mainCamera]->GetViewMatrix(), m_pCamera[m_mainCamera]->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV));
	
	//���̕`��
	//DrawBox();

	//�X�e�[�W�̕`��
	m_pStage->Draw();

	//�v���C���[�̕`��
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

	//ShadowBlock��Ligth�̔���
	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
	{
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			//if (!init->use)	continue;

			bool flag = Collision::RectAndCircle(init->Info, m_pLight->GetInfo(), m_pLight->GetRadius());

			if (flag)
			{
				//printf("������");
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

	//Player��Stage�̓����蔻��
	for (int i = 0; i < m_pStage->GetNum(); i++)
	{
		//�����蔻��Ɏg���v�f
		Stage::Info stage = m_pStage->GetInfo(i);
		Stage::Info player = m_pPlayer->GetInfo();
		player.pos.y += player.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳

		//Obj���m���������Ă��邩
		if (Collision::RectAndRect(stage, player))
		{
			//�ǂ̕����ɓ������Ă��邩
			Collision::Direction dire = Collision::LineAndLine(stage, player);

			//�␳�ppos
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

	//Player��ShadowBloack�̓����蔻��
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
