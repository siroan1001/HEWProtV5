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
#include "Fade.h"

Fade* g_pFade;

Game3D::Game3D()
	:m_cylinderFlag(false)
{
	//�X�e�[�W�̐���
	m_pStage = new Stage;

	//�v���C���[�̐���
	m_pPlayer = new Player;

	g_pFade = new Fade;

	m_mainCamera = E_CAM_MAIN;
	m_pCamera[E_CAM_MAIN] = new CameraMain(m_pPlayer);
	m_pCamera[E_CAM_DEBUG] = new CameraDebug;

	m_pShadowBlock = new ShadowBlock;
	Stage::Info info = { {0.0f, 0.5f, 0.0f}, {1.0f, 1.5f, 1.0f}, {0.0f, 0.0f, 0.0f} };
	m_pShadowBlock->SetShadowBlock(info);

	m_pLight = new Light;

	m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
	m_pPlayer->InitDirection(m_pStage->GetNum() + m_pShadowBlock->GetNum());

	// �摜�������@�̐ݒ�
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

}
Game3D::~Game3D()
{
	delete m_pBlend;
	delete g_pFade;
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
	if (IsKeyPress('0'))
	{
		g_pFade->StartOut();
	}
	g_pFade->Update();

	//�J�����̍X�V
	m_pCamera[m_mainCamera]->Update();

	m_pShadowBlock->Update();
	m_pLight->Update();
	m_pShadowBlock->Update();

	//�v���C���[�̍X�V
	//�J������PlayerCamera�̏ꍇ�̂ݏ�������
	if(m_mainCamera == E_CAM_MAIN)	m_pPlayer->Update();

	//�J�����̐؂�ւ�
	CameraKind camera = m_mainCamera;
	if (IsKeyPress('C'))
	{
		if (IsKeyTrigger('1'))	camera = E_CAM_DEBUG;
		if (IsKeyTrigger('2'))	camera = E_CAM_MAIN;
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
	
	//�X�e�[�W�̕`��
	m_pStage->Draw();

	//�v���C���[�̕`��
	m_pPlayer->Draw();

	//�V���h�E�u���b�N�̕`��
	m_pShadowBlock->Draw();

	//���C�g�̕`��
	m_pLight->Draw(); 
	
	g_pFade->Draw();

	
}

void Game3D::CheckCollision()
{
	
	//ShadowBlock��Ligth�̔���
	std::vector<std::vector<ShadowBlock::SmallBlockTemp>>* block = m_pShadowBlock->GetInfo();	//�V���h�E�u���b�N�̏��

	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
	{
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			if (Collision::RectAndCircle(init->Info, m_pLight->GetInfo(), m_pLight->GetRadius()))
			{
				init->life -= m_pLight->GetPower();		//�V���h�E�u���b�N�̃��C�t�����
				if (init->life <= 0.0f)
				{//���C�t���O�����������
					init->life = 0.0f;	//�O�ȉ��ɂȂ�Ȃ��悤�ɕ␳
					init->use = false;	//�g�p���ĂȂ���Ԃɂ���
				}
			}
		}
	}

	int num = 0;		//�v���C���[�ƃu���b�N�̓����蔻�肪���ڂ�������i�O�t���[���̂ǂ̕����ɓ������������m�F����̂Ɏg���j

	//Player��Stage�̓����蔻��
	for (num = 0; num < m_pStage->GetNum(); num++)
	{
		//�����蔻��Ɏg���v�f
		Stage::Info stage = m_pStage->GetInfo(num);		//�X�e�[�W�u���b�N�̏��
		Stage::Info player = m_pPlayer->GetInfo();		//�v���C���[�̏��i�v���C���[�̒��S��pos�Ƃ���j
		Stage::Info Oplayer = m_pPlayer->GetOldInfo();	//�v���C���[�̑O�t���[���̏��
		player.pos.y += player.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳
		Oplayer.pos.y += player.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳
		

		//�ǂ̕����ɓ������������m�F����
		if (Collision::Direction dire = Collision::RectAndRectDirection(player, Oplayer, stage, m_pPlayer->GetDirection(num)))
		{
			//�␳�ppos(����)
			XMFLOAT3 pos = m_pPlayer->GetInfo().pos;

			switch (dire)
			{//�������������ɉ����Ă̏���
			case Collision::E_DIRECTION_L:	//��
				pos.x = stage.pos.x + stage.size.x / 2.0f + player.size.x / 2.0f;
				break;
			case Collision::E_DIRECTION_R:	//�E
				pos.x = stage.pos.x - stage.size.x / 2.0f - player.size.x / 2.0f;
				break;
			case Collision::E_DIRECTION_U:	//��
				pos.y = stage.pos.y + stage.size.y / 2.0f;
				m_pPlayer->ResetMove();		//�d�͂����Z�b�g����
				break;
			case Collision::E_DIRECTION_D:	//��
				pos.y = stage.pos.y - stage.size.y / 2.0f - player.size.y;
				m_pPlayer->ResetMove();
				break;
			default:
				break;
			}
			m_pPlayer->SetPos(pos);		//�␳�����l���v���C���[�ɔ��f
			m_pPlayer->SetDirection(dire, num);		//�ǂ̕����ɓ�����������ێ�����
			
		}
	}

	//Player��ShadowBloack�̓����蔻��
	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
	{
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init, num++)
		{
			Stage::Info shadow = init->Info;		//�V���h�E�u���b�N�̏��
			Stage::Info player = m_pPlayer->GetInfo();		//�v���C���[�̏��
			player.pos.y += player.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳

			if (init->use)
			{//���݂���i�����߂��̏����j
				Stage::Info Oplayer = m_pPlayer->GetOldInfo();		//�O�t���[���̏��
				Oplayer.pos.y += player.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳

				if (Collision::Direction dire = Collision::RectAndRectDirection(player, Oplayer, shadow, m_pPlayer->GetDirection(num)))
				{
					//�␳�ppos
					XMFLOAT3 pos = m_pPlayer->GetInfo().pos;
					switch (dire)
					{
					case Collision::E_DIRECTION_L:		//��
					case Collision::E_DIRECTION_R:		//�E
						Stage::Info PlayerBot;
						Stage::Info PlayerTop;
						PlayerBot = PlayerTop = m_pPlayer->GetInfo();
						PlayerBot.size.y = 0.1f;		//�����̑傫��
						PlayerBot.pos.y += PlayerBot.size.y / 2.0f;		//�v���C���[�̌��̍��W���瑫���̑傫�������炷
						PlayerTop.size.y -= PlayerBot.size.y;		//�̂̑傫���i�v���C���[�S�̂��瑫���̑傫�����������傫���j
						PlayerTop.pos.y += PlayerBot.size.y + PlayerTop.size.y / 2.0f;	//�v���C���[�̌��̍��W���瑫���̑傫�����Ƒ̂̔������炷
						{
							bool bTop = Collision::RectAndRect(PlayerTop, shadow);		//�̂��u���b�N�Ɠ������Ă��邩
							bool bBot = Collision::RectAndRect(PlayerBot, shadow);		//�������u���b�N�Ɠ������Ă��邩
							if (bBot && !bTop)		//�����͓������Ă��đ͓̂������Ă��Ȃ��ꍇ�i���𖳎�����
							{//��
								pos.y = shadow.pos.y + shadow.size.y / 2.0f;		//�u���b�N�̏�ɕ␳
								m_pPlayer->ResetMove();		//�d�͂����Z�b�g
							}
							else
							{//��
								if (player.pos.x < shadow.pos.x)
								{//�E
									pos.x = shadow.pos.x - shadow.size.x / 2.0f - player.size.x / 2.0f;
								}
								else if (player.pos.x >= shadow.pos.x)
								{//��
									pos.x = shadow.pos.x + shadow.size.x / 2.0f + player.size.x / 2.0f;
								}
							}
						}
						break;
					case Collision::E_DIRECTION_U:		//��
						pos.y = shadow.pos.y + shadow.size.y / 2.0f;
						m_pPlayer->ResetMove();
						break;	
					case Collision::E_DIRECTION_D:		//��
						pos.y = shadow.pos.y - shadow.size.y / 2.0f - player.size.y;
						m_pPlayer->ResetMove();
						break;
					default:
						continue;
						break;
					}
					m_pPlayer->SetPos(pos);		//�v���C���[�ɔ��f
					m_pPlayer->SetDirection(dire, num);		//��������������ێ�
				}
			}
			else if (!init->use)
			{//���݂��Ȃ��i���������鏈���j
				if (Collision::RectAndRect(player, shadow))		//�v���C���[�ƃu���b�N���������Ă��邩
				{
					init->life -= m_pLight->GetPower();		
					if (init->life <= 0.0f)
					{
						init->life = 0.0f;
						init->use = false;
					}
				}
			}			
		}
	}
}
