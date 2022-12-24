//#pragma once

#ifndef _____SHADOW_BLOCK_H____
#define _____SHADOW_BLOCK_H____

#include <DirectXMath.h>
//#include "Stage.h"
#include "Object.h"
#include <vector>
//#include "ShadowBillBoard.h"

using namespace DirectX;
using namespace std;

class ShadowBlock
{
public:
	struct BlockTemp
	{
		Object::Info Info;		//��̏��
		XMFLOAT2 xy;			//�c���̏������u���b�N�̐�
	};

	struct SmallBlockTemp
	{
		Object::Info Info;		//�������u���b�N�̏��
		bool use;				//�g���Ă��邩�̃t���O
		float life;
	};

public:
	ShadowBlock(Object::Info info);
	~ShadowBlock();
	void Update();
	void Draw();

	void SetShadowBlock(Object::Info info);
	void SetUse(XMFLOAT2 num, bool flag);
	std::vector<std::vector<SmallBlockTemp>>* GetInfo();
	int GetNum();


private:
	const Object::Info m_BlockBase = { { 999.0f, 999.0f, 0.0f }, { 0.02f, 0.02f, 0.5f }, { 0.0f, 0.0f, 0.0f } };
	//const Billboard::Info m_Billboard = { { 999.0f, 999.0f, 1.0f }, { 0.04f, 0.04f } };
		//�ׂ������ׂ���u���b�N�̏��
	BlockTemp m_BlockInfo;		//�S�̂̏��
	vector<vector<ShadowBlock::SmallBlockTemp>> m_SmallBlockInfo;		//���я���ꏊ�̏��𓮓I�Ɋm��
};

#endif // !_____SHADOW_BLOCK_H____
