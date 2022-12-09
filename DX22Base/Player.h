//#pragma once

#ifndef _____PLAYER_H____
#define _____PLAYER_H____

#include <DirectXMath.h>
#include "CameraBase.h"
#include "Model.h"
#include "ConstantBuffer.h"

using namespace DirectX;

class Player
{
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
	Model* m_pModel;
	VertexShader* m_pVS;
	ConstantBuffer* m_pWVP;
	bool m_Ground;
	XMFLOAT3 m_Move;

};

#endif // !_____PLAYER_H____
