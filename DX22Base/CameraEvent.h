//#pragma once
#ifndef _____CAMERA_EVENT_H____
#define _____CAMERA_EVENT_H____

#include "CameraBase.h"
#include <DirectXMath.h>

using namespace DirectX;

class CameraEvent : public CameraBase
{
public:
	CameraEvent() : m_Start(0.0f, 0.0f, 0.0f), m_End(0.0f, 0.0f, 0.0f), m_Time(0.0f), m_TotalTime(0.0f){}
	~CameraEvent() {}
	void Update()
	{
		if (!IsEvent()) { return; }
		XMFLOAT3 ES = { m_End.x - m_Start.x, m_End.y - m_Start.y, m_End.z - m_Start.z };
		float rate = 1 - pow(1 - m_Time / m_TotalTime, 3);
		XMFLOAT3 ESR = { ES.x * rate, ES.y * rate, ES.z * rate };
		XMFLOAT3 lerp = { ESR.x + m_Start.x, ESR.y + m_Start.y, ESR.z + m_Start.z };
		m_look = lerp;

		m_pos.x = cos(m_radY) * sin(m_radXZ) * m_radius + m_look.x;
		m_pos.y = sin(m_radY)                * m_radius + m_look.y;
		m_pos.z = cos(m_radY) * cos(m_radXZ) * m_radius + m_look.z;

		m_Time += 1.0f / 60.0f;
	}
	//void Draw();
	
	void SetEvent(XMFLOAT3 start, XMFLOAT3 end, float time)
	{
		m_Start = start;
		m_End = end;
		m_Time = 0.0f;
		m_TotalTime = time;
	}
	bool IsEvent()
	{
		return m_Time < m_TotalTime;
	}

private:
	XMFLOAT3 m_Start;
	XMFLOAT3 m_End;
	float m_Time;
	float m_TotalTime;
};

#endif // !_____CAMERA_EVENT_H____
