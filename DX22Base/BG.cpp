#include "BG.h"
#include "DirectXTex/Texture.h"
#include "Sprite.h"
#include "Game3D.h"

using namespace DirectX;

BG::BG()
{
	LoadTextureFromFile("Assets/ForestBG.jpg", &m_pTex);
}

BG::~BG()
{
	m_pTex->Release();
}

void BG::Draw()
{
//	//2D�\���̂��߂̍s���ݒ�
////�@�r���[�s��̓J�����̈ʒu���֌W�Ȃ��̂ŁA����������Ă���s����g���i�P�ʍs��j
////�b�P�O�O�O�b
////�b�O�P�O�O�b
////�b�O�O�P�O�b
////�b�O�O�O�P�b
//	XMFLOAT4X4 fView;
//	XMStoreFloat4x4(&fView, XMMatrixIdentity());
//
//	XMFLOAT4X4 fProj;
//	XMStoreFloat4x4(&fProj, XMMatrixTranspose(XMMatrixOrthographicOffCenterLH(
//		0.0f,		//��ʍ��[�̍��W
//		1280.0f,	//��ʉE�[�̍��W
//		720.0f,		//��ʏ�[�̍��W
//		0.0f,		//��ʉ��[�̍��W
//		-1.0f,		//Z�����Ŏʂ���ŏ��l
//		1.0f		//Z�����Ŏʂ���ő�l
//	)
//	));
//
//	//���[���h�s��ŉ�ʂ̕\���ʒu���v�Z
//	XMMATRIX t = XMMatrixTranslation(640.0f, 360.0f, 0.0f);
//	XMFLOAT4X4 fworld;
//	XMStoreFloat4x4(&fworld, XMMatrixTranspose(t));
//
//	Sprite::SetWorld(fworld);
//	Sprite::SetView(fView);
//	Sprite::SetProjection(fProj);
//	Sprite::SetSize(XMFLOAT2(1280.0f, -720.0f));
//	Sprite::SetTexture(m_pTex);
//	Sprite::Draw();
//


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
	XMMATRIX t = XMMatrixTranslation(cam->GetPos().x, cam->GetPos().y, -1.0f);
	XMStoreFloat4x4(&world, XMMatrixTranspose(matInv * t));
	Sprite::SetWorld(world);
	Sprite::SetTexture(m_pTex);
	Sprite::SetSize(XMFLOAT2(10.0f, 5.625f));

	Sprite::Draw();
}
