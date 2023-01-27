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
	
	//ステージ１
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

	//一番最初のシャドウブロック
	info.pos = { -3.7f, 3.95f, 0.0f };
	info.size = { 0.5f, 3.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//1つ目の台
	info.pos = { -3.0f, 3.3f, 0.0f };
	info.size = { 2.3f, 0.1f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//二番目のシャドウブロック
	info.pos = { -1.45f, 3.95f, 0.0f };
	info.size = { 0.5f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//三番目のシャドウブロック
	info.pos = { 2.5f, 4.25f, 0.0f };
	info.size = { 0.8f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//2つ目の台
	info.pos = { 3.5f, 3.3f, 0.0f };
	info.size = { 2.0f, 0.1f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//四番目のシャドウブロック
	info.pos = { 5.4f, 4.25f, 0.0f };
	info.size = { 1.0f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//3つ目の台
	info.pos = { 6.2f, 3.4f, 0.0f };
	info.size = { 3.5f, 0.12f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Info.push_back(info);

	//五番目のシャドウブロック
	info.pos = { 8.7f, 4.25f, 0.0f };
	info.size = { 0.8f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_2].m_Shadow.push_back(new ShadowBlock(info));

	//ステージ３
	//地面
	info.pos = { 1.6f, 3.0f, 0.0f };
	info.size = { 22.0f, 0.5f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//一番最初のシャドウブロック
	info.pos = { -3.7f, 3.95f, 0.0f };
	info.size = { 0.5f, 3.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//1つ目の台
	info.pos = { -3.0f, 3.3f, 0.0f };
	info.size = { 2.3f, 0.1f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//二番目のシャドウブロック
	info.pos = { -1.45f, 3.95f, 0.0f };
	info.size = { 0.5f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//三番目のシャドウブロック
	info.pos = { 2.5f, 4.25f, 0.0f };
	info.size = { 0.8f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//2つ目の台
	info.pos = { 3.5f, 3.3f, 0.0f };
	info.size = { 2.0f, 0.1f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//四番目のシャドウブロック
	info.pos = { 5.4f, 4.25f, 0.0f };
	info.size = { 1.0f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));

	//3つ目の台
	info.pos = { 6.2f, 3.4f, 0.0f };
	info.size = { 3.5f, 0.12f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Info.push_back(info);

	//五番目のシャドウブロック
	info.pos = { 8.7f, 4.25f, 0.0f };
	info.size = { 0.8f, 1.0f, 0.5f };
	info.rot = { 0.0f, 0.0f, 0.0f };
	m_Date[SceneGame::E_STAGE_NUMBER_STAGE_3].m_Shadow.push_back(new ShadowBlock(info));
}

Stage::~Stage()
{
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
}

void Stage::Draw()
{
	CameraBase* cam = Game3D::GetCamera();

	for (int i = 0; i < m_Date[*m_pStageNum].m_Info.size(); i++)
	{
		if (!Collision::RectAndRect(m_Date[*m_pStageNum].m_Info[i], cam->GetInfo()))	continue;
		SetGeometoryTranslate(m_Date[*m_pStageNum].m_Info[i].pos.x, m_Date[*m_pStageNum].m_Info[i].pos.y, m_Date[*m_pStageNum].m_Info[i].pos.z);
		SetGeometoryScaling(m_Date[*m_pStageNum].m_Info[i].size.x, m_Date[*m_pStageNum].m_Info[i].size.y, m_Date[*m_pStageNum].m_Info[i].size.z);
		SetGeometoryRotation(m_Date[*m_pStageNum].m_Info[i].rot.x, m_Date[*m_pStageNum].m_Info[i].rot.y, m_Date[*m_pStageNum].m_Info[i].rot.z);
		SetGeometoryColor(XMFLOAT4(10.0f, 10.0f, 10.0f, 1.0f));
		DrawBox();
	}

	for (int i = 0; i < m_Date[*m_pStageNum].m_Shadow.size(); i++)
	{
		if (!Collision::RectAndRect(m_Date[*m_pStageNum].m_Shadow[i]->GetInfo(), cam->GetInfo()))	continue;
		m_Date[*m_pStageNum].m_Shadow[i]->Draw();
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
