#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX11.h> 
#include "Game3D.h"
#include "CameraBase.h"
//a
class EffectManager
{
public:
	enum EffectKind
	{
		E_EFFECT_KIND_ATK = 0,
		E_EFFECT_KIND_RAIN,

		E_EFFECT_KIND_MAX
	};

public:
	EffectManager();
	~EffectManager();
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static void SetEffect(EffectKind effect, float x, float y, float z);
	static void SetCamera(CameraBase* pCamera);
private:
	static Effekseer::ManagerRef m_efkManager;
	static EffekseerRendererDX11::RendererRef m_efkRenderer;
	static Effekseer::Handle m_efkHandle;

	static CameraBase* m_pCamera;

	static Effekseer::EffectRef m_effect[E_EFFECT_KIND_MAX];
};



