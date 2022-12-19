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
		Stage::Info Info;		//��̏��
		XMFLOAT2 xy;			//�c���̏������u���b�N�̐�
	};

	struct SmallBlockTemp
	{
		Stage::Info Info;		//�������u���b�N�̏��
		bool use;				//�g���Ă��邩�̃t���O
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
		//�ׂ������ׂ���u���b�N�̏��
	

	BlockTemp m_BlockInfo;		//�S�̂̏��
	std::vector<std::vector<SmallBlockTemp>> m_SmallBlockInfo;		//���я���ꏊ�̏��𓮓I�Ɋm��

};

#endif // !_____SHADOW_BLOCK_H____
