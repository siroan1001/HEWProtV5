#include "Object.h"
#include "Geometory.h"

VertexShader* Object::m_pVS = NULL;
ConstantBuffer* Object::m_pWVP = NULL;
PixelShader* Object::m_pPS = NULL;
ConstantBuffer* Object::m_pBufLight = NULL;
Lig* Object::m_pObjLight = NULL;
Lig::Light Object::m_ObjLight;
ConstantBuffer* Object::m_pObjColor = NULL;
Object::ObjCol Object::m_ObjColor;

Object::Object()
	:m_pModel(NULL)
	,m_Info{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}
	,m_pCamera(NULL)
	,m_ModelSize{1.0f, 1.0f, 1.0f}
{
}

Object::~Object()
{
	//if (m_pModel)	delete m_pModel;
	//if (m_pCamera)	delete m_pCamera;
}

void Object::Init()
{
	m_pVS = new VertexShader;
	if (FAILED(m_pVS->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(NULL, "プレイヤーのVS読み込み失敗", "エラー", MB_OK);
	}

	m_pWVP = new ConstantBuffer;
	if (FAILED(m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3)))
	{
		MessageBox(NULL, "pWVP作成失敗", "エラー", MB_OK);
	}

	m_pPS = new PixelShader;
	if (FAILED(m_pPS->Load("Assets/Shader/ModelPS.cso")))
	{
		MessageBox(nullptr, "ModelPS.cso", "Error", MB_OK);
	}

	m_pBufLight = new ConstantBuffer();
	if (FAILED(m_pBufLight->Create(sizeof(Lig::Light))))
	{
		MessageBox(NULL, "m_pLight", "Error", MB_OK);
	}
	m_ObjLight.eyePos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pObjLight = new Lig;
	m_pObjLight->InitSpLig(m_ObjLight);
	m_pObjLight->InitAmLig(m_ObjLight);

	m_pObjColor = new ConstantBuffer();
	if (FAILED(m_pObjColor->Create(sizeof(Object::ObjCol))))
	{
		MessageBox(NULL, "m_pObjColor", "Error", MB_OK);
	}
	m_ObjColor.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}

void Object::Uninit()
{
	delete m_pObjLight;
	delete m_pBufLight;
	delete m_pPS;
	delete m_pWVP;
	delete m_pVS;
}

void Object::Draw()
{
	if (!m_pCamera)	return;		//カメラが設定されてなければ処理しない
	XMFLOAT3 ConvertRot = { XMConvertToRadians(m_Info.rot.x), XMConvertToRadians(m_Info.rot.y), XMConvertToRadians(m_Info.rot.z) };
	XMFLOAT4X4 mat[3];
	XMMATRIX temp = XMMatrixScaling(m_ModelSize.x, m_ModelSize.y, m_ModelSize.z) * XMMatrixRotationX(ConvertRot.x) * XMMatrixRotationY(ConvertRot.y) * XMMatrixRotationZ(ConvertRot.z)	* XMMatrixTranslation(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	XMStoreFloat4x4(&mat[0], XMMatrixTranspose(temp));	//ワールド行列
	mat[1] = m_pCamera->GetViewMatrix();		//ビュー行列
	mat[2] = m_pCamera->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV);	//プロジェクション行列
	m_pWVP->Write(mat);		//WVP設定
	m_pWVP->BindVS(0);
	m_ObjLight = GetLig();
	m_pBufLight->Write(&m_ObjLight);
	m_pBufLight->BindPS(0);
	m_pObjColor->Write(&m_ObjColor);
	m_pObjColor->BindPS(1);
	m_pModel->Draw();
}

void Object::SetObjColor(XMFLOAT4 color)
{
	m_ObjColor.color = color;
}

Def::Info Object::GetInfo()
{
	return m_Info;
}

void Object::SetCamera(CameraBase* cam)
{
	m_pCamera = cam;
}
