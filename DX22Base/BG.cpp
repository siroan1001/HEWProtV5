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
//	XMFLOAT4X4 inv;	//‹ts—ñ‚ÌŠi”[æ
//	inv = cam->GetViewMatrix();
//	XMMATRIX matInv = XMLoadFloat4x4(&inv);
//	matInv = XMMatrixTranspose(matInv);	//“]’u‚³‚ê‚Ä‚¢‚é‚à‚Ì‚ðŒ³‚É–ß‚·‚½‚ß‚ÉÄ“x“]’u‚·‚é
//	//ˆÚ“®¬•ª‚ÍŒ‚‚ÂÁ‚·•K—v‚ª‚È‚¢‚Ì‚Å‚O‚ðÝ’è‚µ‚ÄˆÚ“®‚ð–³Ž‹‚·‚é
//	XMStoreFloat4x4(&inv, matInv);
//	inv._41 = inv._42 = inv._43 = 0.0f;
//	//‹ts—ñ‚ÌŒvŽZ‚ÍXMMATRIXŒ^‚Ås‚¤
//	matInv = XMLoadFloat4x4(&inv);
//	matInv = XMMatrixInverse(nullptr, matInv);
//	//‹ts—ñ¨ƒ[ƒ‹ƒh¨ƒrƒ…[‚Ì‡‚Åƒrƒ‹ƒ{[ƒh‚ðì‚é
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
