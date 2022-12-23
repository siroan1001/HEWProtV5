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

using namespace DirectX;
using namespace std;


class Player
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
	~Player();
	void Update();
	void Draw();

	void SetCamera(CameraBase* pCamera);
	void SetPos(XMFLOAT3 pos);

	void InitDirection(int num);

	void ResetMove();

	//XMFLOAT3 GetPos();
	Object::Info GetInfo();
	Object::Info GetOldInfo();
	Collision::Direction GetDirection();
	Collision::Direction GetStageCollistonDirection(int num);
	void SetStageCollisionDirection(Collision::Direction dire, int num);
	void SetDirection(Collision::Direction);


private:
	CameraBase* m_pCamera;
	//XMFLOAT3 m_Pos;
	//XMFLOAT3 m_Rot;
	Object::Info m_Info;
	Object::Info m_OldInfo;
	Model* m_pModel;
	VertexShader* m_pVS;
	ConstantBuffer* m_pWVP;
	bool m_Ground;
	XMFLOAT3 m_Move;
	Collision::Direction m_Direction;		//進んでいる方向
	vector<Collision::Direction> m_StageDire;
};

#endif // !_____PLAYER_H____
