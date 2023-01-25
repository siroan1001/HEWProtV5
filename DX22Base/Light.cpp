#include "Light.h"
#include "Input.h"
#include "controller.h"

Light::Light()
	:m_Info{ {-3.8f, 4.25f, -0.20f}, {0.45f, 0.0001f, 0.45f}, {XMConvertToRadians(90.0f), 0.0f, 0.0f} }
	,m_Power(30.0f)
{

}

Light::~Light()
{
}

void Light::Update()
{
	XMFLOAT3 CameraPos = m_pCamera->GetPos();
	float right = CameraPos.x + 2.0f;
	float left = CameraPos.x - 2.0f;
	float ceiling = CameraPos.y + 1.0f;
	float floor = CameraPos.y - 1.0f;

	const float LIGHT_MOVE = 0.05f;

	XMFLOAT2 stick = GetLStick();

	m_Info.pos.x -= stick.x / 25.0f;
	m_Info.pos.y += stick.y / 25.0f;

	if (IsKeyPress(VK_LEFT))
	{
		m_Info.pos.x += LIGHT_MOVE;
	}
	if (IsKeyPress(VK_RIGHT))
	{
		m_Info.pos.x -= LIGHT_MOVE;
	}
	if (IsKeyPress(VK_UP))
	{
		m_Info.pos.y += LIGHT_MOVE;
	}
	if (IsKeyPress(VK_DOWN))
	{
		m_Info.pos.y -= LIGHT_MOVE;
	}
	if (m_Info.pos.x > right)m_Info.pos.x = right;
	if (m_Info.pos.x < left)m_Info.pos.x = left;
	if (m_Info.pos.y > ceiling)m_Info.pos.y = ceiling;
	if (m_Info.pos.y < floor)m_Info.pos.y = floor;
}

void Light::Draw()
{
	SetGeometoryTranslate(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	SetGeometoryScaling(m_Info.size.x, m_Info.size.y, m_Info.size.z);
	SetGeometoryRotation(m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
	XMFLOAT3 LigPos = m_Info.pos; LigPos.z += 10.0f;
	SetGeometorySpLigPos(LigPos);
	//SetGeometoryColor(DirectX::XMFLOAT4(246.0f / 255.0f, 139.0f / 255.0f, 30.0f / 255.0f, 0.5f));
	SetGeometoryColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.6f));
	DrawCylinder();
}

float Light::GetRadius()
{
	return GetCylinderRadius() * m_Info.size.x;
}

Def::Info Light::GetInfo()
{
	return m_Info;
}

float Light::GetPower()
{
	return m_Power;
}

void Light::SetCamera(CameraBase * pCamera)
{
	m_pCamera = pCamera;
}