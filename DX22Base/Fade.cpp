#include "Fade.h"
#include "DirectXTex/Texture.h"
#include "Game3D.h"
#include "DirectX.h"
#include "SpriteDefault.h"

Fade::Fade() :
	m_color{ 0.0f, 0.0f ,0.0f, 0.0f }
	, m_state(FADE_NONE)
	, m_frame(60.0f)
	, m_skipflag(false)
{
	m_pFadePS = new PixelShader;
	m_pFadePS->Load("Assets/Shader/FadePS.cso");
}
Fade::~Fade()
{
	delete m_pFadePS;
}

void Fade::Update()
{

	switch (m_state)
	{
	case (FADE_IN):
		m_color.w -= 1.0f / m_frame;
		if (m_color.w <= 0.0f)
		{
			m_color.w = 0.0f;
			m_state = FADE_NONE;
		}
		break;
	case (FADE_OUT):
		m_color.w += 1.0f / m_frame;
		if (m_color.w >= 1.0f)
		{
			m_color.w = 1.0f;
			m_state = FADE_IN;
			Game3D::StartSceneChange();
		}
		break;
	case (FADE_SKIP):
		m_skipflag = false;
		m_state = FADE_NONE;
		Game3D::StartSceneChange();
		break;
	default:
		break;
	}

}

void Fade::Draw()
{
	// 2D�\���̂��߂̍s���ݒ�
	DirectX::XMFLOAT4X4 fView;
	DirectX::XMStoreFloat4x4(&fView, DirectX::XMMatrixIdentity());

	// ���̍s���2D�̃X�N���[���̑傫�������߂�
	DirectX::XMFLOAT4X4 fProj;
	DirectX::XMStoreFloat4x4(&fProj,
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(
				0.0f,		// ��ʍ��[�̍��W
				1280.0f,	// ��ʉE�[�̍��W
				720.0f,		// ��ʉ��[�̍��W
				0.0f,		// ��ʏ�[�̍��W
				-1.0f,		// z�����Ŏʂ���ŏ��l
				1.0f		// z�����Ŏʂ���ő�l
			)
		));

	// ���[���h�s��ŉ�ʂ̕\���ʒu���v�Z
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(640.0f, 360.0f, 0.0f);
	DirectX::XMFLOAT4X4 fWorld;
	DirectX::XMStoreFloat4x4(&fWorld,
		DirectX::XMMatrixTranspose(T));

	// �X�v���C�g�̐ݒ�
	SpriteDefault::SetWorld(fWorld);
	SpriteDefault::SetView(fView);
	SpriteDefault::SetProjection(fProj);
	SpriteDefault::SetPixelShader(m_pFadePS);
	SpriteDefault::SetSize(DirectX::XMFLOAT2(1280.0f, -720.0f));
	SpriteDefault::SetColor(m_color);
	EnableDepth(false);
	SpriteDefault::Draw();
	EnableDepth(true);

}

void Fade::StartOut()
{
	if (FADE_NONE != m_state) {
		return;
	}
	if (m_skipflag == true) {
		m_state = FADE_SKIP;
		return;
	}
	m_state = FADE_OUT;
}

void Fade::SetFrame(float frame)
{
	m_frame = frame;
}

// �t�F�[�h���X�L�b�v����
void Fade::Skip()
{
	m_skipflag = true;
}