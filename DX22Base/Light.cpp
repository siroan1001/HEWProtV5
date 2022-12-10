#include "Light.h"
#include "Input.h"

Light::Light()
	:m_Info{ {1.0f, 1.0f, 0.0f}, {0.5f, 0.1f, 0.5f}, {XMConvertToRadians(90.0f), 0.0f, 0.0f} }
	,m_Power(5.0f)
{

}

Light::~Light()
{
}

void Light::Update()
{
	const float LIGHT_MOVE = 0.05f;

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
}

void Light::Draw()
{
	SetGeometoryTranslate(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	SetGeometoryScaling(m_Info.size.x, m_Info.size.y, m_Info.size.z);
	SetGeometoryRotation(m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
	DrawCylinder();
}

float Light::GetRadius()
{
	return GetCylinderRadius() * m_Info.size.x;
}

Stage::Info Light::GetInfo()
{
	return m_Info;
}

float Light::GetPower()
{
	return m_Power;
}
