//#pragma once

#ifndef _____SHADOW_BLOCK_H____
#define _____SHADOW_BLOCK_H____

#include <DirectXMath.h>
//#include "Stage.h"
#include "Object.h"
#include <vector>
#include "Def.h"
//#include "ShadowBillBoard.h"

using namespace DirectX;
using namespace std;

class ShadowBlock : public Object
{
public:
	struct BlockTemp
	{
		Def::Info Info;		//塊の情報
		XMFLOAT2 xy;			//縦横の小さいブロックの数
	};

	struct SmallBlockTemp
	{
		Def::Info Info;		//小さいブロックの情報
		bool use;				//使っているかのフラグ
		float life;
	};

public:
	ShadowBlock(Def::Info info);
	~ShadowBlock();
	void Update();
	void Draw();

	void Reset();

	void SetShadowBlock(Def::Info info);
	void SetUse(XMFLOAT2 num, bool flag);
	std::vector<std::vector<SmallBlockTemp>>* GetSmallBlockInfo();
	int GetNum();
	Def::Info GetInfo();


private:
	Model* m_pModel;
	XMFLOAT3 m_ModelSize;
	const Def::Info m_BlockBase = { { 999.0f, 999.0f, 0.0f }, { 0.02f, 0.02f, 0.5f }, { 0.0f, 0.0f, 0.0f } };
	//const Billboard::Info m_Billboard = { { 999.0f, 999.0f, 1.0f }, { 0.04f, 0.04f } };
		//細かく並べられるブロックの情報
	BlockTemp m_BlockInfo;		//全体の情報
	vector<vector<ShadowBlock::SmallBlockTemp>> m_SmallBlockInfo;		//並び順や場所の情報を動的に確保
};

#endif // !_____SHADOW_BLOCK_H____
