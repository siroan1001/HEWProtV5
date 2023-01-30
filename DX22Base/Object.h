#pragma once
#ifndef _____OBJECT_H____
#define _____OBJECT_H____

#include <DirectXMath.h>
#include "CameraBase.h"
#include "Model.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "Def.h"
#include "Lig.h"

using namespace DirectX;

class Object
{
public:
	Object();
	~Object();
	static void Init();
	static void Uninit();
	void Draw();
	static void SetObjColor(XMFLOAT4 color);
	XMFLOAT4 GetColor();

	Def::Info GetInfo();

	void SetCamera(CameraBase*);

	struct ObjCol
	{
		XMFLOAT4 color;
	};
protected:
	Model* m_pModel;
	Def::Info m_Info;
	XMFLOAT3 m_ModelSize;
	CameraBase* m_pCamera;
	static VertexShader* m_pVS;
	static ConstantBuffer* m_pWVP;	
	static PixelShader* m_pPS;
	static ConstantBuffer* m_pBufLight;
	static Lig::Light m_ObjLight;
	static Lig* m_pObjLight;
	static ConstantBuffer* m_pObjColor;
	static ObjCol m_ObjColor;
	XMFLOAT4 m_Color;
};

#endif // !_____OBJECT_H____
