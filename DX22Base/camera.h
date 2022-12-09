//#pragma once

#ifndef _____CAMERA_H____
#define _____CAMERA_H____

#include "DirectXMath.h"

class Camera
{
public:
	Camera();
	~Camera();
	void Update();
	//void Draw();

	DirectX::XMFLOAT3 GetPos();
private:
	DirectX::XMFLOAT3 m_Pos;

};

#endif // !_____CAMERA_H____
