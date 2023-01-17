#include "Billboard.h"
#include "SceneGame.h"
#include "Sprite.h"

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
	CameraBase* cam = SceneGame::GetCamera();
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
	XMMATRIX t = XMMatrixTranslation(m_Info.Pos.x, m_Info.Pos.y, m_Info.Pos.z);
	XMStoreFloat4x4(&world, XMMatrixTranspose(matInv * t));
	Sprite::SetWorld(world);
	Sprite::SetTexture(m_pTex);
	Sprite::SetSize(m_Info.Size);

	Sprite::Draw();
}

Def::Info Billboard::GetInfo()
{
	return { m_Info.Pos, {m_Info.Size.x, m_Info.Size.y, 0.0f}, {0.0f, 0.0f, 0.0f} };
}
