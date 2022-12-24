#include "ReverseBlock.h"
#include <vector>
#include "Input.h"

ReverseBlock::ReverseBlock()
{
	//m_blockNum = 1;
	//m_pBlocks = new Object::Info[m_blockNum];

	//m_pBlocks[0].pos = { -4.0f, 3.25f, 0.0f };
	//m_pBlocks[0].size = { 1.0f, 1.0f, 1.0f };
	//m_pBlocks[0].rot = { 0.0f, 0.0f, 0.0f };

	m_blockNum = 2;

	m_Info.clear();

	Object::Info info;
	info.pos = { 6.8f, 0.95f, 0.0f };
	info.size = { 0.5f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);
	m_dire.push_back(Collision::E_DIRECTION_R);

	info.pos = { -6.1f, 0.0f, 0.0f };
	info.size = { 0.5f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);
	m_dire.push_back(Collision::E_DIRECTION_L);
}
ReverseBlock::~ReverseBlock()
{
	
}

void ReverseBlock::Draw()
{
	for (int i = 0; i < m_Info.size(); i++)
	{
		SetGeometoryTranslate(m_Info[i].pos.x, m_Info[i].pos.y, m_Info[i].pos.z);
		SetGeometoryScaling(m_Info[i].size.x, m_Info[i].size.y, m_Info[i].size.z);
		SetGeometoryRotation(m_Info[i].rot.x, m_Info[i].rot.y, m_Info[i].rot.z);
		DrawBox();
	}
}

Collision::Direction ReverseBlock::GetDirection(int i)
{
	return m_dire[i];
}

void ReverseBlock::Hit(int i)
{
	//m_pBlocks[i].pos.y = 999.0f;
}