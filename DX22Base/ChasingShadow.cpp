#include "ChasingShadow.h"
#include "ModelList.h"

//ChasingShadow::ChasingShadow()
//	:m_Info{ {-10.0f, 5.0f, 0.0f}, {2.0f, 0.5f, 2.0f}, {XMConvertToRadians(90.0f), 0.0f, 0.0f} }
//	, m_PlDirection(Collision::E_DIRECTION_L)
//{
//}
//
//ChasingShadow::~ChasingShadow()
//{
//}
//
//void ChasingShadow::Update()
//{
//	const int cn_MaxFlame = 300;
//	m_PosLog.push_back(m_pPlayer->GetInfo().pos);
//
//	if (m_PosLog.size() >= cn_MaxFlame)
//	{
//		m_Info.pos = *m_PosLog.begin();
//		m_PosLog.pop_front();
//	}
//	/*const float SHADOW_MOVE = 0.01f;
//	const float LIMIT = 3.0f;
//
//	Collision::Direction PlOldDirection = m_PlDirection;
//	m_PlDirection = m_pPlayer->GetDirection();
//
//	XMFLOAT3 PlayerPos = m_pPlayer->GetInfo().pos;
//
//	if (PlOldDirection != m_PlDirection)
//	{
//		switch (m_PlDirection)
//		{
//		case Collision::E_DIRECTION_NULL:
//			break;
//		case Collision::E_DIRECTION_L:
//			m_Info.pos.x = PlayerPos.x - LIMIT;
//			m_Info.pos.y = PlayerPos.y;
//			break;
//		case Collision::E_DIRECTION_R:
//			m_Info.pos.x = PlayerPos.x + LIMIT;
//			m_Info.pos.y = PlayerPos.y;
//			break;
//		case Collision::E_DIRECTION_U:
//			break;
//		case Collision::E_DIRECTION_D:
//			break;
//		case Collision::E_DIRECTION_MAX:
//			break;
//		default:
//			break;
//		}
//	}
//
//
//
//
//	if (PlayerPos.x > m_Info.pos.x)
//	{
//		m_Info.pos.x += SHADOW_MOVE;
//	}
//	if (PlayerPos.x < m_Info.pos.x)
//	{
//		m_Info.pos.x -= SHADOW_MOVE;
//	}
//	if (PlayerPos.y > m_Info.pos.y)
//	{
//		m_Info.pos.y += SHADOW_MOVE * 0.5f;
//	}
//	if (PlayerPos.y < m_Info.pos.y)
//	{
//		m_Info.pos.y -= SHADOW_MOVE * 0.5f;
//	}
//	if (m_Info.pos.x < PlayerPos.x - LIMIT)
//	{
//		m_Info.pos.x  = PlayerPos.x - LIMIT;
//	}
//	if (m_Info.pos.x > PlayerPos.x + LIMIT)
//	{
//		m_Info.pos.x = PlayerPos.x + LIMIT;
//	}*/
//}
//
//void ChasingShadow::Draw()
//{
//	SetGeometoryTranslate(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
//	SetGeometoryScaling(m_Info.size.x, m_Info.size.y, m_Info.size.z);
//	SetGeometoryRotation(m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
//	DrawCylinder();
//}
//
//void ChasingShadow::SetPlayer(Player * pPlayer)
//{
//	m_pPlayer = pPlayer;
//}
//
//Def::Info ChasingShadow::GetInfo()
//{
//	return m_Info;
//}
//
//float ChasingShadow::GetRadius()
//{
//	return GetCylinderRadius() * m_Info.size.x;
//}

ChasingShadow::ChasingShadow()
	:m_PlDirection(Collision::E_DIRECTION_L)
{
	m_ModelSize.x = m_ModelSize.y = m_ModelSize.z = 1.0f;
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_GHOST);

	//頂点シェーダをモデルに設定
	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);

	m_Info = { {-10.0f, 5.0f, 0.0f}, {2.0f, 0.5f, 2.0f}, {0.0f, 0.0f, 0.0f} };


}

void ChasingShadow::Update()
{
	const int cn_MaxFlame = 150;
	m_PosLog.push_back(m_pPlayer->GetInfo().pos);

	if (m_PosLog.size() >= cn_MaxFlame)
	{
		m_Info.pos = *m_PosLog.begin();
		m_Info.pos.y += 0.9f;

		m_PosLog.pop_front();
	}
}

void ChasingShadow::SetPlayer(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}

float ChasingShadow::GetRadius()
{
	return 1.0f;
}
