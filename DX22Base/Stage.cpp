#include "Stage.h"
#include <vector>
#include "Input.h"

Stage::Stage()
	:m_pBlocks(nullptr), m_blockNum(4)
{
	m_pBlocks = new Info[m_blockNum];

	m_pBlocks[0].pos = { 0.0f, -1.5f, 0.0f };
	m_pBlocks[0].size = { 9.0f, 1.0f, 0.5f };
	m_pBlocks[0].rot = { 0.0f, 0.0f, 0.0f };

	m_pBlocks[1].pos = { -2.0f, -0.25f, 0.0f };
	m_pBlocks[1].size = { 2.0f, 1.5f, 0.5f };
	m_pBlocks[1].rot = { 0.0f, 0.0f, 0.0f };

	m_pBlocks[2].pos = { -3.75f, 0.0f, 0.0f };
	m_pBlocks[2].size = { 1.5f, 2.0f, 0.5f };
	m_pBlocks[2].rot = { 0.0f, 0.0f, 0.0f };

	m_pBlocks[3].pos = { 1.0f, 0.8f, 0.0f };
	m_pBlocks[3].size = { 0.5f, 0.2f, 0.3f };
	m_pBlocks[3].rot = { 0.0f, 0.0f, 0.0f };
}

Stage::~Stage()
{
	delete[] m_pBlocks;
}

void Stage::Draw()
{
	for (int i = 0; i < m_blockNum; ++i)
	{
		SetGeometoryTranslate(m_pBlocks[i].pos.x, m_pBlocks[i].pos.y, m_pBlocks[i].pos.z);
		SetGeometoryScaling(m_pBlocks[i].size.x, m_pBlocks[i].size.y, m_pBlocks[i].size.z);
		SetGeometoryRotation(m_pBlocks[i].rot.x, m_pBlocks[i].rot.y, m_pBlocks[i].rot.z);
		DrawBox();
	}
}

Stage::Info Stage::GetInfo(int num)
{
	return m_pBlocks[num];
}

int Stage::GetNum()
{
	return m_blockNum;
}
