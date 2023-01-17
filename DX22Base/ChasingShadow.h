#ifndef _____CHASING_SHADOW_H____
#define _____CHASING_SHADOW_H____

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

private:
	Def::Info m_Info;


	Player * m_pPlayer;
	Collision::Direction m_PlDirection;
};

#endif // !_____CHASING_SHADOW_H____
