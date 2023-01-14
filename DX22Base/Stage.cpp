#include "Stage.h"
#include <vector>
#include "Input.h"
#include "Collision.h"
#include "Game3D.h"
#include "CameraBase.h"

Stage::Stage()
	:m_blockNum(11)
{
	Def::Info info;

	////��(��)
	//info.pos = { 3.8f, -2.5f, 0.0f };
	//info.size = { 20.5f, 0.5f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////��(�^��)
	//info.pos = { 1.7f, 0.2f, 0.0f };
	//info.size = { 10.9f, 0.5f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////��(��)
	//info.pos = { -2.2f, 3.0f, 0.0f };
	//info.size = { 13.5f, 0.5f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////��(��)
	//info.pos = { -6.2f, 0.35f, 0.0f };
	//info.size = { 0.5f, 5.7f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////��(�E)
	//info.pos = { 6.9f, 2.9f, 0.0f };
	//info.size = { 0.5f, 5.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////�I�u�W�F�N�g1(��)
	//info.pos = { -2.0f, 3.75f, 0.0f };
	//info.size = { 1.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////�I�u�W�F�N�g2(��)
	//info.pos = { 0.7f, 3.75f, 0.0f };
	//info.size = { 1.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////�I�u�W�F�N�g3(�^��)
	//info.pos = { 0.0f, 0.95f, 0.0f };
	//info.size = { 3.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////�I�u�W�F�N�g4(��)
	//info.pos = { -0.7f, -1.75f, 0.0f };
	//info.size = { 3.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////�I�u�W�F�N�g5(��)
	//info.pos = { 5.0f, -1.75f, 0.0f };
	//info.size = { 2.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////�I�u�W�F�N�g6(��)
	//info.pos = { 9.5f, -1.55f, 0.0f };
	//info.size = { 2.0f, 1.5f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Info.push_back(info);

	////�V���h�E�u���b�N1(��)
	//info.pos = { -2.5f, 4.25f, 0.0f };
	//info.size = { 1.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Shadow.push_back(new ShadowBlock(info));

	////�V���h�E�u���b�N2(��)
	//info.pos = { 0.2f, 5.25f, 0.0f };
	//info.size = { 1.7f, 2.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Shadow.push_back(new ShadowBlock(info));

	////�V���h�E�u���b�N3(��)
	//info.pos = { 2.2f, 4.25f, 0.0f };
	//info.size = { 1.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Shadow.push_back(new ShadowBlock(info));

	////�V���h�E�u���b�N4(�^��)
	//info.pos = { -1.5f, 1.44f, 0.0f };
	//info.size = { 1.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Shadow.push_back(new ShadowBlock(info));

	////�V���h�E�u���b�N5(�^��)
	//info.pos = { 2.48f, 1.44f, 0.0f };
	//info.size = { 1.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Shadow.push_back(new ShadowBlock(info));

	////�V���h�E�u���b�N6(��)
	//info.pos = { -2.2f, -1.26f, 0.0f };
	//info.size = { 1.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Shadow.push_back(new ShadowBlock(info));

	////�V���h�E�u���b�N7(��)
	//info.pos = { 1.79f, -1.26f, 0.0f };
	//info.size = { 1.0f, 1.0f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Shadow.push_back(new ShadowBlock(info));

	////�V���h�E�u���b�N8(��)
	//info.pos = { 4.0f, -0.76f, 0.0f };
	//info.size = { 1.0f, 1.5f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Shadow.push_back(new ShadowBlock(info));

	////�V���h�E�u���b�N9(��)
	//info.pos = { 8.5f, -0.76f, 0.0f };
	//info.size = { 2.51f, 1.2f, 0.5f };
	//info.rot = { 0.0f, 0.0f, 0.0f };
	//m_Shadow.push_back(new ShadowBlock(info));

	//��
	info.pos = { 1.6f, 3.0f, 0.0f };
	info.size = { 22.0f, 0.5f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Info.push_back(info);
	
	//�V���h�E�u���b�N1
	info.pos = { -2.3f, 3.95f, 0.0f };
	info.size = { 1.3f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Shadow.push_back(new ShadowBlock(info));
	
	//�V���h�E�u���b�N2
	info.pos = { 0.3f, 3.95f, 0.0f };
	info.size = { 1.3f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Shadow.push_back(new ShadowBlock(info));
	
	//�V���h�E�u���b�N3
	info.pos = { 4.5f, 4.55f, 0.0f };
	info.size = { 2.3f, 1.3f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Shadow.push_back(new ShadowBlock(info));
}

Stage::~Stage()
{
	m_Info.clear();
}

void Stage::Draw()
{
	CameraBase* cam = Game3D::GetCamera();

	for (int i = 0; i < m_Info.size(); i++)
	{
		if (!Collision::RectAndRect(m_Info[i], cam->GetInfo()))	continue;
		SetGeometoryTranslate(m_Info[i].pos.x, m_Info[i].pos.y, m_Info[i].pos.z);
		SetGeometoryScaling(m_Info[i].size.x, m_Info[i].size.y, m_Info[i].size.z);
		SetGeometoryRotation(m_Info[i].rot.x, m_Info[i].rot.y, m_Info[i].rot.z);
		DrawBox();
	}

	for (int i = 0; i < m_Shadow.size(); i++)
	{
		if (!Collision::RectAndRect(m_Shadow[i]->GetInfo(), cam->GetInfo()))	continue;
		m_Shadow[i]->Draw();
	}
}

Def::Info Stage::GetInfo(int num)
{
	return m_Info[num];
}

int Stage::GetStageNum()
{
	return m_Info.size();
}

int Stage::GetShadowNum()
{
	int num = 0;

	for (int i = 0; i < m_Shadow.size(); i++)
	{
		num += m_Shadow[i]->GetNum();
	}

	return num;
}

vector<ShadowBlock*> Stage::GetShadowBlock()
{
	return m_Shadow;
}
