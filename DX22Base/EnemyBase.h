//#pragma once

#ifndef _____ENEMY_BASE_H____
#define _____ENEMY_BASE_H____

#include "Object.h"
#include "Collision.h"

class EnemyBase : public Object
{
public:
	EnemyBase():m_OldInfo(m_Info), m_Direction(Collision::E_DIRECTION_NULL), m_IsColPlayer(false), m_Life(300), m_Use(true) {}
	virtual void Update() = 0;

protected:
	Def::Info m_OldInfo;
	Collision::Direction m_Direction;
	bool m_IsColPlayer;
	float m_Life;
	bool m_Use;

};

#endif // !_____ENEMY_BASE_H____
