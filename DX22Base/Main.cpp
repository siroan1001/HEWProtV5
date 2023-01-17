#include "Main.h"
#include "DirectX.h"
#include "WinUtil.h"
#include "DirectXTex/Texture.h"
#include "Input.h"
#include "Game3D.h"
#include "Geometory.h"
#include "Sprite.h"
#include "Object.h"
#include "ModelList.h"
#include "Quadtree.h"

using namespace IKD;

//--- 定数定義
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

//-- グローバル変数
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
	Sprite::Init();
	ModelList::Init();

	
	
	g_pGame = new Game3D();
}
void Uninit()
{
	delete g_pGame;
	ModelList::Uninit();
	Object::Uninit();
	Sprite::Uninit();
	UninitGeometory();
	UninitInput();
	UninitTexture();
	UninitDX();
}
void Update(float deltaTime)
{
	UpdateInput();
	g_pGame->Update();
}
void Draw()
{
	BeginDrawDX();
	g_pGame->Draw();
	EndDrawDX();
}
