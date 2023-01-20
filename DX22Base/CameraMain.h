//#pragma once
#ifndef _____CAMERA_MAIN_H____
#define _____CAMERA_MAIN_H____

#include "CameraBase.h"
#include "Player.h"
#include "Collision.h"
#include "Stage.h"

struct CameraAreaSide {
	float Top, Bottom, Left, Right;
};
class CameraMain : public CameraBase
{
public:
	CameraMain() : m_pPlayer(NULL), m_lateXZ(90.0f), m_lateY(0.0f), m_LimitX{0.0f, 0.0f}, m_LimitY{ 0.0f, 0.0f }
	{
		m_radius = 2.0f;
		m_currentCameraArea = 0;
	}
	~CameraMain() {}
	void Update()
	{

		m_pCameraArea = m_pStage->GetCameraArea();
		CameraAreaSide side;

		// カメラ範囲を計算して格納
		for (auto it = m_pCameraArea.begin(); it != m_pCameraArea.end(); ++it)
		{
			side.Top = ((*it)->pos.y + (*it)->size.y / 2);
			side.Bottom = ((*it)->pos.y - (*it)->size.y / 2);
			side.Right = ((*it)->pos.x - (*it)->size.x / 2);
			side.Left = ((*it)->pos.x + (*it)->size.x / 2);

			m_Side.push_back(side);
		}
		//if (SceneGame::GetGameStatus() != SceneGame::E_GAME_STATUS_NORMAL)	return;

		const float LIMIT = 1.2f;
		XMFLOAT3 Playerpos = m_pPlayer->GetInfo().pos;

		if (SceneGame::GetGameStatus() == SceneGame::E_GAME_STATUS_NORMAL)
		{
			/*
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
			*/
			switch (m_pPlayer->GetDirection())
			{
			case Collision::E_DIRECTION_L:

				m_look.x = Playerpos.x + LIMIT;
				
				if (m_look.x > m_Side[m_currentCameraArea].Left)
				{
					m_look.x = m_Side[m_currentCameraArea].Left;	// 注視点をカメラ範囲の超えた地点にする
					if (m_Side.size() > m_currentCameraArea)		
					{
						m_currentCameraArea++;	// 1つ後のカメラ範囲に設定
					}
				}
				break;
			case Collision::E_DIRECTION_R:
				m_look.x = Playerpos.x - LIMIT;
				if (m_look.x < m_Side[m_currentCameraArea].Right)
				{
					m_look.x = m_Side[m_currentCameraArea].Right;
					if (m_currentCameraArea > 0)
					{
						m_currentCameraArea--; // 1つ前のカメラ範囲に設定
					}
				}
				break;
			default:
				break;
			}
		}

		m_look.y = Playerpos.y + 0.8f;
		if (m_look.y > m_Side[m_currentCameraArea].Top)
		{
			m_look.y = m_Side[m_currentCameraArea].Top;
		}
		if (m_look.y < m_Side[m_currentCameraArea].Bottom)
		{
			m_look.y = m_Side[m_currentCameraArea].Bottom;
		}


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
	void SetStage(Stage* stage)
	{
		m_pStage = stage;
	}

private:
	float m_lateY, m_lateXZ;
	Player* m_pPlayer;
	XMFLOAT2 m_LimitX;	//max,min
	XMFLOAT2 m_LimitY;	//max,min

	Stage* m_pStage;		// カメラ範囲の設定
	vector<CameraAreaSide> m_Side;
	vector<Def::Info*> m_pCameraArea;
	int m_currentCameraArea;

};

#endif // !_____CAMERA_MAIN_H____
