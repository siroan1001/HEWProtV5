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
#include "Game3D.h"
#include "SceneGame.h"

using namespace DirectX;
using namespace std;

const float PLAYER_MOVE_NORMAL = 0.02f;

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

	void Reset();

	Def::Info GetOldInfo();
	Collision::Direction GetDirection();
	Collision::Direction GetStageCollistonDirection(int num);
	void SetStageCollisionDirection(Collision::Direction dire, int num);
	void SetDirection(Collision::Direction);
	void SetCollisionEnemy();


private:
	Def::Info m_OldInfo;
	bool m_Ground;
	XMFLOAT3 m_Move;
	Collision::Direction m_Direction;		//進んでいる方向
	vector<Collision::Direction> m_StageDire;
	float m_Spead;
	bool m_IsColEnemy;
};

#endif // !_____PLAYER_H____
