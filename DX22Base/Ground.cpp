#include "Ground.h"
#include "ModelList.h"
#include "Game3D.h"

Ground::Ground()
{
	m_Info = { {Game3D::GetCamera()->GetLook().x, 3.1f, -0.0f}, {0.3f, 0.35f, 0.3f}, {0.0f, 180.0f, 0.0f} };
	m_ModelSize.x = 0.1f;
	m_ModelSize.y = 0.3f;
	m_ModelSize.z = 0.006f;
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_GROUND);

	//頂点シェーダをモデルに設定
	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);

	m_Color = XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f);

	m_pCamera = Game3D::GetCamera();
}

void Ground::Update()
{
	m_Info.pos.x = Game3D::GetCamera()->GetLook().x;
}
