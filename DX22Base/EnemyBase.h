//#pragma once

#ifndef _____ENEMY_BASE_H____
#define _____ENEMY_BASE_H____

#include "Object.h"
#include "Collision.h"

class EnemyBase : public Object
{
public:
	EnemyBase():m_Direction(Collision::E_DIRECTION_NULL), m_IsColPlayer(false), m_Life(300), m_Use(true) {}
	virtual void Update() = 0;

	bool IsCollision() { return m_IsCollision; }

	bool GetUse() { return m_Use; }
	
	void SetPos(XMFLOAT3 pos) { m_Info.pos = pos; }

protected:
	
	Collision::Direction m_Direction;
	bool m_IsColPlayer;
	float m_Life;
	bool m_Use;
	bool m_IsCollision;

};

#endif // !_____ENEMY_BASE_H____
