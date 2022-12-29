//#pragma once
#ifndef _____CAMERA_DELAY_H____
#define _____CAMERA_DELAY_H____

#include "CameraBase.h"

using namespace DirectX;

class CameraDelay : public CameraBase
{
public:
	CameraDelay()
		:m_Time(0.0f) ,m_maxTime(0.0f)
	{
		m_look = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_pos = m_look;
		//CameraBase::Update();
		m_Info.pos = m_look;
	}
	~CameraDelay()
	{

	}
	void Update()
	{
		

		if (!IsDelay()) { return; }
		m_Time += 1.0f / 60.0f;
	}

	void SetCamera(XMFLOAT3 look, float radius, float time)
	{
		m_look = look;
		m_radius = radius;
		m_pos = m_look;
		m_pos.z += m_radius;
		m_maxTime = time;
		m_Info.pos = m_look;
	}
	bool IsDelay()
	{
		return m_Time < m_maxTime;
	}

private:
	float m_maxTime;
	float m_Time;

};

#endif // !_____CAMERA_DELAY_H____
