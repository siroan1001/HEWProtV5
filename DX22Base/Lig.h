#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class Lig
{
public:
	struct Light
	{
		XMFLOAT3 spPos;
		float pad3;
		XMFLOAT3 spCol;
		float spRange;
		XMFLOAT3 spDir;
		float spAng;
		XMFLOAT3 eyePos;
		float pad4;
		XMFLOAT3 amCol;
		float pad5;
	};
	void InitSpLig(Light& light);
	void InitAmLig(Light& light);
};
