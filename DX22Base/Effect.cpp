#include "Main.h"
#include "Effect.h"
#include "DirectX.h"
#include "Input.h"
//a
EffectManager::EffectManager()
:efkPos(0.0f,0.0f,0.0f)
,m_pCamera(NULL)
{
	//--- effekseer関連初期化
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


	//--- effect読み込み
	// ↓ここでエフェクトのデータ読み込み
	//m_effect1 = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/charge.efkefc");
	m_effect1 = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/bakuhatu.efkefc");
	//m_effect1 = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/bakuhatu.efkefc");
	//m_effect2 = Effekseer::Effect::Create(m_efkManager, u"Assets/Effect/atk.efkefc");
}

EffectManager::~EffectManager()
{
	//m_effect2.Reset();
	m_effect1.Reset();
	m_efkRenderer.Reset();
	m_efkManager.Reset();
}

void EffectManager::Update()
{
	// マネージャーの更新
	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);

	// 時間を更新する
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

	// レイヤーパラメータの設定
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = viewerPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);



	// 投影行列を設定
	m_efkRenderer->SetProjectionMatrix(projectionMatrix);
	// カメラ行列を設定
	m_efkRenderer->SetCameraMatrix(cameraMatrix);

	time++;

}

void EffectManager::Draw()
{
	
	// エフェクトの描画開始処理を行う。
	m_efkRenderer->BeginRendering();

	// エフェクトの描画を行う。
	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix =
		m_efkRenderer->GetCameraProjectionMatrix();
	m_efkManager->Draw(drawParameter);

	// エフェクトの描画終了処理を行う。
	m_efkRenderer->EndRendering();


}
void EffectManager::AtkEffect(float x, float y, float z)
{
	efkPos.x = x;
	efkPos.y = y;
	efkPos.z = z;
	m_efkHandle = m_efkManager->Play(m_effect1,efkPos.x, efkPos.y, efkPos.z);//0.0.0が座標
	m_efkManager->SetScale(m_efkHandle, 1.0f, 1.0f, 1.0f);	//サイズ変換
	EffectManager::Draw();
}
void EffectManager::SetCamera(CameraBase* pCamera)
{
	m_pCamera = pCamera;
}

// Playで読み込み
// SetScale(固定、サイズ３つ)
// Draw