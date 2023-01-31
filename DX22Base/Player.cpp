#include "Player.h"
#include "Input.h"
#include "Collision.h"
#include "ModelList.h"
#include "controller.h"
#include "Effect.h"

//using namespace DirectX;

bool g_Playerflag = true;

Player::Player(Collision::Direction dire)
	:m_Ground(true)
	,m_Move{0.0f, 0.0f, 0.0f}
	,m_OldInfo{ {-7.6f, 3.25f, 0.0f}, {0.3f, 0.35f, 0.3f}, {0.0f, -90.0f, 0.0f} }
	,m_Direction(dire)
	,m_Spead(PLAYER_MOVE_NORMAL)
	,m_IsColEnemy(false)
{
	m_Info = { {-7.6f, 3.25f, 0.0f}, {0.3f, 0.35f, 0.3f}, {0.0f, -90.0f, 0.0f} };
	m_ModelSize.x = m_ModelSize.y = m_ModelSize.z = 0.01f;

	//���f���ǂݍ���
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_PLAYER);

	//���_�V�F�[�_�����f���ɐݒ�
	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);

	switch (m_Direction)
	{
	case Collision::E_DIRECTION_L:
		m_Info.rot.y = 90.0f;
		break;
	case Collision::E_DIRECTION_R:
		m_Info.rot.y = -90.0f;
		break;
	default:
		break;
	}

	m_Color = XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f);

	m_EndFlag = false;
}

void Player::Update()
{
	// �V�[���Q�[���̏��擾
	SceneGame* pScene = static_cast<SceneGame*>(Game3D::GetScene());
	pScene->GetGameStatus();

	//�ړ��ʃJ�b�g
	m_Move = { 0.0f, m_Move.y, 0.0f };

	//�O�t���[���̃|�W�V������ێ�
	m_OldInfo = m_Info;

	if (!m_EndFlag)
	{

		//�ړ�����
		float x = GetRStick().x;

		if (IsKeyPress('D') || x >= 0.8f)
		{
			m_Direction = Collision::E_DIRECTION_R;
			m_Info.rot.y = -90.0f;
		}

		if (IsKeyPress('A') || x <= -0.8f)
		{
			m_Direction = Collision::E_DIRECTION_L;
			m_Info.rot.y = 90.0f;
		}

		if (m_IsColEnemy)m_Spead = PLAYER_MOVE_NORMAL / 2.0f;
		else m_Spead = PLAYER_MOVE_NORMAL;

		m_IsColEnemy = false;

		//if (pScene->GetGameStatus() == SceneGame::E_GAME_STATUS_GOAL)
		//{
		//	m_Spead = 0.0f;
		//}

		// �����ړ�
		switch (m_Direction)
		{
		case Collision::E_DIRECTION_L:
			m_Move.x += m_Spead;
			break;
		case Collision::E_DIRECTION_R:
			m_Move.x -= m_Spead;
			break;
		default:
			break;
		}




		//�W�����v
		//if (IsKeyTrigger(VK_SPACE))
		//{
		//	m_Move.y += 0.05f;
		//	m_Ground = false;
		//}
		//if (IsButtonTrigger(BUTTON_A))
		//{
		//	m_Move.y += 0.05f;
		//	m_Ground = false;
		//}
	}
	else
	{
		m_ModelSize.x -= 0.0015f;
		m_ModelSize.y -= 0.0015f;
		m_ModelSize.z -= 0.0015f;
		if (m_ModelSize.x < 0.0f)	m_ModelSize.x = 0.0f;
		if (m_ModelSize.y < 0.0f)	m_ModelSize.y = 0.0f;
		if (m_ModelSize.z < 0.0f)	m_ModelSize.z = 0.0f;
	}

	//�d�͉��Z
	m_Move.y -= 0.01f;

	if (IsKeyTrigger('Z'))	
		g_Playerflag ^= 1;

	//�ړ��ʔ��f
	if (g_Playerflag)
	{
		m_Info.pos.x += m_Move.x;
		m_Info.pos.y += m_Move.y;
		m_Info.pos.z += m_Move.z;
	}
	//if (IsKeyTrigger('F'))
	//{
	//	EffectManager::SetEffect(EffectManager::E_EFFECT_KIND_RAIN, m_Info.pos.x, m_Info.pos.y - 0.0f, m_Info.pos.z - 0.0f);
	//}

	//�����㏈��
	if (m_Info.pos.y < -50.0f)
	{
		m_Info.pos.y = 5.0f;
		m_Move.y = 0.0f;
	}

}

void Player::SetPos(XMFLOAT3 pos)
{
	m_Info.pos = pos;
}

void Player::InitDirection(int num)
{
	//m_StageDire.
	for (int i = 0; i < num; i++)
	{
		
		m_StageDire.push_back(Collision::E_DIRECTION_NULL);
	}
}

void Player::ResetMove()
{
	m_Move.y = 0.0f;
}

void Player::Reset()
{
	m_Info = { {-7.6f, 3.25f, 0.0f}, {0.3f, 0.35f, 0.3f}, {0.0f, 90.0f, 0.0f} };
	m_OldInfo = m_Info;
	m_Ground = true;
	m_Move = { 0.0f, 0.0f, 0.0f };
	m_Direction = Collision::E_DIRECTION_L;
	m_IsColEnemy = false;
	m_Color = XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f);
	m_EndFlag = false;
	m_ModelSize.x = m_ModelSize.y = m_ModelSize.z = 0.03f;
}

Def::Info Player::GetOldInfo()
{
	return m_OldInfo;
}

Collision::Direction Player::GetDirection()
{
	return m_Direction;
}

Collision::Direction Player::GetStageCollistonDirection(int num)
{
	return m_StageDire[num];
}

bool Player::GetEndFlag()
{
	return m_EndFlag;
}

void Player::SetStageCollisionDirection(Collision::Direction dire, int num)
{
	m_StageDire[num] = dire;
}

void Player::SetDirection(Collision::Direction dire)
{
	m_Direction = dire;

	switch (m_Direction)
	{
	case Collision::E_DIRECTION_L:
		m_Info.rot.y =  90.0f;
		break;
	case Collision::E_DIRECTION_R:
		m_Info.rot.y = -90.0f;
		break;
	default:
		break;
	}
}

void Player::SetCollisionEnemy()
{
	m_IsColEnemy = true;
}

void Player::SetEndFlag(bool flag)
{
	m_EndFlag = flag;
}

