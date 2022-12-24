//#pragma once

#ifndef _____PLAYER_H____
#define _____PLAYER_H____

#include <DirectXMath.h>
#include "CameraBase.h"
#include "Model.h"
#include "ConstantBuffer.h"
#include "Stage.h"
#include "Collision.h"
#include <vector>
#include "Object.h"

using namespace DirectX;
using namespace std;


class Player : public Object
{
public:
	// プレイヤーの方向
	enum PlayerDirection
	{
		E_PLAYER_RIGHT,	// 右
		E_PLAYER_LEFT,	// 左

		E_PLAYER_DIRECTION_MAX
	};
public:
	Player(Collision::Direction dire);
	void Update();

	void SetPos(XMFLOAT3 pos);

	void InitDirection(int num);

	void ResetMove();


	Object::Info GetOldInfo();
	Collision::Direction GetDirection();
	Collision::Direction GetStageCollistonDirection(int num);
	void SetStageCollisionDirection(Collision::Direction dire, int num);
	void SetDirection(Collision::Direction);


private:
	Object::Info m_OldInfo;
	bool m_Ground;
	XMFLOAT3 m_Move;
	Collision::Direction m_Direction;		//進んでいる方向
	vector<Collision::Direction> m_StageDire;
};

#endif // !_____PLAYER_H____
