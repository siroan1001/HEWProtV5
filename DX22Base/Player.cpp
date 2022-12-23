#include "Player.h"
#include "Input.h"
#include "Collision.h"

//using namespace DirectX;

Player::Player(Collision::Direction dire)
	//:m_Pos{2.0f, -1.0f, 0.0f}
	//,m_Rot{0.0f, -90.0f, 0.0f}
	:m_Ground(true)
	,m_Move{0.0f, 0.0f, 0.0f}
	,m_Info{{-7.6f, 3.25f, 0.0f}, {0.3f, 0.646f, 0.3f}, {0.0f, -90.0f, 0.0f}}
	,m_OldInfo{{2.0f, 1.0f, -0.0f}, {0.3f, 1.0f, 1.0f}, {0.0f, -90.0f, 0.0f}}
	,m_Direction(dire)
{
	//���f���ǂݍ���
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/�����c�߂߂�/MokotaMememe.pmx", 0.03f))
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

Player::~Player()
{
	delete m_pWVP;
	delete m_pVS;
	delete m_pModel;
}

void Player::Update()
{
	//�ړ��ʃJ�b�g
	m_Move = { 0.0f, m_Move.y, 0.0f };

	//�O�t���[���̃|�W�V������ێ�
	m_OldInfo = m_Info;

	//�ړ�����
	if (IsKeyPress('D'))
	{
		//m_Move.x -= 0.1f;
		m_Direction = Collision::E_DIRECTION_R;
		m_Info.rot.y = -90.0f;
	}
		
	if (IsKeyPress('A'))
	{
		//m_Move.x += 0.1f;
		m_Direction = Collision::E_DIRECTION_L;
		m_Info.rot.y = 90.0f;
	}
	// �����ړ�
	switch (m_Direction)
	{
	case Collision::E_DIRECTION_L:
		m_Move.x += 0.03f;
		break;
	case Collision::E_DIRECTION_R:
		m_Move.x -= 0.03f;
		break;
	default:
		break;
	}

	
	// R�L�[�Ń��X�|�[������ (�f�o�b�O�p
#ifdef DEBUG
	if (IsKeyPress('R')) m_Info.pos = { 2.0f, 1.0f, -0.0f };
#endif // DEBUG

	
	//�W�����v
	if (IsKeyTrigger(VK_SPACE))
	{
		m_Move.y += 0.10f;
		m_Ground = false;
	}

	//�d�͉��Z
	m_Move.y -= 0.01f;

	//�ړ��ʔ��f
	m_Info.pos.x += m_Move.x;
	m_Info.pos.y += m_Move.y;
	m_Info.pos.z += m_Move.z;

	//�����㏈��
	if (m_Info.pos.y < -50.0f)
	{
		m_Info.pos.y = 5.0f;
		m_Move.y = 0.0f;
	}
}

void Player::Draw()
{
	if (!m_pCamera)	return;		//�J�������ݒ肳��ĂȂ���Ώ������Ȃ�
	XMFLOAT3 ConvertRot = { XMConvertToRadians(m_Info.rot.x), XMConvertToRadians(m_Info.rot.y), XMConvertToRadians(m_Info.rot.z) };
	XMFLOAT4X4 mat[3];
	XMMATRIX temp =	XMMatrixRotationX(ConvertRot.x) * XMMatrixRotationY(ConvertRot.y) * XMMatrixRotationZ(ConvertRot.z) 
		* XMMatrixTranslation(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
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

Object::Info Player::GetInfo()
{
	return m_Info;
}

Object::Info Player::GetOldInfo()
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

