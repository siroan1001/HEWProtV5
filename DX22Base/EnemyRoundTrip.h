//#pragma once
#ifndef _____ENEMY_ROUND_TRIP_H____
#define _____ENEMY_ROUND_TRIP_H____

#include "EnemyBase.h"

class EnemyRoundTrip : public EnemyBase
{
public:
	EnemyRoundTrip(Collision::Direction dire, XMFLOAT3 pos, XMFLOAT3 point, int flame);
	void Update();

private:

};

#endif // !_____ENEMY_ROUND_TRIP_H____
