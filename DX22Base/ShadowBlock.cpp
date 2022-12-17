#include "ShadowBlock.h"

using namespace std;

ShadowBlock::ShadowBlock()
{
	m_BlockInfo.Info.pos = { 999.0f, 999.0f, 0.0f };
	m_BlockInfo.Info.size = { 0.5f, 0.5f, 0.5f };
	m_BlockInfo.Info.rot = { 0.0f, 0.0f, 0.0f };
	m_BlockInfo.xy = { 0.0f, 0.0f };
}

ShadowBlock::~ShadowBlock()
{
}

void ShadowBlock::Update()
{
	for (std::vector<std::vector<SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		for (std::vector<SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			if (init->life >= 30.0f)	continue;

			init->life += 0.04f;
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
	//for (int i = 0; i < m_BlockInfo.size(); i++)
	//{


	//	if (!m_BlockInfo[i].use)	continue;

	//	SetGeometoryTranslate(m_BlockInfo[i].Info.pos.x, m_BlockInfo[i].Info.pos.y, m_BlockInfo[i].Info.pos.z);
	//	SetGeometoryScaling(m_BlockInfo[i].Info.size.x, m_BlockInfo[i].Info.size.y, m_BlockInfo[i].Info.size.z);
	//	SetGeometoryRotation(m_BlockInfo[i].Info.rot.x, m_BlockInfo[i].Info.rot.y, m_BlockInfo[i].Info.rot.z);
	//	DrawBox();
	//}

	vector<Stage::Info>	block;
	Stage::Info info;
	float PosL;

	for (std::vector<std::vector<SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		info = it->begin()->Info;
		PosL = info.pos.x + info.size.x / 2.0f;
		std::vector<SmallBlockTemp>::iterator end = it->end();
		end--;
		for (std::vector<SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			if (!init->use || init == end)
			{
				block.push_back(info);
				
				if (init == end)
				{
					break;
				}
				else
				{
					std::vector<SmallBlockTemp>::iterator next = init;
					next++;
					while (!next->use)
					{
						next++;
					}
					info = next->Info;
					PosL = info.pos.x + info.size.x / 2.0f;
					next--;
					init = next;
					if (init == end)
					{
						break;
					}
					continue;
				}
			}

			info.size.x += init->Info.size.x;
			info.pos.x = PosL - info.size.x / 2.0f;
		}
	}

	for (vector<Stage::Info>::iterator it = block.begin(); it != block.end(); ++it)
	{
		SetGeometoryTranslate(it->pos.x, it->pos.y, it->pos.z);
		SetGeometoryScaling(it->size.x, it->size.y, it->size.z);
		SetGeometoryRotation(it->rot.x, it->rot.y, it->rot.z);
		DrawBox();
	}

	//for (std::vector<std::vector<SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	//{
	//	for (std::vector<SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
	//	{
	//		if (!init->use)	continue;

	//		SetGeometoryTranslate(init->Info.pos.x, init->Info.pos.y, init->Info.pos.z);
	//		SetGeometoryScaling(init->Info.size.x, init->Info.size.x, init->Info.size.z);
	//		SetGeometoryRotation(init->Info.rot.x, init->Info.rot.y, init->Info.rot.z);
	//		DrawBox();
	//	}
	//}
}

void ShadowBlock::SetShadowBlock(Stage::Info info)
{
	m_BlockInfo.Info = info;
	m_BlockInfo.xy.x = m_BlockInfo.Info.size.x / m_BlockBase.size.x;
	m_BlockInfo.xy.y = m_BlockInfo.Info.size.y / m_BlockBase.size.y;

	for (int i = 0; i < m_BlockInfo.xy.y; i++)
	{
		std::vector<SmallBlockTemp> tempVec;

		for (int j = 0; j < m_BlockInfo.xy.x; j++)
		{
			SmallBlockTemp temp = { m_BlockBase, true, 30.0f};
			temp.Info.pos = { m_BlockInfo.Info.pos.x - m_BlockBase.size.x * j, m_BlockInfo.Info.pos.y - m_BlockBase.size.y * i, m_BlockInfo.Info.pos.z };//ブロックのサイズ分ずらす
			//m_SmallBlockInfo[i].push_back(temp);
			tempVec.push_back(temp);
		}
		m_SmallBlockInfo.push_back(tempVec);
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

	for (std::vector<std::vector<SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		num += it->size();
	}
	return num;
}

