#include "Player.h"
#include "Input.h"
#include "Collision.h"

//using namespace DirectX;

Player::Player(Collision::Direction dire)
	:m_Ground(true)
	,m_Move{0.0f, 0.0f, 0.0f}
	,m_OldInfo{{2.0f, 1.0f, -0.0f}, {0.3f, 1.0f, 1.0f}, {0.0f, -90.0f, 0.0f}}
	,m_Direction(dire)
	,m_Spead(0.03f)
{
	m_Info = { {-7.6f, 3.25f, 0.0f}, {0.3f, 0.646f, 0.3f}, {0.0f, -90.0f, 0.0f} };

	//モデル読み込み
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/もこ田めめめ/MokotaMememe.pmx", 0.03f))
	{
		MessageBox(NULL, "モデルの生成に失敗", "エラー", MB_OK);
	}

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

void Player::Update()
{
	//移動量カット
	m_Move = { 0.0f, m_Move.y, 0.0f };

	//前フレームのポジションを保持
	m_OldInfo = m_Info;

	//移動処理
	if (IsKeyPress('D'))
	{
		m_Direction = Collision::E_DIRECTION_R;
		m_Info.rot.y = -90.0f;
	}
		
	if (IsKeyPress('A'))
	{
		m_Direction = Collision::E_DIRECTION_L;
		m_Info.rot.y = 90.0f;
	}
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
	if (IsKeyTrigger(VK_SPACE) && m_Ground == true)
	{
		m_Move.y += 0.10f;
		m_Ground = false;
	}
	//ジャンプ中は横の移動速度を軽減
	if (m_Ground == false)
	{
		m_Move.x *= 0.5f;
	}
	//ライトに当たっているときは移動速度を軽減
	if (m_bLight == true)
	{
		m_Move.x *= 0.5f;
	}

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
	
	m_bLight = false;
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

void Player::JumpReset()
{
	m_Ground = true;
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

void Player::LightCollision()
{
	m_bLight = true;
}

