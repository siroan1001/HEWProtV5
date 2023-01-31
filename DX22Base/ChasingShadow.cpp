#include "ChasingShadow.h"
#include "ModelList.h"

const float DirRight = -180.0f;
const float DirLeft = 0.0f;
const float GraduallyRight = -1.0f;
const float GraduallyLeft = 1.0f;
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
		float PlayerX = m_pPlayer->GetInfo().pos.x;
		float PlayerY = m_pPlayer->GetInfo().pos.y;
		float DistanceX = PlayerX - m_Info.pos.x;
		float DistanceY = PlayerY - m_Info.pos.y;
		float MoveX = DistanceX / 250.0f;
		float MoveY = DistanceY / 250.0f;
		m_Info.pos.x += MoveX;
		m_Info.pos.y += MoveY;
		if (m_Info.pos.y <= 4.0f)
		{
			m_Info.pos.y = 4.0f;
		}
		/*if (m_PosLog.size() >= cn_MaxFlame)
		{
			m_Info.pos = *m_PosLog.begin();
			m_Info.pos.y += 0.9f;

			m_PosLog.pop_front();
		}*/
	}
	else
	{
		if (SceneGame::GetGameStatus() == SceneGame::E_GAME_STATUS_GOAL)
		{
			m_Color.w -= 0.02f;
			if (m_Color.w <= 0.0f)
			{
				m_Color.w = 0.0f;
			}
		}
	}
}
void ChasingShadow::InvDraw()
{
	if (!m_pCamera)	return;		//カメラが設定されてなければ処理しない
	//--- プレイヤーがより左にいるとき
	if (m_pPlayer->GetInfo().pos.x >= m_Info.pos.x)
	{
		m_Info.rot.y += GraduallyLeft;
		if (m_Info.rot.y >= DirLeft)
		{
			m_Info.rot.y = DirLeft;
		}
	}
	//--- プレイヤーがより右にいるとき
	if (m_pPlayer->GetInfo().pos.x < m_Info.pos.x)
	{
		m_Info.rot.y += GraduallyRight;
		if (m_Info.rot.y <= DirRight)
		{
			m_Info.rot.y = DirRight;
		}
	}
	XMFLOAT3 ConvertRot = { XMConvertToRadians(m_Info.rot.x), XMConvertToRadians(m_Info.rot.y), XMConvertToRadians(m_Info.rot.z) };
	XMFLOAT4X4 mat[3];
	XMMATRIX temp = XMMatrixScaling(m_ModelSize.x, m_ModelSize.y, m_ModelSize.z) * XMMatrixRotationX(ConvertRot.x) * XMMatrixRotationY(ConvertRot.y) * XMMatrixRotationZ(ConvertRot.z)	* XMMatrixTranslation(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	XMStoreFloat4x4(&mat[0], XMMatrixTranspose(temp));	//ワールド行列
	mat[1] = m_pCamera->GetViewMatrix();		//ビュー行列
	mat[2] = m_pCamera->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV);	//プロジェクション行列
	//m_ObjColor.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pWVP->Write(mat);		//WVP設定
	m_pWVP->BindVS(0);
	m_ObjLight = GetLig();
	m_pBufLight->Write(&m_ObjLight);
	m_pBufLight->BindPS(0);
	m_pObjColor->Write(&m_ObjColor);
	m_pObjColor->BindPS(1);
	m_pModel->Draw();
}
void ChasingShadow::Reset()
{
	m_Info = { {-10.0f, 5.0f, 0.0f}, {1.5f, 1.5f, 0.5f}, {0.0f, 0.0f, 0.0f} };
	m_PlDirection = Collision::E_DIRECTION_L;
	m_PosLog.clear();
	m_EndFlag = false;
	m_Color = XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f);
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
