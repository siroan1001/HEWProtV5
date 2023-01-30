#include "ShadowBlock.h"
#include "ShadowBillBoard.h"
#include "Geometory.h"
#include "Modellist.h"
#include "SceneGame.h"
#include "CameraBase.h"
#include "Game3D.h"

using namespace std;

ShadowBlock::ShadowBlock(Def::Info info)
{
	m_BlockInfo.Info.pos = { 999.0f, 999.0f, 0.0f };
	m_BlockInfo.Info.size = { 0.5f, 0.5f, 0.5f };
	m_BlockInfo.Info.rot = { 0.0f, 0.0f, 0.0f };
	m_BlockInfo.xy = { 0.0f, 0.0f };

	m_ModelSize.x = m_ModelSize.y = m_ModelSize.z = 0.1f;
	//モデル読み込み
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_SHADOWBLOCK);

	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);

	m_Color = XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f);

	SetShadowBlock(info);

	m_pCamera = Game3D::GetCamera();
}

ShadowBlock::~ShadowBlock()
{

}

void ShadowBlock::Update()
{
	//for (auto it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	//{
	//	for (auto init = it->begin(); init != it->end(); ++init)
	//	{
	//		init
	//	}
	//}

	for (int i = 0; i < m_SmallBlockInfo.size(); i++)
	{
		for (int j = 0; j < m_SmallBlockInfo[i].size(); j++)
		{
			m_SmallBlockInfo[i][j]->Update();
		}
	}
}

void ShadowBlock::Draw(int i)
{

	//for (auto it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	//{
	//	for (auto init = it->begin(); init != it->end(); ++init)
	//	{
	//		Object::SetObjColor(m_Color);
	//		initDraw();
	//	}
	//}

	//for (int i = 0; i < m_SmallBlockInfo.size(); i++)
	//{
	//	for (int j = 0; j < m_SmallBlockInfo[i].size(); j++)
	//	{
	//		m_SmallBlockInfo[i][j]->ShadowDraw();
	//	}
	//}

	m_SmallBlockInfo[0][0]->ShadowDraw(i);

	//for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	//{
	//	

	//	info = m_BlockBase;
	//	info.pos.y = it->begin()->Info.pos.y;
	//	count = 0;
	//	//info.size.x = 0.0f;
	//	PosL = it->begin()->Info.pos.x + it->begin()->Info.size.x / 2.0f;
	//	std::vector<ShadowBlock::SmallBlockTemp>::iterator end = it->end();		//横列の最後の要素を指す
	//	end--;
	//	for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
	//	{
	//		//if (!Collision::RectAndRect(init->Info, cam->GetInfo()))	continue;

	//		if (init == end)
	//		{
	//			if (count <= 0)
	//			{
	//				continue;
	//			}
	//			info.size.x *= count;
	//			info.pos.x = PosL - info.size.x / 2.0f;
	//			block.push_back(info);
	//		}
	//		else if (init->use)
	//		{
	//			count++;
	//		}
	//		else if(!init->use)
	//		{
	//			if (count <= 0)
	//			{
	//				vector<ShadowBlock::SmallBlockTemp>::iterator next = init;
	//				next++;
	//				PosL = next->Info.pos.x + next->Info.size.x / 2.0f;
	//				continue;
	//			}
	//			else
	//			{
	//				info.size.x *= count;
	//				info.pos.x = PosL - info.size.x / 2.0f;
	//				block.push_back(info);
	//				info = m_BlockBase;
	//				//infoの次を示した場所の左端をposLに入れる
	//				vector<ShadowBlock::SmallBlockTemp>::iterator next = init;
	//				info.pos.y = it->begin()->Info.pos.y;
	//				next++;
	//				PosL = next->Info.pos.x + next->Info.size.x / 2.0f;
	//				count = 0;
	//			}
	//		}
	//	}
	//}

	//for (vector<Def::Info>::iterator it = block.begin(); it != block.end(); ++it)
	//{
	//	SetGeometoryTranslate(it->pos.x, it->pos.y, it->pos.z);
	//	SetGeometoryScaling(it->size.x, it->size.y, it->size.z);
	//	SetGeometoryRotation(it->rot.x, it->rot.y, it->rot.z);
	//	SetGeometoryColor(XMFLOAT4(0.0f, 0.0f, 10.0f, 1.0f));
	//	DrawBox();
	//}

	//for (auto it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	//{
	//	for (auto init = it->begin(); init != it->end(); ++init)
	//	{
	//		Object::SetObjColor(m_Color);
	//		Object::Draw();
	//	}
	//}

	//for (int i = 0; i < m_BillBoard.size(); i++)
	//{
	//	for (int j = 0; j < m_BillBoard[i].size(); j++)
	//	{
	//		m_BillBoard[i][j]->Draw();
	//	}
	//}
}

void ShadowBlock::Reset()
{
	for (int i = 0; i < m_SmallBlockInfo.size(); i++)
	{
		for (int j = 0; j < m_SmallBlockInfo[i].size(); j++)
		{
			m_SmallBlockInfo[i][j]->Reset();
		}
	}
}

void ShadowBlock::SetShadowBlock(Def::Info info)
{
	m_BlockInfo.Info = info;
	m_BlockInfo.xy.x = m_BlockInfo.Info.size.x / m_BlockBase.size.x;
	m_BlockInfo.xy.y = m_BlockInfo.Info.size.y / m_BlockBase.size.y;

	for (int i = 0; i < m_BlockInfo.xy.y; i++)
	{
		std::vector<SmallShadowBlock*> tempVec;
		//vector<ShadowBillBoard*> tempb;

		for (int j = 0; j < m_BlockInfo.xy.x; j++)
		{
			SmallShadowBlock* temp;
			Def::Info info = m_BlockBase;
			
			info.pos = { m_BlockInfo.Info.pos.x - m_BlockBase.size.x * j, m_BlockInfo.Info.pos.y - m_BlockBase.size.y * i, m_BlockInfo.Info.pos.z };//ブロックのサイズ分ずらす
			temp = new SmallShadowBlock(info);

			tempVec.push_back(temp);

		}
		m_SmallBlockInfo.push_back(tempVec);
	}

	m_BlockInfo.Info.pos.x += m_BlockBase.size.x / 2.0f;
	m_BlockInfo.Info.pos.y += m_BlockBase.size.y / 2.0f;

	XMFLOAT2 size = { m_BlockInfo.xy.x * m_BlockBase.size.x, m_BlockInfo.xy.y * m_BlockBase.size.y };
	m_BlockInfo.Info.pos.x -= size.x / 2.0f;
	m_BlockInfo.Info.pos.y -= size.y / 2.0f;
}

void ShadowBlock::SetUse(XMFLOAT2 num, bool flag)
{
	m_SmallBlockInfo[num.y][num.x]->SetUse(flag);
}

std::vector<std::vector<SmallShadowBlock*>> ShadowBlock::GetSmallBlockInfo()
{
	return m_SmallBlockInfo;
}

int ShadowBlock::GetNum()
{
	int num = 0;

	for (auto it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		num += it->size();
	}
	return num;
}

Def::Info ShadowBlock::GetInfo()
{
	return m_BlockInfo.Info;
}

