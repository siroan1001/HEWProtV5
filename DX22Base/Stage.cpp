#include "Stage.h"
#include <vector>
#include "Input.h"
#include "Collision.h"
#include "SceneGame.h"
#include "SceneStageSelect.h"
#include "CameraBase.h"
#include "Geometory.h"
#include "Game3D.h"

Stage::Stage()
	:m_blockNum(11)
{
	Def::Info info;

	m_pStageNum = SceneStageSelect::GetStageNumber();
	
	//ステージ1
	//床
	info.pos = { 1.6f, 3.0f, 0.0f };
	info.size = { 22.0f, 0.5f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Info.push_back(info);

	info.pos = { 0.4f, 3.55f, 0.0f };
	info.size = { 0.2f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Info.push_back(info);

	info.pos = { 3.35f, 3.75f, 0.0f };
	info.size = { 0.2f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Info.push_back(info);

	info.pos = { 6.5f, 4.05f, 0.0f };
	info.size = { 1.5f, 0.2f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Info.push_back(info);

	info.pos = { 6.5f, 4.275f, 0.0f };
	info.size = { 0.2f, 0.25f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Info.push_back(info);

	info.pos = { 6.5f, 5.075f, 0.0f };
	info.size = { 0.2f, 0.25f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Info.push_back(info);

	//シャドウブロック1
	info.pos = { -2.3f, 3.95f, 0.0f };
	info.size = { 1.3f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック2
	info.pos = { 0.3f, 3.95f, 0.0f };
	info.size = { 1.3f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック3
	info.pos = { 4.5f, 4.55f, 0.0f };
	info.size = { 2.3f, 1.3f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック4
	info.pos = { 5.75f, 4.15f, 0.0f };
	info.size = { 1.5f, 0.2f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック4
	info.pos = { 7.0f, 4.95f, 0.0f };
	info.size = { 1.0f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック4
	info.pos = { 7.0f, 3.95f, 0.0f };
	info.size = { 1.0f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_1].m_Shadow.push_back(new ShadowBlock(info));

	//ステージ２
	//地面
	info.pos = { 1.6f, 3.0f, 0.0f };
	info.size = { 22.0f, 0.5f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//壁
	//1
	info.pos = { -2.17f, 3.55f, 0.0f };
	info.size = { 0.2f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//2
	info.pos = { 1.6f, 3.77f, 0.0f };
	info.size = { 0.2f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//3
	info.pos = { 2.58f, 4.8f, 0.0f };
	info.size = { 0.2f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//4
	info.pos = { 2.58f, 3.55f, 0.0f };
	info.size = { 0.2f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//5
	info.pos = { 3.73f, 4.8f, 0.0f };
	info.size = { 0.5f, 0.7f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//6
	info.pos = { 3.73f, 3.6f, 0.0f };
	info.size = { 0.5f, 0.7f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//7
	info.pos = { 6.5f, 4.3f, 0.0f };
	info.size = { 0.5f, 0.7f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//8
	info.pos = { 7.78f, 3.98f, 0.0f };
	info.size = { 0.5f, 0.25f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//シャドウブロック1
	info.pos = { -2.3f, 3.95f, 0.0f };
	info.size = { 1.3f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック2
	info.pos = { -0.8f, 3.95f, 0.0f };
	info.size = { 1.3f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック3
	info.pos = { 1.47f, 4.35f, 0.0f };
	info.size = { 1.0f, 1.1f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック4
	info.pos = { 2.47f, 4.67f, 0.0f };
	info.size = { 0.8f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック5
	info.pos = { 3.45f, 4.67f, 0.0f };
	info.size = { 0.8f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック6
	info.pos = { 4.75f, 4.65f, 0.0f };
	info.size = { 0.8f, 1.4f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック7
	info.pos = { 7.52f, 4.65f, 0.0f };
	info.size = { 0.8f, 1.4f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック8
	info.pos = { 8.8f, 4.65f, 0.0f };
	info.size = { 0.8f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//ステージ３
	//地面
	info.pos = { 1.6f, 3.0f, 0.0f };
	info.size = { 22.0f, 0.5f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//壁
	//1
	info.pos = { -1.28f, 4.05f, 0.0f };
	info.size = { 0.5f, 0.3f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//2
	info.pos = { -1.28f, 3.35f, 0.0f };
	info.size = { 0.5f, 0.3f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//3
	info.pos = { 0.0f, 3.85f, 0.0f };
	info.size = { 0.5f, 0.3f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//4
	info.pos = { 0.0f, 4.48f, 0.0f };
	info.size = { 0.5f, 0.3f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//5
	info.pos = { 1.28f, 4.35f, 0.0f };
	info.size = { 0.5f, 0.6f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//6
	info.pos = { 3.28f, 3.35f, 0.0f };
	info.size = { 0.5f, 0.8f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//7
	info.pos = { 4.7f, 3.35f, 0.0f };
	info.size = { 0.8f, 0.55f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//8
	info.pos = { 4.7f, 4.45f, 0.0f };
	info.size = { 0.8f, 0.3f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//9
	info.pos = { 5.48f, 4.15f, 0.0f };
	info.size = { 0.8f, 0.3f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//10
	info.pos = { 6.11f, 4.15f, 0.0f };
	info.size = { 0.5f, 0.7f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//11
	info.pos = { 7.38f, 4.05f, 0.0f };
	info.size = { 0.5f, 0.7f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//12
	info.pos = { 8.65f, 4.28f, 0.0f };
	info.size = { 0.5f, 0.25f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//シャドウブロック1
	info.pos = { -1.57f, 4.25f, 0.0f };
	info.size = { 1.2f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック2
	info.pos = { -0.25f, 4.41f, 0.0f };
	info.size = { 0.8f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック3
	info.pos = { 1.02f, 4.38f, 0.0f };
	info.size = { 0.8f, 1.1f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック4
	info.pos = { 3.02f, 4.38f, 0.0f };
	info.size = { 0.8f, 1.1f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック5
	info.pos = { 4.3f, 4.59f, 0.0f };
	info.size = { 0.8f, 0.9f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック6
	info.pos = { 5.07f, 4.3f, 0.0f };
	info.size = { 0.8f, 0.7f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック7
	info.pos = { 5.85f, 4.0f, 0.0f };
	info.size = { 0.8f, 0.7f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック8
	info.pos = { 5.85f, 4.97f, 0.0f };
	info.size = { 0.8f, 0.7f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック9
	info.pos = { 7.13f, 4.38f, 0.0f };
	info.size = { 0.8f, 1.1f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//シャドウブロック10
	info.pos = { 8.4f, 4.38f, 0.0f };
	info.size = { 0.8f, 1.1f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));


	m_pGround = new Ground;
	m_pGrass = new Grass;
}

Stage::~Stage()
{
	delete m_pGrass;
	delete m_pGround;

	for (int i = 0; i < SceneGame::E_STAGE_NUMBER_STAGE_MAX; i++)
	{
		m_Date[i].m_Info.clear();
		m_Date[i].m_Shadow.clear();
	}
}

void Stage::Update()
{
	for (int i = 0; i < m_Date[*m_pStageNum].m_Shadow.size(); i++)
	{
		m_Date[*m_pStageNum].m_Shadow[i]->Update();
	}

	m_pGround->Update();
}

void Stage::Draw()
{
	CameraBase* cam = Game3D::GetCamera();

	for (int i = 1; i < m_Date[*m_pStageNum].m_Info.size(); i++)
	{
		if (!Collision::RectAndRect(m_Date[*m_pStageNum].m_Info[i], cam->GetInfo()))	continue;
		SetGeometoryTranslate(m_Date[*m_pStageNum].m_Info[i].pos.x, m_Date[*m_pStageNum].m_Info[i].pos.y, m_Date[*m_pStageNum].m_Info[i].pos.z);
		SetGeometoryScaling(m_Date[*m_pStageNum].m_Info[i].size.x, m_Date[*m_pStageNum].m_Info[i].size.y, m_Date[*m_pStageNum].m_Info[i].size.z);
		SetGeometoryRotation(m_Date[*m_pStageNum].m_Info[i].rot.x, m_Date[*m_pStageNum].m_Info[i].rot.y, m_Date[*m_pStageNum].m_Info[i].rot.z);
		SetGeometoryColor(XMFLOAT4(10.0f, 10.0f, 10.0f, 1.0f));
		DrawBox();

		
	}

	Object::SetObjColor(m_pGround->GetColor());
	m_pGround->Draw();

	//Object::SetObjColor(m_pGrass->GetColor());
	//m_pGrass->Draw();

	for (int i = 0; i < m_Date[*m_pStageNum].m_Shadow.size(); i++)
	{
		if (!Collision::RectAndRect(m_Date[*m_pStageNum].m_Shadow[i]->GetInfo(), cam->GetInfo()))	continue;
		m_Date[*m_pStageNum].m_Shadow[i]->Draw();
	}
}

void Stage::Reset()
{
	for (int i = 0; i < m_Date[*m_pStageNum].m_Shadow.size(); i++)
	{
		m_Date[*m_pStageNum].m_Shadow[i]->Reset();
	}
	
}

Def::Info Stage::GetInfo(int num)
{
	return m_Date[*m_pStageNum].m_Info[num];
}

int Stage::GetStageNum()
{
	return m_Date[*m_pStageNum].m_Info.size();
}

int Stage::GetShadowNum()
{
	int num = 0;

	for (int i = 0; i < m_Date[*m_pStageNum].m_Shadow.size(); i++)
	{
		num += m_Date[*m_pStageNum].m_Shadow[i]->GetNum();
	}

	return num;
}

vector<ShadowBlock*> Stage::GetShadowBlock()
{
	return m_Date[*m_pStageNum].m_Shadow;
}
