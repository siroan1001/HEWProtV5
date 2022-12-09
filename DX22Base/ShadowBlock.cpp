#include "ShadowBlock.h"

ShadowBlock::ShadowBlock()
{
	m_Block.Info.pos = { 999.0f, 999.0f, 0.0f };
	m_Block.Info.size = { 0.5f, 0.5f, 0.5f };
	m_Block.Info.rot = { 0.0f, 0.0f, 0.0f };
	m_Block.xy = { 0.0f, 0.0f };
	m_Block.use = false;
}

ShadowBlock::~ShadowBlock()
{
}

void ShadowBlock::Update()
{
}

void ShadowBlock::Draw()
{
	for (int i = 0; i < m_BlockInfo.size(); i++)
	{
		if (!m_BlockInfo[i].use)	continue;

		SetGeometoryTranslate(m_BlockInfo[i].Info.pos.x, m_BlockInfo[i].Info.pos.y, m_BlockInfo[i].Info.pos.z);
		SetGeometoryScaling(m_BlockInfo[i].Info.size.x, m_BlockInfo[i].Info.size.y, m_BlockInfo[i].Info.size.z);
		SetGeometoryRotation(m_BlockInfo[i].Info.rot.x, m_BlockInfo[i].Info.rot.y, m_BlockInfo[i].Info.rot.z);
		DrawBox();
	}
}

void ShadowBlock::SetShadowBlock(Stage::Info info)
{
	m_Block.Info = info;
	m_Block.xy.x = m_Block.Info.size.x / m_BlockBase.size.x;
	m_Block.xy.y = m_Block.Info.size.y / m_BlockBase.size.y;

	for (int i = 0; i < m_Block.xy.y; i++)
	{
		for (int j = 0; j < m_Block.xy.x; j++)
		{
			BlockBase temp = { m_BlockBase, {(float)j, (float)i} };
			temp.Info.pos = { m_Block.Info.pos.x - m_BlockBase.size.x * j, m_Block.Info.pos.y - m_BlockBase.size.y * i, m_Block.Info.pos.z };//ブロックのサイズ分ずらす
			temp.use = true;
			m_BlockInfo.push_back(temp);
		}
	}

	m_Block.Info.pos.x = m_Block.Info.pos.x + m_BlockInfo[0].Info.size.x / 2.0f;
	m_Block.Info.pos.y = m_Block.Info.pos.y + m_BlockInfo[0].Info.size.y / 2.0f;
	m_Block.use = true;
}

void ShadowBlock::SetUse(int num, bool flag)
{
	m_BlockInfo[num].use = flag;
}

std::vector<ShadowBlock::BlockBase> ShadowBlock::GetInfo()
{
	return m_BlockInfo;
}

