#include "BG.h"
#include "DirectXTex/Texture.h"
#include "Sprite.h"
#include "Game3D.h"

using namespace DirectX;

BG::BG()
{
	LoadTextureFromFile("Assets/ForestBG.jpg", &m_pTex);
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, -1.0f);
	m_Info.Size = XMFLOAT2(10.0f, 5.625f);
}

void BG::Update()
{
	CameraBase* cam = Game3D::GetCamera();
	m_Info.Pos = XMFLOAT3(cam->GetPos().x, cam->GetPos().y, -1.0f);
}



//void BG::Draw()
//{
//	CameraBase* cam = Game3D::GetCamera();
//	Sprite::SetView(cam->GetViewMatrix());
//	Sprite::SetProjection(cam->GetProjectionMatrix(CameraBase::E_CAM_ANGLE_PERSPECTIVEFOV));
//	XMFLOAT4X4 inv;	//逆行列の格納先
//	inv = cam->GetViewMatrix();
//	XMMATRIX matInv = XMLoadFloat4x4(&inv);
//	matInv = XMMatrixTranspose(matInv);	//転置されているものを元に戻すために再度転置する
//	//移動成分は撃つ消す必要がないので０を設定して移動を無視する
//	XMStoreFloat4x4(&inv, matInv);
//	inv._41 = inv._42 = inv._43 = 0.0f;
//	//逆行列の計算はXMMATRIX型で行う
//	matInv = XMLoadFloat4x4(&inv);
//	matInv = XMMatrixInverse(nullptr, matInv);
//	//逆行列→ワールド→ビューの順でビルボードを作る
//
//	XMFLOAT4X4 world;
//	XMMATRIX t = XMMatrixTranslation(cam->GetPos().x, cam->GetPos().y, -1.0f);
//	XMStoreFloat4x4(&world, XMMatrixTranspose(matInv * t));
//	Sprite::SetWorld(world);
//	Sprite::SetTexture(m_pTex);
//	Sprite::SetSize(XMFLOAT2(10.0f, 5.625f));
//
//	Sprite::Draw();
//}
