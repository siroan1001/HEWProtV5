#include "Main.h"
#include "DirectX.h"
#include "WinUtil.h"
#include "DirectXTex/Texture.h"
#include "Input.h"
#include "Game3D.h"
#include "Geometory.h"
#include "Sprite.h"
#include "SpriteDefault.h"
#include "Object.h"
#include "ModelList.h"
#include "Quadtree.h"
#include "controller.h"
#include "Effect.h"
#include "ShadowBlock.h"
#include "Sound.h"

using namespace IKD;

//--- �萔��`
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

//-- �O���[�o���ϐ�
Game3D* g_pGame;

unsigned int GetAppWidth()
{
	return SCREEN_WIDTH;
}
unsigned int GetAppHeight()
{
	return SCREEN_HEIGHT;
}

void Init()
{
	if (FAILED(InitDX(GetHWND(), SCREEN_WIDTH, SCREEN_HEIGHT, false)))
	{
		Error("directx initialize failed.");
	}
	if (FAILED(InitTexture(GetDevice())))
	{
		Error("texture initialize failed.");
	}
	if (FAILED(InitInput()))
	{
		Error("input initialize failed.");
	}
	if (FAILED(InitGeometory()))
	{
		Error("geometory initialize failed.");
	}
	//SetGeometoryColor(XMFLOAT3(1.0f, 1.0f, 1.0f));
	Object::Init();
	SpriteDefault::Init();
	Sprite::Init();
	ModelList::Init();
	EffectManager::Init();
	ShadowBlock::Init();
	Sound::Init();

	InitCtrl();

	if (!CheckCtrl())
	{
		Error("controller initialize failed.");
	}
	
	g_pGame = new Game3D();
}
void Uninit()
{
	
	delete g_pGame;
	UninitCtrl();
	Sound::Unitit();
	ShadowBlock::Uninit();
	EffectManager::Uninit();
	ModelList::Uninit();
	Object::Uninit();
	Sprite::Uninit();
	SpriteDefault::Uninit();
	UninitGeometory();
	UninitInput();
	UninitTexture();
	UninitDX();
}
void Update(float deltaTime)
{
	UpdateInput();
	UpdateCtrl();
	EffectManager::Update();
	g_pGame->Update();
}
void Draw()
{
	BeginDrawDX();
	g_pGame->Draw();
	EffectManager::Draw();
	EndDrawDX();
}
