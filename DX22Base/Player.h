//#pragma once

#ifndef _____PLAYER_H____
#define _____PLAYER_H____

#include <DirectXMath.h>
#include "CameraBase.h"
#include "Model.h"
#include "ConstantBuffer.h"
#include "Stage.h"

using namespace DirectX;


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
	Player();
	~Player();
	void Update();
	void Draw();

	void SetCamera(CameraBase* pCamera);
	XMFLOAT3 GetPos();

private:
	CameraBase* m_pCamera;
	XMFLOAT3 m_Pos;
	XMFLOAT3 m_Rot;
	Stage::Info m_Info;
	Model* m_pModel;
	VertexShader* m_pVS;
	ConstantBuffer* m_pWVP;
	bool m_Ground;
	XMFLOAT3 m_Move;

};

#endif // !_____PLAYER_H____
