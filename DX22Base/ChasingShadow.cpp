#include "ChasingShadow.h"
#include "ModelList.h"

ChasingShadow::ChasingShadow()
	:m_PlDirection(Collision::E_DIRECTION_L)
{
	m_ModelSize.x = m_ModelSize.y = m_ModelSize.z = 1.0f;
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_GHOST);

	//頂点シェーダをモデルに設定
	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);

	m_Info = { {-10.0f, 5.0f, 0.0f}, {1.5f, 1.5f, 0.5f}, {0.0f, 0.0f, 0.0f} };

	m_EndFlag = false;

	m_Color = XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f);
}

void ChasingShadow::Update()
{
	const int cn_MaxFlame = 150;
	m_PosLog.push_back(m_pPlayer->GetInfo().pos);

	if (!m_EndFlag)
	{
		if (m_PosLog.size() >= cn_MaxFlame)
		{
			m_Info.pos = *m_PosLog.begin();
			m_Info.pos.y += 0.9f;

			m_PosLog.pop_front();
		}
	}
	else
	{
		m_Color.w -= 0.02f;
		if (m_Color.w <= 0.0f)
		{
			m_Color.w = 0.0f;
		}
	}
}

void ChasingShadow::Reset()
{
	m_Info = { {-10.0f, 5.0f, 0.0f}, {1.5f, 1.5f, 0.5f}, {0.0f, 0.0f, 0.0f} };
	m_PlDirection = Collision::E_DIRECTION_L;
	m_PosLog.clear();
}

bool ChasingShadow::GetEndFlag()
{
	return m_EndFlag;
}

void ChasingShadow::SetPlayer(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}

void ChasingShadow::SetPos(XMFLOAT3 pos)
{
	m_Info.pos = pos;
}

void ChasingShadow::SetEndFlag(bool flag)
{
	m_EndFlag = flag;
}

float ChasingShadow::GetRadius()
{
	return 1.0f;
}
