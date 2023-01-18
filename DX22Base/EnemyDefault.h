#pragma once

#ifndef _____ENEMY_DEFAULT_H____
#define _____ENEMY_DEFAULT_H____

#include "EnemyBase.h"
#include "Collision.h"

class EnemyDefault : public EnemyBase
{
public:
	EnemyDefault(Collision::Direction dire, XMFLOAT3 pos);
	void Update();

	Def::Info GetOldInfo();
	Collision::Direction GetStageCollistonDirection(int num);

	void SetStageCollisionDirection(Collision::Direction dire, int num);
	void SetDirection(Collision::Direction);

	void InitDirectin(int);

	void ResetMove();

private:
	Def::Info m_OldInfo;
	bool m_Ground;
	XMFLOAT3 m_Move;
	vector<Collision::Direction> m_StageDire;
	float m_Spead;

};

#endif // !_____ENEMY_DEFAULT_H____
