#include "ReverseBlock.h"
#include <vector>
#include "Input.h"

ReverseBlock::ReverseBlock()
{
	m_blockNum = 1;
	m_pBlocks = new Stage::Info[m_blockNum];

	m_pBlocks[0].pos = { -4.0f, 3.25f, 0.0f };
	m_pBlocks[0].size = { 1.0f, 1.0f, 1.0f };
	m_pBlocks[0].rot = { 0.0f, 0.0f, 0.0f };

}
ReverseBlock::~ReverseBlock()
{

}

void ReverseBlock::Hit(int i)
{
	m_pBlocks[i].pos.y = 999.0f;
}