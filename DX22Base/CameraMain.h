//#pragma once
#ifndef _____CAMERA_MAIN_H____
#define _____CAMERA_MAIN_H____

#include "CameraBase.h"
#include "Player.h"
#include "Collision.h"
#include "Stage.h"

class CameraMain : public CameraBase
{
public:
	CameraMain() : m_pPlayer(NULL), m_lateXZ(90.0f), m_lateY(0.0f), m_LimitX{0.0f, 0.0f}, m_LimitY{ 0.0f, 0.0f }{ m_radius = 3.0f; }
	~CameraMain() {}
	void Update()
	{
		//if (Game3D::GetGameStatus() != Game3D::E_GAME_STATUS_NORMAL)	return;

		const float LIMIT = 1.5f;
		XMFLOAT3 Playerpos = m_pPlayer->GetInfo().pos;

		if (Game3D::GetGameStatus() == Game3D::E_GAME_STATUS_NORMAL)
		{
			switch (m_pPlayer->GetDirection())
			{
			case Collision::E_DIRECTION_L:

				m_look.x += 0.1f;

				if (m_look.x - LIMIT > Playerpos.x)
				{
					m_look.x = Playerpos.x + LIMIT;
				}

				if (m_look.x > 9.0f)
				{
					m_look.x = 9.0f;
				}

				break;
			case Collision::E_DIRECTION_R:
				m_look.x -= 0.1f;


				if (m_look.x + LIMIT < Playerpos.x)
				{
					m_look.x = Playerpos.x - LIMIT;
				}



				break;
			default:
				break;
			}
		}

		m_look.y = Playerpos.y + 1.0f;


		m_pos.x = m_look.x;
		m_pos.y = m_look.y;
		m_pos.z = m_look.z + m_radius;

		m_Info.pos = m_look;
	}
	void SetPlayer(Player* player)
	{
		m_pPlayer = player;
	}
	void SetLook(XMFLOAT3 look)
	{
		m_look = look;
		m_pos = look;
		m_pos.z += m_radius;
		m_Info.pos = m_look;
	}

private:
	float m_lateY, m_lateXZ;
	Player* m_pPlayer;
	XMFLOAT2 m_LimitX;	//max,min
	XMFLOAT2 m_LimitY;	//max,min
};

#endif // !_____CAMERA_MAIN_H____
