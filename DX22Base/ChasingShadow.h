#ifndef _____CHASING_SHADOW_H____
#define _____CHASING_SHADOW_H____

#include <list>
#include "Stage.h"
#include "Player.h"

class ChasingShadow
{
public:
	ChasingShadow();
	~ChasingShadow();
	void Update();
	void Draw();

	void SetPlayer(Player * pPlayer);

	Def::Info GetInfo();
	float GetRadius();

private:
	Def::Info m_Info;


	Player * m_pPlayer;
	Collision::Direction m_PlDirection;

	std::list<XMFLOAT3> m_PosLog;
};

#endif // !_____CHASING_SHADOW_H____
