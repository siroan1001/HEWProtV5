//#pragma once

#ifndef _____STAGE_H____
#define _____STAGE_H____

#include <DirectXMath.h>
#include "Geometory.h"

using namespace DirectX;

class Stage
{
public:
	struct Info
	{
		XMFLOAT3 pos;
		XMFLOAT3 size;
		XMFLOAT3 rot;
	};
public:
	Stage();
	~Stage();
	void Draw();

	Info GetInfo(int num);
	int GetNum();

protected:
	Info* m_pBlocks;
	int m_blockNum;
};

#endif // !_____STAGE_H____
