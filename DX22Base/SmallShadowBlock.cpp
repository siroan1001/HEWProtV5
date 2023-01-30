#include "SmallShadowBlock.h"
#include "ModelList.h"
#include "Game3D.h"

SmallShadowBlock::SmallShadowBlock(Def::Info info)
	:m_Life(30.0f)
	,m_Use(true)
{
	m_Info = info;
	m_ModelSize = XMFLOAT3(0.1f, 0.1f, 0.1f);
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_SHADOWBLOCK);
	//頂点シェーダをモデルに設定
	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);
	m_Color = XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f);
	m_pCamera = Game3D::GetCamera();
}

void SmallShadowBlock::Update()
{
	if (m_Life >= 30.0f)	return;
	m_Life += 0.1f;
	if (m_Life > 30.0f)
	{
		m_Life = 30.0f;
		m_Use = true;
	}
}

void SmallShadowBlock::Reset()
{
	m_Life = 30.0f;
	m_Use = true;
}

bool SmallShadowBlock::GetUse()
{
	return m_Use;
}

float SmallShadowBlock::GetLife()
{
	return m_Life;
}

void SmallShadowBlock::SetUse(bool flag)
{
	m_Use = flag;
}

void SmallShadowBlock::SetLife(float num)
{
	m_Life = num;
}
