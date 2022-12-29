//#pragma once

#ifndef _____CAMERA_PLAYER_H____
#define _____CAMERA_PLAYER_H____

#include "CameraBase.h"
#include "Player.h"

class CameraPlayer : public CameraBase
{
public:
	CameraPlayer(Player* pPlayer) :m_pPlayer(pPlayer) { m_pos.y += 2.0f; m_lateXZ = m_radXZ; m_lateY = m_radY; m_radius = 10.0f; }
	~CameraPlayer() {}
	void Update()
	{
		m_look = m_pPlayer->GetPos();
		m_look.y += 2.0f;
		//ƒJƒƒ‰‚ð’Ž‹“_‚ð’†S‚É‰ñ“]
		const float ROTA_Y = 2.0f;
		const float ROTA_XZ = 3.0f;

		if (IsKeyPress(VK_UP))
		{
			m_radY += XMConvertToRadians(ROTA_Y);
		}
		if (IsKeyPress(VK_DOWN))
		{
			m_radY -= XMConvertToRadians(ROTA_Y);
		}
		if (IsKeyPress(VK_LEFT))
		{
			m_radXZ += XMConvertToRadians(ROTA_XZ);
		}
		if (IsKeyPress(VK_RIGHT))
		{
			m_radXZ -= XMConvertToRadians(ROTA_XZ);
		}

		if (m_radY > 1.5f)
		{
			m_radY = 1.5f;
		}
		else if (m_radY < -1.5f)
		{
			m_radY = -1.5f;
		}

		m_lateXZ = (m_radXZ - m_lateXZ) * 0.1f + m_lateXZ;
		m_lateY = (m_radY - m_lateY) * 0.1f + m_lateY;

		m_pos.x = cos(m_lateY) * sin(m_lateXZ) * m_radius + m_look.x;
		m_pos.y = sin(m_lateY)                 * m_radius + m_look.y;
		m_pos.z = cos(m_lateY) * cos(m_lateXZ) * m_radius + m_look.z;
	}

private:
	Player* m_pPlayer;
	float m_lateXZ, m_lateY;	//–Ú“IˆÊ’u‚É‘Î‚µ‚Ä’x‚ê‚Ä‚Â‚¢‚Ä‚­‚éŠp“xiŒ»Ý‚ÌŠp“x
};

#endif // !_____CAMERA_PLAYER_H____
