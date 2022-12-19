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
//	//2D•\Ž¦‚Ì‚½‚ß‚Ìs—ñ‚ðÝ’è
////‡@ƒrƒ…[s—ñ‚ÍƒJƒƒ‰‚ÌˆÊ’u‚ªŠÖŒW‚È‚¢‚Ì‚ÅA‰Šú‰»‚³‚ê‚Ä‚¢‚és—ñ‚ðŽg‚¤i’PˆÊs—ñj
////b‚P‚O‚O‚Ob
////b‚O‚P‚O‚Ob
////b‚O‚O‚P‚Ob
////b‚O‚O‚O‚Pb
//	XMFLOAT4X4 fView;
//	XMStoreFloat4x4(&fView, XMMatrixIdentity());
//
//	XMFLOAT4X4 fProj;
//	XMStoreFloat4x4(&fProj, XMMatrixTranspose(XMMatrixOrthographicOffCenterLH(
//		0.0f,		//‰æ–Ê¶’[‚ÌÀ•W
//		1280.0f,	//‰æ–Ê‰E’[‚ÌÀ•W
//		720.0f,		//‰æ–Êã’[‚ÌÀ•W
//		0.0f,		//‰æ–Ê‰º’[‚ÌÀ•W
//		-1.0f,		//Z•ûŒü‚ÅŽÊ‚¹‚éÅ¬’l
//		1.0f		//Z•ûŒü‚ÅŽÊ‚¹‚éÅ‘å’l
//	)
//	));
//
//	//ƒ[ƒ‹ƒhs—ñ‚Å‰æ–Ê‚Ì•\Ž¦ˆÊ’u‚ðŒvŽZ
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
	XMFLOAT4X4 inv;	//‹ts—ñ‚ÌŠi”[æ
	inv = cam->GetViewMatrix();
	XMMATRIX matInv = XMLoadFloat4x4(&inv);
	matInv = XMMatrixTranspose(matInv);	//“]’u‚³‚ê‚Ä‚¢‚é‚à‚Ì‚ðŒ³‚É–ß‚·‚½‚ß‚ÉÄ“x“]’u‚·‚é
	//ˆÚ“®¬•ª‚ÍŒ‚‚ÂÁ‚·•K—v‚ª‚È‚¢‚Ì‚Å‚O‚ðÝ’è‚µ‚ÄˆÚ“®‚ð–³Ž‹‚·‚é
	XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;
	//‹ts—ñ‚ÌŒvŽZ‚ÍXMMATRIXŒ^‚Ås‚¤
	matInv = XMLoadFloat4x4(&inv);
	matInv = XMMatrixInverse(nullptr, matInv);
	//‹ts—ñ¨ƒ[ƒ‹ƒh¨ƒrƒ…[‚Ì‡‚Åƒrƒ‹ƒ{[ƒh‚ðì‚é

	XMFLOAT4X4 world;
	XMMATRIX t = XMMatrixTranslation(cam->GetPos().x, cam->GetPos().y, -1.0f);
	XMStoreFloat4x4(&world, XMMatrixTranspose(matInv * t));
	Sprite::SetWorld(world);
	Sprite::SetTexture(m_pTex);
	Sprite::SetSize(XMFLOAT2(10.0f, 5.625f));

	Sprite::Draw();
}
