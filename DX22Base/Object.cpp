#include "Object.h"

VertexShader* Object::m_pVS = NULL;
ConstantBuffer* Object::m_pWVP = NULL;

Object::Object()
	:m_pModel(NULL)
	,m_Info{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}
	,m_pCamera(NULL)
{
}

Object::~Object()
{
	if (m_pModel)	delete m_pModel;
	if (m_pCamera)	delete m_pCamera;
}

void Object::Init()
{
	m_pVS = new VertexShader;
	if (FAILED(m_pVS->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(NULL, "�v���C���[��VS�ǂݍ��ݎ��s", "�G���[", MB_OK);
	}

	m_pWVP = new ConstantBuffer;
	if (FAILED(m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3)))
	{
		MessageBox(NULL, "pWVP�쐬���s", "�G���[", MB_OK);
	}

}

void Object::Uninit()
{
	delete m_pWVP;
	delete m_pVS;
}

void Object::Draw()
{
	if (!m_pCamera)	return;		//�J�������ݒ肳��ĂȂ���Ώ������Ȃ�
	XMFLOAT3 ConvertRot = { XMConvertToRadians(m_Info.rot.x), XMConvertToRadians(m_Info.rot.y), XMConvertToRadians(m_Info.rot.z) };
	XMFLOAT4X4 mat[3];
	XMMATRIX temp = XMMatrixRotationX(ConvertRot.x) * XMMatrixRotationY(ConvertRot.y) * XMMatrixRotationZ(ConvertRot.z)
		* XMMatrixTranslation(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	XMStoreFloat4x4(&mat[0], XMMatrixTranspose(temp));	//���[���h�s��
	mat[1] = m_pCamera->GetViewMatrix();		//�r���[�s��
	mat[2] = m_pCamera->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV);	//�v���W�F�N�V�����s��
	m_pWVP->Write(mat);		//WVP�ݒ�
	m_pWVP->BindVS(0);
	m_pModel->Draw();
}

Object::Info Object::GetInfo()
{
	return m_Info;
}

void Object::SetCamera(CameraBase* cam)
{
	m_pCamera = cam;
}
