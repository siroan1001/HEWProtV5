#include "Main.h"
#include "Effect.h"
#include "DirectX.h"
#include "Input.h"
//a

Effekseer::ManagerRef EffectManager::m_efkManager;
EffekseerRendererDX11::RendererRef EffectManager::m_efkRenderer;
Effekseer::Handle EffectManager::m_efkHandle;
CameraBase* EffectManager::m_pCamera;
Effekseer::EffectRef EffectManager::m_effect[];

EffectManager::EffectManager()
//:efkPos(0.0f,0.0f,0.0f)
//,m_pCamera(NULL)
{
	//--- effekseer�֘A������
	m_efkManager = Effekseer::Manager::Create(8000);

	auto graphicsDevice = EffekseerRendererDX11::CreateGraphicsDevice(
		GetDevice(), GetContext());
	m_efkRenderer = EffekseerRendererDX11::Renderer::Create(graphicsDevice, 8000);

	m_efkManager->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
	m_efkManager->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
	m_efkManager->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
	m_efkManager->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
	m_efkManager->SetModelRenderer(m_efkRenderer->CreateModelRenderer());

	m_efkManager->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
	m_efkManager->SetModelLoader(m_efkRenderer->CreateModelLoader());
	m_efkManager->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
	m_efkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());


	//--- effect�ǂݍ���
	// �������ŃG�t�F�N�g�̃f�[�^�ǂݍ���
	//m_effect1 = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/charge.efkefc");
	m_effect[E_EFFECT_KIND_ATK] = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/bakuhatu.efkefc");
	//m_effect1 = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/bakuhatu.efkefc");
	//m_effect2 = Effekseer::Effect::Create(m_efkManager, u"Assets/Effect/atk.efkefc");
}

EffectManager::~EffectManager()
{
	//m_effect2.Reset();
	for (int i = 0; i < E_EFFECT_KIND_MAX; i++)
	{
		m_effect[i].Reset();
	}
	m_efkRenderer.Reset();
	m_efkManager.Reset();
}

void EffectManager::Init()
{
	//--- effekseer�֘A������
	m_efkManager = Effekseer::Manager::Create(8000);

	auto graphicsDevice = EffekseerRendererDX11::CreateGraphicsDevice(
		GetDevice(), GetContext());
	m_efkRenderer = EffekseerRendererDX11::Renderer::Create(graphicsDevice, 8000);

	m_efkManager->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
	m_efkManager->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
	m_efkManager->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
	m_efkManager->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
	m_efkManager->SetModelRenderer(m_efkRenderer->CreateModelRenderer());

	m_efkManager->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
	m_efkManager->SetModelLoader(m_efkRenderer->CreateModelLoader());
	m_efkManager->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
	m_efkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());


	//--- effect�ǂݍ���
	// �������ŃG�t�F�N�g�̃f�[�^�ǂݍ���
	//m_effect1 = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/charge.efkefc");
	m_effect[E_EFFECT_KIND_ATK] = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/bakuhatu.efkefc");
	m_effect[E_EFFECT_KIND_RAIN] = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/rain.efkefc");
	//m_effect1 = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/bakuhatu.efkefc");
	//m_effect2 = Effekseer::Effect::Create(m_efkManager, u"Assets/Effect/atk.efkefc");

	m_pCamera = NULL;
}

void EffectManager::Uninit()
{
	//m_effect2.Reset();
	for (int i = 0; i < E_EFFECT_KIND_MAX; i++)
	{
		m_effect[i].Reset();
	}
	m_efkRenderer.Reset();
	m_efkManager.Reset();
}

void EffectManager::Update()
{
	// �}�l�[�W���[�̍X�V
	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);

	// ���Ԃ��X�V����
	static float time = 0.0f;
	m_efkRenderer->SetTime(time);
	DirectX::XMFLOAT3 pos = m_pCamera->GetPos();

	auto viewerPosition = Effekseer::Vector3D(pos.x,pos.y, pos.z);
	::Effekseer::Matrix44 projectionMatrix;
	projectionMatrix.PerspectiveFovLH(
		(60 * 3.14f / 180.0f), (16.0f / 9.0f),
		0.2f, 1000.0f);

	// m_fovy(60 * 3.14f / 180.0f), m_aspect(16.0f / 9.0f), m_near(0.2f), m_far(1000.0f)
	

	::Effekseer::Matrix44 cameraMatrix;
	DirectX::XMFLOAT3 look = m_pCamera->GetLook();

	cameraMatrix.LookAtLH(viewerPosition,	
		Effekseer::Vector3D(look.x,look.y,look.z),
		Effekseer::Vector3D(0.0f, 1.0f, 0.0f));

	// ���C���[�p�����[�^�̐ݒ�
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = viewerPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);



	// ���e�s���ݒ�
	m_efkRenderer->SetProjectionMatrix(projectionMatrix);
	// �J�����s���ݒ�
	m_efkRenderer->SetCameraMatrix(cameraMatrix);

	time++;

}

void EffectManager::Draw()
{
	// �G�t�F�N�g�̕`��J�n�������s���B
	m_efkRenderer->BeginRendering();

	// �G�t�F�N�g�̕`����s���B
	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix =
		m_efkRenderer->GetCameraProjectionMatrix();
	m_efkManager->Draw(drawParameter);

	// �G�t�F�N�g�̕`��I���������s���B
	m_efkRenderer->EndRendering();

}
void EffectManager::SetEffect(EffectKind effect, float x, float y, float z)
{
	m_efkHandle = m_efkManager->Play(m_effect[effect], x, y, z);//0.0.0�����W
	m_efkManager->SetScale(m_efkHandle, 0.03f, 0.03f, 0.005f);	//�T�C�Y�ϊ�
	//EffectManager::Draw();
}
void EffectManager::SetCamera(CameraBase* pCamera)
{
	m_pCamera = pCamera;
}

// Play�œǂݍ���
// SetScale(�Œ�A�T�C�Y�R��)
// Draw