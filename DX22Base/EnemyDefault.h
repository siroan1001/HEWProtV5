#pragma once

#ifndef _____ENEMY_DEFAULT_H____
#define _____ENEMY_DEFAULT_H____

#include "EnemyBase.h"

class EnemyDefault : public EnemyBase
{
public:
	EnemyDefault(Collision::Direction dire, XMFLOAT3 pos);
	void Update();

private:
	bool m_Ground;
	XMFLOAT3 m_Move;
	vector<Collision::Direction> m_StageDire;
	float m_Spead;

};

#endif // !_____ENEMY_DEFAULT_H____
