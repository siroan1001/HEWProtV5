#include "Grass.h"
#include "Game3D.h"
#include "ModelList.h"

Grass::Grass()
{
	m_Info = { {Game3D::GetCamera()->GetLook().x, 3.0f, 1.0f}, {0.3f, 0.35f, 0.3f}, {0.0f, -90.0f, -10.0f} };
	m_ModelSize.x = 0.05f;
	m_ModelSize.y = 0.04f;
	m_ModelSize.z = 0.05f;
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_GRASS);

	//頂点シェーダをモデルに設定
	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);

	m_Color = XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f);

	m_pCamera = Game3D::GetCamera();
}

void Grass::Update()
{
}
