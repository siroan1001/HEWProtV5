#include "BobbingEnemy.h"
#include "Collision.h"

//using namespace DirectX;



BobbingEnemy::BobbingEnemy(Collision::Direction dire, XMFLOAT3 pos, XMFLOAT3 point, int flame)
	: m_Move{ 0.0f, 0.0f, 0.0f }
	, m_OldInfo{ {2.0f, 1.0f, -0.0f}, {0.3f, 1.0f, 1.0f}, {0.0f, -90.0f, 0.0f} }
	, m_Direction(dire)
	, m_IsColPlayer(false)
	, m_life(300.0f)
	, m_use(true)
	, m_flame(0)
{
	m_Info = { {pos.x, pos.y, pos.z}, {0.3f, 0.646f, 0.3f}, {0.0f, -90.0f, 0.0f} };

	m_Start = { pos.x,pos.y,pos.z };        //�J�n�n�_
	m_Point = { point.x, point.y, point.z };//�܂�Ԃ��n�_
	m_maxflame = flame;
	//���f���ǂݍ���
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/�����c�߂߂�/MokotaMememe.pmx", 0.03f))
	{
		MessageBox(NULL, "���f���̐����Ɏ��s", "�G���[", MB_OK);
	}
	//if (!m_pModel->Load("Assets/Model/enemy01.fbx", 1.0f))
	//{
	//	MessageBox(NULL, "���f���̐����Ɏ��s", "�G���[", MB_OK);
	//}

	//���_�V�F�[�_�����f���ɐݒ�
	m_pModel->SetVertexShader(m_pVS);

	//WVP����
	//m_pWVP = new ConstantBuffer;
	//if (FAILED(m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3)))
	//{
	//	MessageBox(NULL, "pWVP�쐬���s", "�G���[", MB_OK);
	//}

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
}

void BobbingEnemy::Update()
{
	
	//�ړ��ʃJ�b�g

	//�O�t���[���̃|�W�V������ێ�
	m_OldInfo = m_Info;

	m_IsColPlayer = false;


	// �����ړ�
	switch (m_Direction)
	{
	case Collision::E_DIRECTION_L:
		m_Info.pos.x = m_Start.x + (m_Point.x - m_Start.x) * m_flame / m_maxflame;
		m_Info.pos.y = m_Start.y + (m_Point.y - m_Start.y) * m_flame / m_maxflame;
		break;
	case Collision::E_DIRECTION_R:
		m_Info.pos.x = m_Start.x + (m_Point.x - m_Start.x) * (m_maxflame - m_flame) / m_maxflame;
		m_Info.pos.y = m_Start.y + (m_Point.y - m_Start.y) * (m_maxflame - m_flame) / m_maxflame;
		break;
	default:
		break;
	}


	//�W�����v

	//�d�͉��Z


	//�ړ��ʔ��f

	//�����㏈��

	m_flame++;
	if (m_flame > m_maxflame)
	{
		m_flame = 0;
		switch (m_Direction)
		{
		case Collision::E_DIRECTION_L:
			SetDirection(Collision::E_DIRECTION_R);
			break;
		case Collision::E_DIRECTION_R:
			SetDirection(Collision::E_DIRECTION_L);
			break;
		default:
			break;
		}
	}
}


//void BobbingEnemy::InitDirection(int num)
//{
//	//m_StageDire.
//	for (int i = 0; i < num; i++)
//	{
//
//		m_StageDire.push_back(Collision::E_DIRECTION_NULL);
//	}
//}

Def::Info BobbingEnemy::GetOldInfo()
{
	return m_OldInfo;
}

Collision::Direction BobbingEnemy::GetDirection()
{
	return m_Direction;
}

//Collision::Direction BobbingEnemy::GetStageCollistonDirection(int num)
//{
//	return m_StageDire[num];
//}

//void BobbingEnemy::SetStageCollisionDirection(Collision::Direction dire, int num)
//{
//	m_StageDire[num] = dire;
//}

void BobbingEnemy::SetDirection(Collision::Direction dire)
{
	m_Direction = dire;

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
}

void BobbingEnemy::SetCollisionPlayer()
{
	m_IsColPlayer = true;
}

