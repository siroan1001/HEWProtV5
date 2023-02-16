//#pragma once

#ifndef _____SHADOW_BLOCK_H____
#define _____SHADOW_BLOCK_H____

#include <DirectXMath.h>
//#include "Stage.h"
#include "Object.h"
#include <vector>
#include "Def.h"
#include "ShadowBillBoard.h"

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

	struct SmallBlockTemp
	{
		Def::Info Info;		//�������u���b�N�̏��
		bool use;				//�g���Ă��邩�̃t���O
		float life;
	};

public:
	static void Init();
	static void Uninit();
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
	vector<Def::Info> GetDrawBlock();


private:
	Model* m_pModel;
	XMFLOAT3 m_ModelSize;
	const Def::Info m_BlockBase = { { 999.0f, 999.0f, 0.0f }, { 0.02f, 0.02f, 0.5f }, { 0.0f, 0.0f, 0.0f } };
	//const Billboard::Info m_Billboard = { { 999.0f, 999.0f, 1.0f }, { 0.04f, 0.04f } };
		//�ׂ������ׂ���u���b�N�̏��
	BlockTemp m_BlockInfo;		//�S�̂̏��
	vector<vector<ShadowBlock::SmallBlockTemp>> m_SmallBlockInfo;		//���я���ꏊ�̏��𓮓I�Ɋm��
	static ID3D11ShaderResourceView* m_pTex;
	vector<Def::Info> m_DrawBlock;
	vector<ShadowBillBoard*> m_shadowBill;
};

#endif // !_____SHADOW_BLOCK_H____
