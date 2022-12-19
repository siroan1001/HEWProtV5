//#pragma once
#ifndef _____CAMERA_MAIN_H____
#define _____CAMERA_MAIN_H____

#include "CameraBase.h"
#include "Player.h"

class CameraMain : public CameraBase
{
public:
	CameraMain() : m_pPlayer(NULL), m_lateXZ(90.0f), m_lateY(0.0f) { m_radius = 3.0f; }
	~CameraMain() {}
	void Update()
	{
		m_look = m_pPlayer->GetInfo().pos;
		m_look.x -= 2.0f;
		m_look.y += 1.0f;
		
		//m_pos.x = cos(m_lateY) * sin(m_lateXZ) * m_radius + m_look.x;
		//m_pos.y = sin(m_lateY)                 * m_radius + m_look.y;
		//m_pos.z = cos(m_lateY) * cos(m_lateXZ) * m_radius + m_look.z;

		m_pos.x = m_look.x;
		m_pos.y = m_look.y;
		m_pos.z = m_look.z + m_radius;
	}
	void SetPlayer(Player* player)
	{
		m_pPlayer = player;
	}

private:
	float m_lateY, m_lateXZ;
	Player* m_pPlayer;
};

#endif // !_____CAMERA_MAIN_H____
