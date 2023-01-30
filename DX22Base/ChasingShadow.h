#ifndef _____CHASING_SHADOW_H____
#define _____CHASING_SHADOW_H____

#include <list>
#include "Stage.h"
#include "Player.h"
#include "Object.h"

//class ChasingShadow
//{
//public:
//	ChasingShadow();
//	~ChasingShadow();
//	void Update();
//	void Draw();
//
//	void SetPlayer(Player * pPlayer);
//
//	Def::Info GetInfo();
//	float GetRadius();
//
//private:
//	Def::Info m_Info;
//
//
//	Player * m_pPlayer;
//	Collision::Direction m_PlDirection;
//
//	std::list<XMFLOAT3> m_PosLog;
//};

class ChasingShadow : public Object
{
public:
	ChasingShadow();
	void Update();
	void InvDraw();
	void Reset();

	bool GetEndFlag();

	void SetPlayer(Player* pPlayer);
	void SetPos(XMFLOAT3 pos);
	void SetEndFlag(bool);

	float GetRadius();

private:
	Player * m_pPlayer;
	Collision::Direction m_PlDirection;
	std::list<XMFLOAT3> m_PosLog;
	bool m_EndFlag;
};

#endif // !_____CHASING_SHADOW_H____
