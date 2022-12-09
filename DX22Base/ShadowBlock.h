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
	struct BlockBase
	{
		Stage::Info Info;
		XMFLOAT2 xy;
		bool use;
	};

public:
	ShadowBlock();
	~ShadowBlock();
	void Update();
	void Draw();

	void SetShadowBlock(Stage::Info info);
	void SetUse(int num, bool flag);
	std::vector<BlockBase> GetInfo();


private:
	const Stage::Info m_BlockBase = { { 999.0f, 999.0f, 0.0f }, { 0.02f, 0.02f, 0.5f }, { 0.0f, 0.0f, 0.0f } };
		//�ׂ������ׂ���u���b�N�̏��
	

	BlockBase m_Block;		//�S�̂̏��
	std::vector<BlockBase> m_BlockInfo;		//���я���ꏊ�̏��𓮓I�Ɋm��

};

#endif // !_____SHADOW_BLOCK_H____
