//#pragma once

#ifndef _____SHADOW_BLOCK_H____
#define _____SHADOW_BLOCK_H____

#include <DirectXMath.h>
#include "Stage.h"
#include <vector>

using namespace DirectX;

class ShadowBlock
{
public:
	struct BlockTemp
	{
		Stage::Info Info;		//塊の情報
		XMFLOAT2 xy;			//縦横の小さいブロックの数
	};

	struct SmallBlockTemp
	{
		Stage::Info Info;		//小さいブロックの情報
		bool use;				//使っているかのフラグ
		float life;
	};

public:
	ShadowBlock();
	~ShadowBlock();
	void Update();
	void Draw();

	void SetShadowBlock(Stage::Info info);
	void SetUse(XMFLOAT2 num, bool flag);
	std::vector<std::vector<SmallBlockTemp>>* GetInfo();
	int GetNum();


private:
	const Stage::Info m_BlockBase = { { 999.0f, 999.0f, 0.0f }, { 0.02f, 0.02f, 0.5f }, { 0.0f, 0.0f, 0.0f } };
		//細かく並べられるブロックの情報
	

	BlockTemp m_BlockInfo;		//全体の情報
	std::vector<std::vector<SmallBlockTemp>> m_SmallBlockInfo;		//並び順や場所の情報を動的に確保

};

#endif // !_____SHADOW_BLOCK_H____
