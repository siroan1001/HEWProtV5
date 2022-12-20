#include "Stage.h"
#include <vector>
#include "Input.h"

Stage::Stage()
	:m_pBlocks(nullptr), m_blockNum(11)
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

	//床(下)
	m_pBlocks[0].pos = { 3.8f, -2.5f, 0.0f };
	m_pBlocks[0].size = { 20.5f, 0.5f, 0.5f };
	m_pBlocks[0].rot = { 0.0f, 0.0f, 0.0f };

	//m_pBlocks[1].size = { 0.5f, 1.0f, 0.5f };
	//m_pBlocks[1].pos = { 2.0f, -1.0f + m_pBlocks[1].size.y / 2.0f, 0.0f };
	//m_pBlocks[1].rot = { 0.0f, 0.0f, 0.0f };

	//床(真ん中)
	m_pBlocks[1].pos = { 1.7f, 0.2f, 0.0f };
	m_pBlocks[1].size = { 10.9f, 0.5f, 0.5f };
	m_pBlocks[1].rot = { 0.0f, 0.0f, 0.0f };

	//床(上)
	m_pBlocks[2].pos = { -2.2f, 3.0f, 0.0f };
	m_pBlocks[2].size = { 13.5f, 0.5f, 0.5f };
	m_pBlocks[2].rot = { 0.0f, 0.0f, 0.0f };

	//壁(左)
	m_pBlocks[3].pos = { -6.2f, 0.35f, 0.0f };
	m_pBlocks[3].size = { 0.5f, 5.7f, 0.5f };
	m_pBlocks[3].rot = { 0.0f, 0.0f, 0.0f };

	//壁(右)
	m_pBlocks[4].pos = { 6.9f, 2.9f, 0.0f };
	m_pBlocks[4].size = { 0.5f, 5.0f, 0.5f };
	m_pBlocks[4].rot = { 0.0f, 0.0f, 0.0f };

	//オブジェクト1(上)
	m_pBlocks[5].pos = { -2.0f, 3.75f, 0.0f };
	m_pBlocks[5].size = { 1.0f, 1.0f, 0.5f };
	m_pBlocks[5].rot = { 0.0f, 0.0f, 0.0f };

	//オブジェクト2(上)
	m_pBlocks[6].pos = { 0.7f, 3.75f, 0.0f };
	m_pBlocks[6].size = { 1.0f, 1.0f, 0.5f };
	m_pBlocks[6].rot = { 0.0f, 0.0f, 0.0f };

	//オブジェクト3(真ん中)
	m_pBlocks[7].pos = {  0.0f, 0.95f, 0.0f };
	m_pBlocks[7].size = { 3.0f, 1.0f, 0.5f };
	m_pBlocks[7].rot = { 0.0f, 0.0f, 0.0f };

	//オブジェクト4(下)
	m_pBlocks[8].pos = { -0.7f, -1.75f, 0.0f };
	m_pBlocks[8].size = { 3.0f, 1.0f, 0.5f };
	m_pBlocks[8].rot = { 0.0f, 0.0f, 0.0f };

	//オブジェクト5(下)
	m_pBlocks[9].pos = { 5.0f, -1.75f, 0.0f };
	m_pBlocks[9].size = { 2.0f, 1.0f, 0.5f };
	m_pBlocks[9].rot = { 0.0f, 0.0f, 0.0f };

	//オブジェクト6(下)
	m_pBlocks[10].pos = { 9.5f, -1.55f, 0.0f };
	m_pBlocks[10].size = { 2.0f, 1.5f, 0.5f };
	m_pBlocks[10].rot = { 0.0f, 0.0f, 0.0f };

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
