#include "Stage.h"
#include <vector>
#include "Input.h"

Stage::Stage()
	:m_blockNum(11)
{
	Info info;

	//��(��)
	info.pos = { 3.8f, -2.5f, 0.0f };
	info.size = { 20.5f, 0.5f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);

	//��(�^��)
	info.pos = { 1.7f, 0.2f, 0.0f };
	info.size = { 10.9f, 0.5f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);

	//��(��)
	info.pos = { -2.2f, 3.0f, 0.0f };
	info.size = { 13.5f, 0.5f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);

	//��(��)
	info.pos = { -6.2f, 0.35f, 0.0f };
	info.size = { 0.5f, 5.7f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);

	//��(�E)
	info.pos = { 6.9f, 2.9f, 0.0f };
	info.size = { 0.5f, 5.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);

	//�I�u�W�F�N�g1(��)
	info.pos = { -2.0f, 3.75f, 0.0f };
	info.size = { 1.0f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);

	//�I�u�W�F�N�g2(��)
	info.pos = { 0.7f, 3.75f, 0.0f };
	info.size = { 1.0f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);

	//�I�u�W�F�N�g3(�^��)
	info.pos = { 0.0f, 0.95f, 0.0f };
	info.size = { 3.0f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);

	//�I�u�W�F�N�g4(��)
	info.pos = { -0.7f, -1.75f, 0.0f };
	info.size = { 3.0f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);

	//�I�u�W�F�N�g5(��)
	info.pos = { 5.0f, -1.75f, 0.0f };
	info.size = { 2.0f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);

	//�I�u�W�F�N�g6(��)
	info.pos = { 9.5f, -1.55f, 0.0f };
	info.size = { 2.0f, 1.5f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);
}

Stage::~Stage()
{
	m_Info.clear();
}

void Stage::Draw()
{


	for (int i = 0; i < m_blockNum; i++)
	{
		SetGeometoryTranslate(m_Info[i].pos.x, m_Info[i].pos.y, m_Info[i].pos.z);
		SetGeometoryScaling(m_Info[i].size.x, m_Info[i].size.y, m_Info[i].size.z);
		SetGeometoryRotation(m_Info[i].rot.x, m_Info[i].rot.y, m_Info[i].rot.z);
		DrawBox();
	}
	
}

Stage::Info Stage::GetInfo(int num)
{
	return m_Info[num];
}

int Stage::GetNum()
{
	return m_blockNum;
}
