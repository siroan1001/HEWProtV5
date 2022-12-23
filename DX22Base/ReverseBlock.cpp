#include "ReverseBlock.h"
#include <vector>
#include "Input.h"

ReverseBlock::ReverseBlock()
{
	//m_blockNum = 1;
	//m_pBlocks = new Stage::Info[m_blockNum];

	//m_pBlocks[0].pos = { -4.0f, 3.25f, 0.0f };
	//m_pBlocks[0].size = { 1.0f, 1.0f, 1.0f };
	//m_pBlocks[0].rot = { 0.0f, 0.0f, 0.0f };

	m_blockNum = 1;

	m_Info.clear();

	Info info;
	info.pos = { -4.0f, 3.25f, 0.0f };
	info.size = { 1.0f, 1.0f, 1.0f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);
	m_dire.push_back(Collision::E_DIRECTION_R);

}
ReverseBlock::~ReverseBlock()
{
	
}

Collision::Direction ReverseBlock::GetDirection(int i)
{
	return m_dire[i];
}

void ReverseBlock::Hit(int i)
{
	//m_pBlocks[i].pos.y = 999.0f;
}