#include "Stage.h"
#include <vector>
#include "Input.h"

Stage::Stage()
	:m_pBlocks(nullptr), m_blockNum(3)
{
	m_pBlocks = new Info[m_blockNum];

	//m_pBlocks[0].pos = { 0.0f, -2.0f, 0.0f };
	//m_pBlocks[0].size = { 9.0f, 1.0f, 8.0f };
	//m_pBlocks[0].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[1].pos = { -3.5f, -1.0f, 0.0f };
	//m_pBlocks[1].size = { 2.0f, 1.0f, 4.0f };
	//m_pBlocks[1].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[2].pos = { -3.5f, -0.5f, -3.0f };
	//m_pBlocks[2].size = { 2.0f, 2.0f, 2.0f };
	//m_pBlocks[2].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[3].pos = { 1.0f, -0.5f, -2.0f };
	//m_pBlocks[3].size = { 7.0f, 2.0f, 4.0f };
	//m_pBlocks[3].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[4].pos = { 1.5f, 0.0f, -5.5f };
	//m_pBlocks[4].size = { 6.0f, 5.0f, 3.0f };
	//m_pBlocks[4].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[5].pos = { 3.5f, 0.5f, -4.0f };
	//m_pBlocks[5].size = { 2.0f, (float)sqrt(2.0f * 2.0f + 2.0f * 2.0f), (float)sqrt(2.0f * 2.0f + 2.0f * 2.0f) };
	//m_pBlocks[5].rot = { XMConvertToRadians(45.0f), 0.0f, 0.0f };

	//m_pBlocks[6].pos = { -3.0f, 1.0f, -5.5f };
	//m_pBlocks[6].size = { 1.0f, 1.0f, 1.0f };
	//m_pBlocks[6].rot = { 0.0f, 0.0f, 0.0f };
	//m_pBlocks[0].pos = { 0.0f, -2.0f, 0.0f };
	//m_pBlocks[0].size = { 9.0f, 1.0f, 8.0f };
	//m_pBlocks[0].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[1].pos = { -3.5f, -1.0f, 0.0f };
	//m_pBlocks[1].size = { 2.0f, 1.0f, 4.0f };
	//m_pBlocks[1].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[2].pos = { -3.5f, -0.5f, -3.0f };
	//m_pBlocks[2].size = { 2.0f, 2.0f, 2.0f };
	//m_pBlocks[2].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[3].pos = { 1.0f, -0.5f, -2.0f };
	//m_pBlocks[3].size = { 7.0f, 2.0f, 4.0f };
	//m_pBlocks[3].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[4].pos = { 1.5f, 0.0f, -5.5f };
	//m_pBlocks[4].size = { 6.0f, 5.0f, 3.0f };
	//m_pBlocks[4].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[5].pos = { 3.5f, 0.5f, -4.0f };
	//m_pBlocks[5].size = { 2.0f, (float)sqrt(2.0f * 2.0f + 2.0f * 2.0f), (float)sqrt(2.0f * 2.0f + 2.0f * 2.0f) };
	//m_pBlocks[5].rot = { XMConvertToRadians(45.0f), 0.0f, 0.0f };

	//m_pBlocks[6].pos = { -3.0f, 1.0f, -5.5f };
	//m_pBlocks[6].size = { 1.0f, 1.0f, 1.0f };
	//m_pBlocks[6].rot = { 0.0f, 0.0f, 0.0f };

	m_pBlocks[0].pos = { 0.0f, -1.5f, 0.0f };
	m_pBlocks[0].size = { 9.0f, 1.0f, 0.5f };
	m_pBlocks[0].rot = { 0.0f, 0.0f, 0.0f };

	m_pBlocks[1].pos = { 0.0f, -1.0f, 0.0f };
	m_pBlocks[1].size = { 2.0f, 1.0f, 1.0f };
	m_pBlocks[1].rot = { 0.0f, 0.0f, 0.0f };

	m_pBlocks[2].pos = { -3.5f, -0.5f, -3.0f };
	m_pBlocks[2].size = { 2.0f, 2.0f, 2.0f };
	m_pBlocks[2].rot = { 0.0f, 0.0f, 0.0f };

	//std::vector<std::vector<int>> hoge;
	//std::vector<int> fuga;
	//fuga.push_back(1);
	//fuga.push_back(12);
	//fuga.push_back(123);
	//hoge.push_back(fuga);
}

Stage::~Stage()
{
	delete[] m_pBlocks;
}

void Stage::Draw()
{
	//if (IsKeyPress('D'))	m_pBlocks[1].pos.x -= 0.1f;
	//if (IsKeyPress('A'))	m_pBlocks[1].pos.x += 0.1f;

	for (int i = 0; i < 1/*m_blockNum*/; ++i)
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
