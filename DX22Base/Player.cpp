#include "Player.h"
#include "Input.h"

//using namespace DirectX;

Player::Player()
	:m_Pos{2.0f, -1.0f, 0.0f}
	,m_Rot{0.0f, -90.0f, 0.0f}
	,m_Ground(true)
	,m_Move{0.0f, 0.0f, 0.0f}
{
	//���f���ǂݍ���
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/�����c�߂߂�/MokotaMememe.pmx", 0.05f))
	{
		MessageBox(NULL, "���f���̐����Ɏ��s", "�G���[", MB_OK);
	}

	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader;
	if (FAILED(m_pVS->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(NULL, "�v���C���[��VS�ǂݍ��ݎ��s", "�G���[", MB_OK);
	}

	//���_�V�F�[�_�����f���ɐݒ�
	m_pModel->SetVertexShader(m_pVS);

	//WVP����
	m_pWVP = new ConstantBuffer;
	if (FAILED(m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3)))
	{
		MessageBox(NULL, "pWVP�쐬���s", "�G���[", MB_OK);
	}
}

Player::~Player()
{
	delete m_pWVP;
	delete m_pVS;
	delete m_pModel;
}

void Player::Update()
{
	//�萔��`
	const float PLAYER_MOVE = 0.1f;

	//���[�J���ϐ��錾
	XMFLOAT3 CamPos = m_pCamera->GetPos();		//�J����Pos
	XMFLOAT3 CamLook = m_pCamera->GetLook();	//�J����Look
	CamPos.y = CamLook.y = 0.0f;
	XMVECTOR vCamPos = XMLoadFloat3(&CamPos);	//�J����Pos��Vector�ɒu��������
	XMVECTOR vCamLook = XMLoadFloat3(&CamLook);	//�J����Look��Vector�ɒu��������

	XMVECTOR vFroat;		//�J�����̐��ʕ����̃x�N�g��
	vFroat = vCamLook - vCamPos;
	vFroat = XMVector3Normalize(vFroat);		//���K��

	XMMATRIX matRotSide = XMMatrixRotationY(XMConvertToRadians(90.0f));		//Y����90�x�i�E�����j�ɉ�]�����]�s��𐶐�
	matRotSide = XMMatrixTranspose(matRotSide);
	XMVECTOR vSide = XMVector3TransformCoord(vFroat, matRotSide);	//���ʕ����̃x�N�g����90�x��]������
																	//�^���̃x�N�g�����Ƃ�

	//XMMATRIX matRotUp = XMMatrixRotationX(XMConvertToRadians(90.0f));

	//�ړ��ʃJ�b�g
	m_Move = { 0.0f, m_Move.y, 0.0f };

	//�ړ�����
	XMVECTOR vMove = XMVectorZero();	//������
	//if (IsKeyPress('W'))	vMove += vFroat;	//�O
	//if (IsKeyPress('S'))	vMove -= vFroat;	//���
	//if (IsKeyPress('A'))	
	//	vMove -= vSide;		//��
	//if (IsKeyPress('D'))	vMove += vSide;		//�E
	vMove = XMVectorScale(vMove, 0.2f);		//�萔�{�����Ĉړ��̑傫����K�؂ɂ���

	XMFLOAT3 move;	//Pos�ɔ��f�����邽�߂̕ϐ�
	XMStoreFloat3(&move, vMove);	//XMVECTOR��XMFLOAT3�ɒu��������

	if (IsKeyPress('D'))	m_Move.x -= 0.1f;
	if (IsKeyPress('A'))	m_Move.x += 0.1f;
/*
	m_Move.x += move.x;
	m_Move.y += move.y;
	m_Move.z += move.z;
*/
	
	//�W�����v
	if (IsKeyTrigger(VK_SPACE))
	{
		m_Move.y += 0.5f;
		m_Ground = false;
	}

	if (!m_Ground)
	{
		m_Move.y -= 0.03f;
	}

	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	m_Pos.z += m_Move.z;

	if (m_Pos.y < -50.0f)
	{
		m_Pos.y = 5.0f;
		m_Move.y = 0.0f;
	}
}

void Player::Draw()
{
	if (!m_pCamera)	return;		//�J�������ݒ肳��ĂȂ���Ώ������Ȃ�
	XMFLOAT3 ConvertRot = { XMConvertToRadians(m_Rot.x), XMConvertToRadians(m_Rot.y), XMConvertToRadians(m_Rot.z) };
	XMFLOAT4X4 mat[3];
	XMMATRIX temp =	XMMatrixRotationX(ConvertRot.x) * XMMatrixRotationY(ConvertRot.y) * XMMatrixRotationZ(ConvertRot.z) * XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	XMStoreFloat4x4(&mat[0], XMMatrixTranspose(temp));	//���[���h�s��
	mat[1] = m_pCamera->GetViewMatrix();		//�r���[�s��
	mat[2] = m_pCamera->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV);	//�v���W�F�N�V�����s��
	m_pWVP->Write(mat);		//WVP�ݒ�
	m_pWVP->BindVS(0);
	m_pModel->Draw();
}

void Player::SetCamera(CameraBase* pCamera)
{
	m_pCamera = pCamera;
}

XMFLOAT3 Player::GetPos()
{
	return m_Pos;
}
