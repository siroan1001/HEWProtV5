#pragma once
#ifndef _____OBJECT_H____
#define _____OBJECT_H____

#include <DirectXMath.h>
#include "CameraBase.h"
#include "Model.h"
#include "Shader.h"
#include "ConstantBuffer.h"

using namespace DirectX;

class Object
{
public:
	struct Info
	{
		XMFLOAT3 pos;
		XMFLOAT3 size;
		XMFLOAT3 rot;
	};

public:
	Object();
	~Object();
	static void Init();
	static void Uninit();
	void Draw();

	Info GetInfo();

	void SetCamera(CameraBase*);

protected:
	Model* m_pModel;
	Info m_Info;
	CameraBase* m_pCamera;
	static VertexShader* m_pVS;
	static ConstantBuffer* m_pWVP;	

};

#endif // !_____OBJECT_H____
