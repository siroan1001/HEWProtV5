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

struct ShadowInfo
{
	ShadowBlock* info;
	bool flag;
};
struct StageInfo
{
	Def::Info info;
	bool flag;
};

class Stage
{
public:
	Stage();
	~Stage();
	void Update();
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
