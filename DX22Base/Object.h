#pragma once
#ifndef _____OBJECT_H____
#define _____OBJECT_H____

#include <DirectXMath.h>

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
};

#endif // !_____OBJECT_H____
