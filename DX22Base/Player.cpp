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
	m_ModelSize.x = m_ModelSize.y = m_ModelSize.z = 0.03f;

	//モデル読み込み
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_PLAYER);

	//頂点シェーダをモデルに設定
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
}

void Player::Update()
{
	// シーンゲームの情報取得
	SceneGame* pScene = static_cast<SceneGame*>(Game3D::GetScene());
	pScene->GetGameStatus();

	//移動量カット
	m_Move = { 0.0f, m_Move.y, 0.0f };

	//前フレームのポジションを保持
	m_OldInfo = m_Info;

	//移動処理
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

	
	// Rキーでリスポーンする (デバッグ用
#ifdef DEBUG
	if (IsKeyPress('R')) m_Info.pos = { 2.0f, 1.0f, -0.0f };
#endif // DEBUG

	
	//ジャンプ
	if (IsKeyTrigger(VK_SPACE))
	{
		m_Move.y += 0.07f;
		m_Ground = false;
	}
	if (IsButtonTrigger(BUTTON_A))
	{
		m_Move.y += 0.07f;
		m_Ground = false;
	}

	//重力加算
	m_Move.y -= 0.01f;

	if (IsKeyTrigger('Z'))	
		g_Playerflag ^= 1;

	//移動量反映
	if (g_Playerflag)
	{
		m_Info.pos.x += m_Move.x;
		m_Info.pos.y += m_Move.y;
		m_Info.pos.z += m_Move.z;
	}
	if (IsKeyTrigger('F'))
	{
		EffectManager::SetEffect(EffectManager::E_EFFECT_KIND_RAIN, m_Info.pos.x, m_Info.pos.y - 0.0f, m_Info.pos.z - 0.0f);
	}

	//落下後処理
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

