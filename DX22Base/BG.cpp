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
//	//2D表示のための行列を設定
////�@ビュー行列はカメラの位置が関係ないので、初期化されている行列を使う（単位行列）
////｜１０００｜
////｜０１００｜
////｜００１０｜
////｜０００１｜
//	XMFLOAT4X4 fView;
//	XMStoreFloat4x4(&fView, XMMatrixIdentity());
//
//	XMFLOAT4X4 fProj;
//	XMStoreFloat4x4(&fProj, XMMatrixTranspose(XMMatrixOrthographicOffCenterLH(
//		0.0f,		//画面左端の座標
//		1280.0f,	//画面右端の座標
//		720.0f,		//画面上端の座標
//		0.0f,		//画面下端の座標
//		-1.0f,		//Z方向で写せる最小値
//		1.0f		//Z方向で写せる最大値
//	)
//	));
//
//	//ワールド行列で画面の表示位置を計算
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
	XMFLOAT4X4 inv;	//逆行列の格納先
	inv = cam->GetViewMatrix();
	XMMATRIX matInv = XMLoadFloat4x4(&inv);
	matInv = XMMatrixTranspose(matInv);	//転置されているものを元に戻すために再度転置する
	//移動成分は撃つ消す必要がないので０を設定して移動を無視する
	XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;
	//逆行列の計算はXMMATRIX型で行う
	matInv = XMLoadFloat4x4(&inv);
	matInv = XMMatrixInverse(nullptr, matInv);
	//逆行列→ワールド→ビューの順でビルボードを作る

	XMFLOAT4X4 world;
	XMMATRIX t = XMMatrixTranslation(cam->GetPos().x, cam->GetPos().y, -1.0f);
	XMStoreFloat4x4(&world, XMMatrixTranspose(matInv * t));
	Sprite::SetWorld(world);
	Sprite::SetTexture(m_pTex);
	Sprite::SetSize(XMFLOAT2(10.0f, 5.625f));

	Sprite::Draw();
}
