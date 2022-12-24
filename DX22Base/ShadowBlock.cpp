#include "ShadowBlock.h"
#include "ShadowBillBoard.h"
#include "Geometory.h"

using namespace std;

ShadowBlock::ShadowBlock(Object::Info info)
{
	m_BlockInfo.Info.pos = { 999.0f, 999.0f, 0.0f };
	m_BlockInfo.Info.size = { 0.5f, 0.5f, 0.5f };
	m_BlockInfo.Info.rot = { 0.0f, 0.0f, 0.0f };
	m_BlockInfo.xy = { 0.0f, 0.0f };

	SetShadowBlock(info);
}

ShadowBlock::~ShadowBlock()
{

}

void ShadowBlock::Update()
{
	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			if (init->life >= 30.0f)	continue;

			init->life += 0.1f;
			if (init->life >= 30.0f)
			{
				init->life = 30.0f;
				init->use = true;
			}

		}
	}
}

void ShadowBlock::Draw()
{
	vector<Object::Info>	block;		//描画用のデータを格納
	Object::Info info;		//計算用
	float PosL;		//ブロックの左端を示す
	int count;

	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		info = m_BlockBase;
		info.pos.y = it->begin()->Info.pos.y;
		count = 0;
		//info.size.x = 0.0f;
		PosL = it->begin()->Info.pos.x + it->begin()->Info.size.x / 2.0f;
		std::vector<ShadowBlock::SmallBlockTemp>::iterator end = it->end();		//横列の最後の要素を指す
		end--;
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			if (init == end)
			{
				if (count <= 0)
				{
					continue;
				}
				info.size.x *= count;
				info.pos.x = PosL - info.size.x / 2.0f;
				block.push_back(info);
			}
			else if (init->use)
			{
				count++;
			}
			else if(!init->use)
			{
				if (count <= 0)
				{
					vector<ShadowBlock::SmallBlockTemp>::iterator next = init;
					next++;
					PosL = next->Info.pos.x + next->Info.size.x / 2.0f;
					continue;
				}
				else
				{
					info.size.x *= count;
					info.pos.x = PosL - info.size.x / 2.0f;
					block.push_back(info);
					info = m_BlockBase;
					//infoの次を示した場所の左端をposLに入れる
					vector<ShadowBlock::SmallBlockTemp>::iterator next = init;
					info.pos.y = it->begin()->Info.pos.y;
					next++;
					PosL = next->Info.pos.x + next->Info.size.x / 2.0f;
					count = 0;
				}
			}
		}
	}

	for (vector<Object::Info>::iterator it = block.begin(); it != block.end(); ++it)
	{
		SetGeometoryTranslate(it->pos.x, it->pos.y, it->pos.z);
		SetGeometoryScaling(it->size.x, it->size.y, it->size.z);
		SetGeometoryRotation(it->rot.x, it->rot.y, it->rot.z);
		DrawBox();
	}

	//for (int i = 0; i < m_BillBoard.size(); i++)
	//{
	//	for (int j = 0; j < m_BillBoard[i].size(); j++)
	//	{
	//		m_BillBoard[i][j]->Draw();
	//	}
	//}
}

void ShadowBlock::SetShadowBlock(Object::Info info)
{
	m_BlockInfo.Info = info;
	m_BlockInfo.xy.x = m_BlockInfo.Info.size.x / m_BlockBase.size.x;
	m_BlockInfo.xy.y = m_BlockInfo.Info.size.y / m_BlockBase.size.y;

	for (int i = 0; i < m_BlockInfo.xy.y; i++)
	{
		std::vector<ShadowBlock::SmallBlockTemp> tempVec;
		//vector<ShadowBillBoard*> tempb;

		for (int j = 0; j < m_BlockInfo.xy.x; j++)
		{
			ShadowBlock::SmallBlockTemp temp = { m_BlockBase, true, 30.0f};
			temp.Info.pos = { m_BlockInfo.Info.pos.x - m_BlockBase.size.x * j, m_BlockInfo.Info.pos.y - m_BlockBase.size.y * i, m_BlockInfo.Info.pos.z };//ブロックのサイズ分ずらす

			tempVec.push_back(temp);
			//tempb.push_back(new ShadowBillBoard(temp.Info.pos));
		}
		m_SmallBlockInfo.push_back(tempVec);
		//m_BillBoard.push_back(tempb);
	}

	

	//m_BlockInfo.Info.pos.x = m_BlockInfo.Info.pos.x + m_SmallBlockInfo[0].Info.size.x / 2.0f;
	//m_BlockInfo.Info.pos.y = m_BlockInfo.Info.pos.y + m_SmallBlockInfo[0].Info.size.y / 2.0f;
}

void ShadowBlock::SetUse(XMFLOAT2 num, bool flag)
{
	m_SmallBlockInfo[num.y][num.x].use = flag;
}

std::vector<std::vector<ShadowBlock::SmallBlockTemp>>* ShadowBlock::GetInfo()
{
	return &m_SmallBlockInfo;
}

int ShadowBlock::GetNum()
{
	int num = 0;

	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		num += it->size();
	}
	return num;
}

