#include "EnemyDefault.h"
#include "ModelList.h"
#include "Player.h"
#include "Input.h"

EnemyDefault::EnemyDefault(Collision::Direction dire, XMFLOAT3 pos)
	:m_Ground(true)
	,m_Move{0.0f, 0.0f, 0.0f}
	,m_Spead(0.001f)
{
	m_Info = { {-5.6f, 3.75f, 0.0f}, { 0.3f, 0.4f, 0.3f }, { 0.0f, -90.0f, 0.0f } };
	m_OldInfo = m_Info;
	m_ModelSize.x = m_ModelSize.y = m_ModelSize.z = 0.2f;

	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_ENEMY);
	//m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_ENEMY);

	m_pModel->SetVertexShader(m_pVS);

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

	m_IsCollision = true;
}

void EnemyDefault::Update()
{
	//移動量カット
	m_Move = { 0.0f, m_Move.y, 0.0f };

	//前フレームのポジションを保持
	m_OldInfo = m_Info;

	if (m_IsColPlayer) m_Spead = 0.0005f;
	else m_Spead = PLAYER_MOVE_NORMAL;

	m_IsColPlayer = false;

	//if (IsKeyPress('N'))
	//{
	//	m_Info.rot.y += 1.0f;
	//}


	// 自動移動
	//switch (m_Direction)
	//{
	//case Collision::E_DIRECTION_L:
	//	m_Move.x += m_Spead;
	//	break;
	//case Collision::E_DIRECTION_R:
	//	m_Move.x -= m_Spead;
	//	break;
	//default:
	//	break;
	//}

	//重力加算
	m_Move.y -= 0.01f;

	//移動量反映
	m_Info.pos.x += m_Move.x;
	m_Info.pos.y += m_Move.y;
	m_Info.pos.z += m_Move.z;
}

Def::Info EnemyDefault::GetOldInfo()
{
	return m_OldInfo;
}

Collision::Direction EnemyDefault::GetStageCollistonDirection(int num)
{
	return m_StageDire[num];
}

void EnemyDefault::SetStageCollisionDirection(Collision::Direction dire, int num)
{
	m_StageDire[num] = dire;
}

void EnemyDefault::SetDirection(Collision::Direction dire)
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

void EnemyDefault::SetPos(XMFLOAT3 pos)
{
	m_Info.pos = pos;
}

void EnemyDefault::InitDirectin(int num)
{
	for (int i = 0; i < num; i++)
	{

		m_StageDire.push_back(Collision::E_DIRECTION_NULL);
	}
}

void EnemyDefault::ResetMove()
{
	m_Move.y = 0.0f;
}