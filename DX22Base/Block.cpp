#include "Block.h"

Block::Block():
	m_Info{ {-7.6f, 3.25f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f} }
{
	// モデルの生成処理
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/box.fbx", 1.0f)) 
	{
		MessageBox(nullptr, "モデルエラー", "Error", MB_OK);
	}

	// シェーダー読み込み
	m_pVS = new VertexShader;
	if (FAILED(m_pVS->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);

	// 定数バッファ作成
	m_pWVP = new ConstantBuffer();
	m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3);

}
Block::~Block()
{
	delete m_pWVP;
	delete m_pVS;
	delete m_pModel;
}
void Block::Update()
{

}
void Block::Draw()
{
	if (!m_pCamera) { return; }
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	DirectX::XMMATRIX R =
		DirectX::XMMatrixRotationX(m_Info.rot.x) *
		DirectX::XMMatrixRotationY(m_Info.rot.y) *
		DirectX::XMMatrixRotationZ(m_Info.rot.z);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_Info.size.x, m_Info.size.y, m_Info.size.z);

	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(S * R * T));

	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV);

	m_pWVP->Write(mat);
	m_pWVP->BindVS(0);
	m_pModel->Draw();

}

void Block::SetCamera(CameraBase* pCamera)
{
	m_pCamera = pCamera;
}
