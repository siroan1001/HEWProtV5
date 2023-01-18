#include "EnemyDefault.h"
#include "ModelList.h"

EnemyDefault::EnemyDefault(Collision::Direction dire, XMFLOAT3 pos)
	:m_Ground(true)
	,m_Move{0.0f, 0.0f, 0.0f}
	,m_Spead(0.02f)
{
	m_Info = { {pos.x, pos.y, pos.z}, {0.3f, 0.4f, 0.3f}, {0.0f, -90.0f, 0.0f} };
	m_OldInfo = m_Info;
	m_ModelSize.x = m_ModelSize.y = m_ModelSize.z = 0.03f;

	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_PLAYER);

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

	if (m_IsColPlayer) m_Spead = 0.015f;
	else m_Spead = 0.02f;

	m_IsColPlayer = false;

	// 自動移動
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