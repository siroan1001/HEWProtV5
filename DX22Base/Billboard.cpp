#include "Billboard.h"
#include "SceneGame.h"
#include "Sprite.h"
#include "Game3D.h"


Billboard::Billboard()
	:m_Info{ {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} }
	,m_pTex(NULL)
{
}

Billboard::~Billboard()
{
	if (!m_pTex)	return;

	m_pTex->Release();
}



void Billboard::Draw()
{
	CameraBase* cam = Game3D::GetCamera();
	Sprite::SetView(cam->GetViewMatrix());
	Sprite::SetProjection(cam->GetProjectionMatrix(CameraBase::E_CAM_ANGLE_PERSPECTIVEFOV));
	XMFLOAT4X4 inv;	//�t�s��̊i�[��
	inv = cam->GetViewMatrix();
	XMMATRIX matInv = XMLoadFloat4x4(&inv);
	matInv = XMMatrixTranspose(matInv);	//�]�u����Ă�����̂����ɖ߂����߂ɍēx�]�u����
	//�ړ������͌������K�v���Ȃ��̂łO��ݒ肵�Ĉړ��𖳎�����
	XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;
	//�t�s��̌v�Z��XMMATRIX�^�ōs��
	matInv = XMLoadFloat4x4(&inv);
	matInv = XMMatrixInverse(nullptr, matInv);
	//�t�s�񁨃��[���h���r���[�̏��Ńr���{�[�h�����

	XMFLOAT4X4 world;
	XMMATRIX t = XMMatrixTranslation(m_Info.Pos.x, m_Info.Pos.y, m_Info.Pos.z);
	XMStoreFloat4x4(&world, XMMatrixTranspose(matInv * t));
	Sprite::SetWorld(world);
	Sprite::SetTexture(m_pTex);
	Sprite::SetSize(m_Info.Size);
	//--- ���C�g�̏���Geometory.cpp��������Ă���
	Sprite::SetLig(GetLig());

	Sprite::Draw();
}

Def::Info Billboard::GetInfo()
{
	return { m_Info.Pos, {m_Info.Size.x, m_Info.Size.y, 0.0f}, {0.0f, 0.0f, 0.0f} };
}
