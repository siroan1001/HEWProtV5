#include "ShadowBlock.h"
#include "ShadowBillBoard.h"
#include "Geometory.h"
#include "Modellist.h"
#include "SceneGame.h"
#include "CameraBase.h"
#include "Game3D.h"

using namespace std;

ID3D11ShaderResourceView* ShadowBlock::m_pTex;

void ShadowBlock::Init()
{
	LoadTextureFromFile("Assets/fin.png", &m_pTex);
}

void ShadowBlock::Uninit()
{
	m_pTex->Release();
}

ShadowBlock::ShadowBlock(Def::Info info)
{
	m_BlockInfo.Info.pos = { 999.0f, 999.0f, 0.0f };
	m_BlockInfo.Info.size = { 0.5f, 0.5f, 0.5f };
	m_BlockInfo.Info.rot = { 0.0f, 0.0f, 0.0f };
	m_BlockInfo.xy = { 0.0f, 0.0f };

	m_ModelSize.x = m_ModelSize.y = m_ModelSize.z = 0.1f;
	//���f���ǂݍ���
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_SHADOWBLOCK);

	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);



	SetShadowBlock(info);
}

ShadowBlock::~ShadowBlock()
{

}

void ShadowBlock::Update()
{
	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			if (init->life >= 30.0f)	continue;

			init->life += 0.1f;
			if (init->life >= 30.0f)
			{
				init->life = 30.0f;
				init->use = true;
			}

		}
	}
}

void ShadowBlock::Draw()
{
	//vector<Def::Info>	block;		//�`��p�̃f�[�^���i�[
	m_DrawBlock.clear();
	Def::Info info;		//�v�Z�p
	float PosL;		//�u���b�N�̍��[������
	int count;
	CameraBase* cam = Game3D::GetCamera();

	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		

		info = m_BlockBase;
		info.pos.y = it->begin()->Info.pos.y;
		count = 0;
		//info.size.x = 0.0f;
		PosL = it->begin()->Info.pos.x + it->begin()->Info.size.x / 2.0f;
		std::vector<ShadowBlock::SmallBlockTemp>::iterator end = it->end();		//����̍Ō�̗v�f���w��
		end--;
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			//if (!Collision::RectAndRect(init->Info, cam->GetInfo()))	continue;

			if (init == end)
			{
				if (count <= 0)
				{
					continue;
				}
				info.size.x *= count;
				info.pos.x = PosL - info.size.x / 2.0f;
				m_DrawBlock.push_back(info);
			}
			else if (init->use)
			{
				count++;
			}
			else if(!init->use)
			{
				if (count <= 0)
				{
					vector<ShadowBlock::SmallBlockTemp>::iterator next = init;
					next++;
					PosL = next->Info.pos.x + next->Info.size.x / 2.0f;
					continue;
				}
				else
				{
					info.size.x *= count;
					info.pos.x = PosL - info.size.x / 2.0f;
					m_DrawBlock.push_back(info);
					info = m_BlockBase;
					//info�̎����������ꏊ�̍��[��posL�ɓ����
					vector<ShadowBlock::SmallBlockTemp>::iterator next = init;
					info.pos.y = it->begin()->Info.pos.y;
					next++;
					PosL = next->Info.pos.x + next->Info.size.x / 2.0f;
					count = 0;
				}
			}
		}
	}

	for (vector<Def::Info>::iterator it = m_DrawBlock.begin(); it != m_DrawBlock.end(); ++it)
	{
		SetGeometoryTranslate(it->pos.x, it->pos.y, it->pos.z);
		SetGeometoryScaling(it->size.x, it->size.y, it->size.z);
		SetGeometoryRotation(it->rot.x, it->rot.y, it->rot.z);
		SetGeometoryColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.75f));
		DrawBox();

		//Billboard::Info info = { {it->pos.x, it->pos.y, 0.75f},{it->size.x, it->size.y} };
		//ShadowBillBoard* sbill = new ShadowBillBoard(info);
		//sbill->Draw();
		//delete sbill;
	}

	

	//for (int i = 0; i < m_BillBoard.size(); i++)
	//{
	//	for (int j = 0; j < m_BillBoard[i].size(); j++)
	//	{
	//		m_BillBoard[i][j]->Draw();
	//	}
	//}
}

void ShadowBlock::Reset()
{
	for (auto it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		for (auto init = it->begin(); init != it->end(); ++init)
		{
			init->life = 30.0f;
			init->use = true;
		}
	}
}

void ShadowBlock::SetShadowBlock(Def::Info info)
{
	m_BlockInfo.Info = info;
	m_BlockInfo.xy.x = m_BlockInfo.Info.size.x / m_BlockBase.size.x;
	m_BlockInfo.xy.y = m_BlockInfo.Info.size.y / m_BlockBase.size.y;

	for (int i = 0; i < m_BlockInfo.xy.y; i++)
	{
		std::vector<ShadowBlock::SmallBlockTemp> tempVec;
		//vector<ShadowBillBoard*> tempb;

		for (int j = 0; j < m_BlockInfo.xy.x; j++)
		{
			ShadowBlock::SmallBlockTemp temp = { m_BlockBase, true, 30.0f};
			temp.Info.pos = { m_BlockInfo.Info.pos.x - m_BlockBase.size.x * j, m_BlockInfo.Info.pos.y - m_BlockBase.size.y * i, m_BlockInfo.Info.pos.z };//�u���b�N�̃T�C�Y�����炷

			tempVec.push_back(temp);
		}
		m_SmallBlockInfo.push_back(tempVec);
	}

	m_BlockInfo.Info.pos.x += m_BlockBase.size.x / 2.0f;
	m_BlockInfo.Info.pos.y += m_BlockBase.size.y / 2.0f;

	XMFLOAT2 size = { m_BlockInfo.xy.x * m_BlockBase.size.x, m_BlockInfo.xy.y * m_BlockBase.size.y };
	m_BlockInfo.Info.pos.x -= size.x / 2.0f;
	m_BlockInfo.Info.pos.y -= size.y / 2.0f;
}

void ShadowBlock::SetUse(XMFLOAT2 num, bool flag)
{
	m_SmallBlockInfo[num.y][num.x].use = flag;
}

std::vector<std::vector<ShadowBlock::SmallBlockTemp>>* ShadowBlock::GetSmallBlockInfo()
{
	return &m_SmallBlockInfo;
}

int ShadowBlock::GetNum()
{
	int num = 0;

	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = m_SmallBlockInfo.begin(); it != m_SmallBlockInfo.end(); ++it)
	{
		num += it->size();
	}
	return num;
}

Def::Info ShadowBlock::GetInfo()
{
	return m_BlockInfo.Info;
}

vector<Def::Info> ShadowBlock::GetDrawBlock()
{
	return m_DrawBlock;
}

