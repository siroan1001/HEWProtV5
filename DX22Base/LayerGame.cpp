#include "LayerGame.h"
#include "Game3D.h"

LayerGame::LayerGame(CameraBase* camera, Game3D::GameStatus* status)
{
	m_pCamera = camera;

	//�X�e�[�W�̐���
	m_pStage = new Stage;

	//�v���C���[�̐���
	m_pPlayer = new Player(Collision::E_DIRECTION_L);

	//�G�̐���
	m_pEnemys.push_back(new Enemy(Collision::E_DIRECTION_L, { -5.0f, 3.25f, 0.0f }));

	m_pLight = new Light;
	m_pLight->SetCamera(camera);

	m_pPlayer->SetCamera(camera);
	m_pPlayer->InitDirection(m_pStage->GetStageNum() + m_pStage->GetShadowNum());

	//m_pEnemy->SetCamera(camera);
	//m_pEnemy->InitDirection(m_pStage->GetStageNum() + m_pStage->GetShadowNum());

	for (int i = 0; i < m_pEnemys.size(); i++)
	{
		m_pEnemys[i]->SetCamera(camera);
		m_pEnemys[i]->InitDirection(m_pStage->GetStageNum() + m_pStage->GetShadowNum());
	}


	m_pRvsBlock = new ReverseBlock;

	m_pStartObj = new StartObj;
	m_pStartObj->SetCamera(camera);

	m_pChasingShadow = new ChasingShadow;
	m_pChasingShadow->SetPlayer(m_pPlayer);

	m_GameStatus = status;
}

LayerGame::~LayerGame()
{
	delete m_pChasingShadow;
	delete m_pStartObj;
	delete m_pRvsBlock;
	delete m_pLight;
	//delete m_pShadowBlock;
	m_pEnemys.clear();
	/*delete m_pEnemy;*/
	delete m_pPlayer;
	delete m_pStage;
}

void LayerGame::Update()
{
	//m_pShadowBlock->Update();
	m_pLight->Update();

	m_pChasingShadow->Update();

	//�v���C���[�̍X�V
	//�J������PlayerCamera�̏ꍇ�̂ݏ�������
	m_pPlayer->Update();

	//�G�̍X�V
	//m_pEnemy->Update();

	for (int i = 0; i < m_pEnemys.size(); i++)
	{
		m_pEnemys[i]->Update();
	}


	CheckCollision();
}

void LayerGame::Draw()
{
	//�X�e�[�W�̕`��
	m_pStage->Draw();

	//�v���C���[�̕`��
	m_pPlayer->Draw();

	//�G�̕`��
	//m_pEnemy->Draw();

	for (int i = 0; i < m_pEnemys.size(); i++)
	{
		m_pEnemys[i]->Draw();
	}

	//�V���h�E�u���b�N�̕`��
	//m_pShadowBlock->Draw();

	m_pRvsBlock->Draw();

	//���C�g�̕`��
	m_pLight->Draw();

	//�X�^�[�g�̕`��
	m_pStartObj->Draw();

	//�ǂ��Ă���e�̕`��
	m_pChasingShadow->Draw();
}

Player * LayerGame::GetPlayer()
{
	return m_pPlayer;
}

void LayerGame::SetCamera(CameraBase * camera)
{
	m_pCamera = camera;
	m_pLight->SetCamera(m_pCamera);
	m_pPlayer->SetCamera(m_pCamera);
}


void LayerGame::CheckCollision()
{
	//ShadowBlock��Ligth�̔���
	vector<ShadowBlock*> shadow = m_pStage->GetShadowBlock();	//�V���h�E�u���b�N�̏��
	vector<vector<ShadowBlock::SmallBlockTemp>>* block;
	
	for (int i = 0; i < shadow.size(); i++)
	{
		block = shadow[i]->GetSmallBlockInfo();
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
	}

	int num = 0;		//�v���C���[�ƃu���b�N�̓����蔻�肪���ڂ�������i�O�t���[���̂ǂ̕����ɓ������������m�F����̂Ɏg���j
	 
	//Player��Stage�̓����蔻��
	for (num = 0; num < m_pStage->GetStageNum(); num++)
	{
		//�����蔻��Ɏg���v�f
		Def::Info stage = m_pStage->GetInfo(num);		//�X�e�[�W�u���b�N�̏��
		Def::Info player = m_pPlayer->GetInfo();		//�v���C���[�̏��i�v���C���[�̒��S��pos�Ƃ���j
		Def::Info Oplayer = m_pPlayer->GetOldInfo();	//�v���C���[�̑O�t���[���̏��
		player.pos.y += player.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳
		Oplayer.pos.y += player.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳


		//�ǂ̕����ɓ������������m�F����
		if (Collision::Direction dire = Collision::RectAndRectDirection(player, Oplayer, stage, m_pPlayer->GetStageCollistonDirection(num)))
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
			m_pPlayer->SetStageCollisionDirection(dire, num);		//�ǂ̕����ɓ�����������ێ�����

		}

		
	}

	num--;

	Def::Info cam = m_pCamera->GetInfo();

	//Player��ShadowBloack�̓����蔻��
	for (int i = 0; i < shadow.size(); i++)
	{
		if (!Collision::RectAndRect(shadow[i]->GetInfo(), cam))	continue;
		block = shadow[i]->GetSmallBlockInfo();

		for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
		{
			for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init, num++)
			{
				Def::Info shadow = init->Info;		//�V���h�E�u���b�N�̏��




				Def::Info player = m_pPlayer->GetInfo();		//�v���C���[�̏��
				player.pos.y += player.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳



				if (init->use)
				{//���݂���i�����߂��̏����j
					Def::Info Oplayer = m_pPlayer->GetOldInfo();		//�O�t���[���̏��
					Oplayer.pos.y += player.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳

					if (Collision::Direction dire = Collision::RectAndRectDirection(player, Oplayer, shadow, m_pPlayer->GetStageCollistonDirection(num)))
					{
						//�␳�ppos
						XMFLOAT3 pos = m_pPlayer->GetInfo().pos;
						switch (dire)
						{
						case Collision::E_DIRECTION_L:		//��
						case Collision::E_DIRECTION_R:		//�E
							Def::Info PlayerBot;
							Def::Info PlayerTop;
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
						m_pPlayer->SetStageCollisionDirection(dire, num);		//��������������ێ�
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

	//�v���C���[�Ɣ��˔�
	for (int i = 0; i < m_pRvsBlock->GetStageNum(); i++)
	{
		if (Collision::RectAndRect(m_pPlayer->GetInfo(), m_pRvsBlock->GetInfo(i)))
		{
			m_pPlayer->SetDirection(m_pRvsBlock->GetDirection(i));
		}
	}

	//�v���C���[�ƃX�^�[�g��
	if (*m_GameStatus == Game3D::E_GAME_STATUS_START)
	{
		Def::Info startInfo = m_pStartObj->GetInfo();
		if (Collision::RectAndRect(m_pPlayer->GetInfo(), startInfo))
		{
			Game3D::SetGameStatus(Game3D::E_GAME_STATUS_NORMAL);
		}
	}

	/*
	//Enemy��Stage�̓����蔻��
	for (num = 0; num < m_pStage->GetStageNum(); num++)
	{
		//�����蔻��Ɏg���v�f
		Def::Info stage = m_pStage->GetInfo(num);		//�X�e�[�W�u���b�N�̏��
		Def::Info Enemy = m_pEnemy->GetInfo();		//�v���C���[�̏��i�v���C���[�̒��S��pos�Ƃ���j
		Def::Info OEnemy = m_pEnemy->GetOldInfo();	//�v���C���[�̑O�t���[���̏��
		Enemy.pos.y += Enemy.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳
		OEnemy.pos.y += Enemy.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳


		//�ǂ̕����ɓ������������m�F����
		if (Collision::Direction dire = Collision::RectAndRectDirection(Enemy, OEnemy, stage, m_pEnemy->GetStageCollistonDirection(num)))
		{
			//�␳�ppos(����)
			XMFLOAT3 pos = m_pEnemy->GetInfo().pos;

			switch (dire)
			{//�������������ɉ����Ă̏���
			case Collision::E_DIRECTION_L:	//��
				pos.x = stage.pos.x + stage.size.x / 2.0f + Enemy.size.x / 2.0f;
				m_pEnemy->SetDirection(Collision::E_DIRECTION_R);
				break;
			case Collision::E_DIRECTION_R:	//�E
				pos.x = stage.pos.x - stage.size.x / 2.0f - Enemy.size.x / 2.0f;
				m_pEnemy->SetDirection(Collision::E_DIRECTION_L);
				break;
			case Collision::E_DIRECTION_U:	//��
				pos.y = stage.pos.y + stage.size.y / 2.0f;
				m_pEnemy->ResetMove();		//�d�͂����Z�b�g����
				break;
			case Collision::E_DIRECTION_D:	//��
				pos.y = stage.pos.y - stage.size.y / 2.0f - Enemy.size.y;
				m_pEnemy->ResetMove();
				break;
			default:
				break;
			}
			m_pEnemy->SetPos(pos);		//�␳�����l���v���C���[�ɔ��f
			m_pEnemy->SetStageCollisionDirection(dire, num);		//�ǂ̕����ɓ�����������ێ�����

		}
	}

	num--;

	//Enemy��ShadowBloack�̓����蔻��
	for (int i = 0; i < shadow.size(); i++)
	{
		if (!Collision::RectAndRect(shadow[i]->GetInfo(), cam))	continue;
		block = shadow[i]->GetSmallBlockInfo();
		
		for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
		{
			for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init, num++)
			{
				Def::Info shadow = init->Info;		//�V���h�E�u���b�N�̏��
				

				

				Def::Info Enemy = m_pEnemy->GetInfo();		//�G�l�~�[�̏��
				Enemy.pos.y += Enemy.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳

				

				if (init->use)
				{//���݂���i�����߂��̏����j
					Def::Info OEnemy = m_pEnemy->GetOldInfo();		//�O�t���[���̏��
					OEnemy.pos.y += Enemy.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳

					if (Collision::Direction dire = Collision::RectAndRectDirection(Enemy, OEnemy, shadow, m_pEnemy->GetStageCollistonDirection(num)))
					{
						//�␳�ppos
						XMFLOAT3 pos = m_pEnemy->GetInfo().pos;
						switch (dire)
						{
						case Collision::E_DIRECTION_L:		//��
						case Collision::E_DIRECTION_R:		//�E
							//��
							if (Enemy.pos.x < shadow.pos.x)
							{//�E
								pos.x = shadow.pos.x - shadow.size.x / 2.0f - Enemy.size.x / 2.0f;
								m_pEnemy->SetDirection(Collision::E_DIRECTION_R);
							}
							else if (Enemy.pos.x >= shadow.pos.x)
							{//��
								pos.x = shadow.pos.x + shadow.size.x / 2.0f + Enemy.size.x / 2.0f;
								m_pEnemy->SetDirection(Collision::E_DIRECTION_L);
							}
							break;
						case Collision::E_DIRECTION_U:		//��
							pos.y = shadow.pos.y + shadow.size.y / 2.0f;
							m_pEnemy->ResetMove();
							break;
						case Collision::E_DIRECTION_D:		//��
							pos.y = shadow.pos.y - shadow.size.y / 2.0f - Enemy.size.y;
							m_pEnemy->ResetMove();
							break;
						default:
							continue;
							break;
						}
						m_pEnemy->SetPos(pos);		//�G�l�~�[�ɔ��f
						m_pEnemy->SetStageCollisionDirection(dire, num);		//��������������ێ�
					}
				}
				else if (!init->use)
				{//���݂��Ȃ��i���������鏈���j
					if (Collision::RectAndRect(Enemy, shadow))		//�G�l�~�[�ƃu���b�N���������Ă��邩
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

	//�G�l�~�[�Ɣ��˔�
	for (int i = 0; i < m_pRvsBlock->GetStageNum(); i++)
	{
		if (Collision::RectAndRect(m_pEnemy->GetInfo(), m_pRvsBlock->GetInfo(i)))
		{
			m_pEnemy->SetDirection(m_pRvsBlock->GetDirection(i));
		}
	}
	*/



	for (int i = 0; i < m_pEnemys.size(); i++)
	{
		//Enemy��Stage�̓����蔻��
		for (num = 0; num < m_pStage->GetStageNum(); num++)
		{
			//�����蔻��Ɏg���v�f
			Def::Info stage = m_pStage->GetInfo(num);		//�X�e�[�W�u���b�N�̏��
			Def::Info Enemy = m_pEnemys[i]->GetInfo();		//�v���C���[�̏��i�v���C���[�̒��S��pos�Ƃ���j
			Def::Info OEnemy = m_pEnemys[i]->GetOldInfo();	//�v���C���[�̑O�t���[���̏��
			Enemy.pos.y += Enemy.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳
			OEnemy.pos.y += Enemy.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳


			//�ǂ̕����ɓ������������m�F����
			if (Collision::Direction dire = Collision::RectAndRectDirection(Enemy, OEnemy, stage, m_pEnemys[i]->GetStageCollistonDirection(num)))
			{
				//�␳�ppos(����)
				XMFLOAT3 pos = m_pEnemys[i]->GetInfo().pos;

				switch (dire)
				{//�������������ɉ����Ă̏���
				case Collision::E_DIRECTION_L:	//��
					pos.x = stage.pos.x + stage.size.x / 2.0f + Enemy.size.x / 2.0f;
					m_pEnemys[i]->SetDirection(Collision::E_DIRECTION_R);
					break;
				case Collision::E_DIRECTION_R:	//�E
					pos.x = stage.pos.x - stage.size.x / 2.0f - Enemy.size.x / 2.0f;
					m_pEnemys[i]->SetDirection(Collision::E_DIRECTION_L);
					break;
				case Collision::E_DIRECTION_U:	//��
					pos.y = stage.pos.y + stage.size.y / 2.0f;
					m_pEnemys[i]->ResetMove();		//�d�͂����Z�b�g����
					break;
				case Collision::E_DIRECTION_D:	//��
					pos.y = stage.pos.y - stage.size.y / 2.0f - Enemy.size.y;
					m_pEnemys[i]->ResetMove();
					break;
				default:
					break;
				}
				m_pEnemys[i]->SetPos(pos);		//�␳�����l���v���C���[�ɔ��f
				m_pEnemys[i]->SetStageCollisionDirection(dire, num);		//�ǂ̕����ɓ�����������ێ�����

			}
		}

		num--;

		//Enemy��ShadowBloack�̓����蔻��
		for (int j = 0; j < shadow.size(); j++)
		{
			if (!Collision::RectAndRect(shadow[j]->GetInfo(), cam))	continue;
			block = shadow[i]->GetSmallBlockInfo();

			for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
			{
				for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init, num++)
				{
					Def::Info shadow = init->Info;		//�V���h�E�u���b�N�̏��




					Def::Info Enemy = m_pEnemys[i]->GetInfo();		//�G�l�~�[�̏��
					Enemy.pos.y += Enemy.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳



					if (init->use)
					{//���݂���i�����߂��̏����j
						Def::Info OEnemy = m_pEnemys[i]->GetOldInfo();		//�O�t���[���̏��
						OEnemy.pos.y += Enemy.size.y / 2.0f;		//���W�������ɂ��邽�ߒ��S�ɂȂ�悤�ɕ␳

						if (Collision::Direction dire = Collision::RectAndRectDirection(Enemy, OEnemy, shadow, m_pEnemys[i]->GetStageCollistonDirection(num)))
						{
							//�␳�ppos
							XMFLOAT3 pos = m_pEnemys[i]->GetInfo().pos;
							switch (dire)
							{
							case Collision::E_DIRECTION_L:		//��
							case Collision::E_DIRECTION_R:		//�E
								//��
								if (Enemy.pos.x < shadow.pos.x)
								{//�E
									pos.x = shadow.pos.x - shadow.size.x / 2.0f - Enemy.size.x / 2.0f;
									m_pEnemys[i]->SetDirection(Collision::E_DIRECTION_R);
								}
								else if (Enemy.pos.x >= shadow.pos.x)
								{//��
									pos.x = shadow.pos.x + shadow.size.x / 2.0f + Enemy.size.x / 2.0f;
									m_pEnemys[i]->SetDirection(Collision::E_DIRECTION_L);
								}
								break;
							case Collision::E_DIRECTION_U:		//��
								pos.y = shadow.pos.y + shadow.size.y / 2.0f;
								m_pEnemys[i]->ResetMove();
								break;
							case Collision::E_DIRECTION_D:		//��
								pos.y = shadow.pos.y - shadow.size.y / 2.0f - Enemy.size.y;
								m_pEnemys[i]->ResetMove();
								break;
							default:
								continue;
								break;
							}
							m_pEnemys[i]->SetPos(pos);		//�G�l�~�[�ɔ��f
							m_pEnemys[i]->SetStageCollisionDirection(dire, num);		//��������������ێ�
						}
					}
					else if (!init->use)
					{//���݂��Ȃ��i���������鏈���j
						if (Collision::RectAndRect(Enemy, shadow))		//�G�l�~�[�ƃu���b�N���������Ă��邩
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

		//�G�l�~�[�Ɣ��˔�
		for (int j = 0; j < m_pRvsBlock->GetStageNum(); j++)
		{
			if (Collision::RectAndRect(m_pEnemys[i]->GetInfo(), m_pRvsBlock->GetInfo(j)))
			{
				m_pEnemys[i]->SetDirection(m_pRvsBlock->GetDirection(j));
			}
		}

		//�v���C���[�ƃG�l�~�[
		Def::Info player = m_pPlayer->GetInfo();
		float playerT = player.pos.y - player.size.y / 2.0f;
		float playerB = player.pos.y + player.size.y / 2.0f;
		float playerR = player.pos.x - player.size.x / 2.0f;
		float playerL = player.pos.x + player.size.x / 2.0f;
		Def::Info Enemy = m_pEnemys[i]->GetInfo();
		float EnemyT = Enemy.pos.y - Enemy.size.y / 2.0f;
		float EnemyB = Enemy.pos.y + Enemy.size.y / 2.0f;
		float EnemyR = Enemy.pos.x - Enemy.size.x / 2.0f;
		float EnemyL = Enemy.pos.x + Enemy.size.x / 2.0f;
		if (playerT > EnemyB && playerB < EnemyT &&
			playerR > EnemyL && playerL < EnemyR)
		{
			m_pPlayer->SetCollisionEnemy();
			m_pEnemys[i]->SetCollisionPlayer();
		}

		//�G�l�~�[�ƃ��C�g
		Def::Info light = m_pLight->GetInfo();
		float Radius = m_pLight->GetRadius();
		if ((light.pos.x > EnemyL - Radius) &&
			(light.pos.x < EnemyR + Radius) &&
			(light.pos.y > EnemyT - Radius) &&
			(light.pos.y < EnemyB + Radius))
		{
			m_pEnemys[i]->m_life -= m_pLight->GetPower();
			if (m_pEnemys[i]->m_life <= 0.0f)
			{
				m_pEnemys.erase(m_pEnemys.begin() + i);
			}
		}
		

	}
	
	
}
