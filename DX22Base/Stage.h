//#pragma once

#ifndef _____STAGE_H____
#define _____STAGE_H____

#include <DirectXMath.h>
#include "Geometory.h"
#include <vector>
#include "ShadowBlock.h"
#include "Object.h"

using namespace DirectX;
using namespace std;

//class ShadowBlock;

class Stage
{
public:
	Stage();
	~Stage();
	void Draw();

	Def::Info GetInfo(int num);
	int GetStageNum();
	int GetShadowNum();
	vector<ShadowBlock*> GetShadowBlock();

protected:
	//Info* m_pBlocks;
	vector<ShadowBlock*> m_Shadow;
	int m_blockNum;
	vector<Def::Info> m_Info;
};

#endif // !_____STAGE_H____
