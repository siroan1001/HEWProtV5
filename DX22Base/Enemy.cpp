#include "Enemy.h"
#include "Collision.h"
#include "ModelList.h"

//using namespace DirectX;



Enemy::Enemy(Collision::Direction dire, XMFLOAT3 pos)
	:m_Ground(true)
	, m_Move{ 0.0f, 0.0f, 0.0f }
	, m_OldInfo{ {2.0f, 1.0f, -0.0f}, {0.3f, 1.0f, 1.0f}, {0.0f, -90.0f, 0.0f} }
	, m_Direction(dire)
	, m_Spead(0.02f)
	, m_IsColPlayer(false)
	, m_life(300.0f)
	, m_use(true)
{
	m_Info = { {pos.x, pos.y, pos.z}, {0.3f, 0.4f, 0.3f}, {0.0f, -90.0f, 0.0f} };
	m_ModelSize.x = m_ModelSize.y = m_ModelSize.z = 0.03f;

	//モデル読み込み
	//m_pModel = new Model;
	//if (!m_pModel->Load("Assets/もこ田めめめ/MokotaMememe.pmx", 0.03f))
	//{
	//	MessageBox(NULL, "モデルの生成に失敗", "エラー", MB_OK);
	//}
	//if (!m_pModel->Load("Assets/Model/enemy01.fbx", 1.0f))
	//{
	//	MessageBox(NULL, "モデルの生成に失敗", "エラー", MB_OK);
	//}

	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_PLAYER);

	//頂点シェーダをモデルに設定
	m_pModel->SetVertexShader(m_pVS);

	//WVP生成
	//m_pWVP = new ConstantBuffer;
	//if (FAILED(m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3)))
	//{
	//	MessageBox(NULL, "pWVP作成失敗", "エラー", MB_OK);
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

void Enemy::Update()
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

	//ジャンプ

	//重力加算
	m_Move.y -= 0.01f;

	//移動量反映
	m_Info.pos.x += m_Move.x;
	m_Info.pos.y += m_Move.y;
	m_Info.pos.z += m_Move.z;

	//落下後処理
	if (m_Info.pos.y < -50.0f)
	{
		m_Info.pos.y = 5.0f;
		m_Move.y = 0.0f;
	}
}

void Enemy::SetPos(XMFLOAT3 pos)
{
	m_Info.pos = pos;
}

void Enemy::InitDirection(int num)
{
	//m_StageDire.
	for (int i = 0; i < num; i++)
	{

		m_StageDire.push_back(Collision::E_DIRECTION_NULL);
	}
}

void Enemy::ResetMove()
{
	m_Move.y = 0.0f;
}

Def::Info Enemy::GetOldInfo()
{
	return m_OldInfo;
}

Collision::Direction Enemy::GetDirection()
{
	return m_Direction;
}

Collision::Direction Enemy::GetStageCollistonDirection(int num)
{
	return m_StageDire[num];
}

void Enemy::SetStageCollisionDirection(Collision::Direction dire, int num)
{
	m_StageDire[num] = dire;
}

void Enemy::SetDirection(Collision::Direction dire)
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

void Enemy::SetCollisionPlayer()
{
	m_IsColPlayer = true;
}

