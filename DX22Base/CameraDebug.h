//#pragma once
#ifndef _____CAMERA_DEBUG_H____
#define _____CAMERA_DEBUG_H____

#include "Input.h"
#include "CameraBase.h"

using namespace DirectX;

class CameraDebug : public CameraBase
{
public:
	CameraDebug() {};
	~CameraDebug() {};
	void Update()
	{
		//if (IsKeyPress(VK_UP))
		//{
		//	m_look.z--;
		//}
		//if (IsKeyPress(VK_DOWN))
		//{
		//	m_look.z++;
		//}
		//if (IsKeyPress(VK_LEFT))
		//{
		//	m_look.x++;
		//}
		//if (IsKeyPress(VK_RIGHT))
		//{
		//	m_look.x--;
		//}
		//if (IsKeyPress(VK_SHIFT))
		//{
		//	m_look.y++;
		//}
		//if (IsKeyPress(VK_CONTROL))
		//{
		//	m_look.y--;
		//}
		//m_look = ;

		if (IsKeyPress(VK_RIGHT))
		{
			m_pos.x -= 0.1f;
			m_look.x -= 0.1f;
		}
		if (IsKeyPress(VK_LEFT))
		{
			m_pos.x += 0.1f;
			m_look.x += 0.1f;
		}

		if (IsKeyPress(VK_UP))
		{
			m_pos.y -= 0.1f;
			m_look.y -= 0.1f;
		}
		if (IsKeyPress(VK_UP))
		{
			m_pos.y += 0.1f;
			m_look.y += 0.1f;
		}

		if (IsKeyPress(VK_CONTROL))
		{
			m_pos.z -= 0.1f;
			m_look.z -= 0.1f;
		}
		if (IsKeyPress(VK_SHIFT))
		{
			m_pos.z += 0.1f;
			m_look.z += 0.1f;
		}

		//カメラを注視点を中心に回転
		const float ROTA_Y = 2.0f;
		const float ROTA_X = 3.0f;

		if (IsKeyPress('W'))
		{
			m_radY += XMConvertToRadians(ROTA_Y);
		}
		if (IsKeyPress('S'))
		{
			m_radY -= XMConvertToRadians(ROTA_Y);
		}
		if (IsKeyPress('A'))
		{
			m_radXZ += XMConvertToRadians(ROTA_X);
		}
		if (IsKeyPress('D'))
		{
			m_radXZ -= XMConvertToRadians(ROTA_X);
		}

		if (m_radY > 1.5f)
		{
			m_radY = 1.5f;
		}
		else if (m_radY < -1.5f)
		{
			m_radY = -1.5f;
		}

		//カメラと注視点の距離を変える
		const float RADIUS_MOVE = 0.1f;
		const float MAX_CAMERA_RADIUS = 15.0f;
		const float MIN_CAMERA_RADIUS = 1.0f;

		if (IsKeyPress('Q'))
		{
			m_radius += RADIUS_MOVE;	//近づく
		}
		if (IsKeyPress('E'))
		{
			m_radius -= RADIUS_MOVE;	//離れる
		}
		
		if (m_radius < MIN_CAMERA_RADIUS)
		{
			m_radius = MIN_CAMERA_RADIUS;
		}
		else if(m_radius > MAX_CAMERA_RADIUS)
		{
			m_radius = MAX_CAMERA_RADIUS;
		}

		m_pos.x = cos(m_radY) * sin(m_radXZ) * m_radius + m_look.x;
		m_pos.y = sin(m_radY)                * m_radius + m_look.y;
		m_pos.z = cos(m_radY) * cos(m_radXZ) * m_radius + m_look.z;



	}

};

#endif // !_____CAMERA_DEBUG_H____
