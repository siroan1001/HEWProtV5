//#pragma once

#ifndef _____SHADOW_BLOCK_H____
#define _____SHADOW_BLOCK_H____

#include <DirectXMath.h>
//#include "Stage.h"
#include "Object.h"
#include <vector>
#include "Def.h"
#include "SmallShadowBlock.h"
//#include "ShadowBillBoard.h"

using namespace DirectX;
using namespace std;

class ShadowBlock : public Object
{
public:
	struct BlockTemp
	{
		Def::Info Info;		//��̏��
		XMFLOAT2 xy;			//�c���̏������u���b�N�̐�
	};

	//struct SmallBlockTemp
	//{
	//	Def::Info Info;		//�������u���b�N�̏��
	//	bool use;				//�g���Ă��邩�̃t���O
	//	float life;
	//	Model* pModel;
	//};

public:
	ShadowBlock(Def::Info info);
	~ShadowBlock();
	void Update();
	void Draw(int);

	void Reset();

	void SetShadowBlock(Def::Info info);
	void SetUse(XMFLOAT2 num, bool flag);
	std::vector<std::vector<SmallShadowBlock*>> GetSmallBlockInfo();
	int GetNum();
	Def::Info GetInfo();


private:
	XMFLOAT3 m_ModelSize;
	const Def::Info m_BlockBase = { { 999.0f, 999.0f, 0.0f }, { 0.03f, 0.03f, 0.5f }, { 0.0f, 0.0f, 0.0f } };
		//�ׂ������ׂ���u���b�N�̏��
	BlockTemp m_BlockInfo;		//�S�̂̏��
	vector<vector<SmallShadowBlock*>> m_SmallBlockInfo;		//���я���ꏊ�̏��𓮓I�Ɋm��
};

#endif // !_____SHADOW_BLOCK_H____
