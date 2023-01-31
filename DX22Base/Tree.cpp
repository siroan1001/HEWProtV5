#include "Tree.h"
#include "Game3D.h"
#include "ModelList.h"

Tree::Tree(XMFLOAT3 info, float size)
{
	m_Info = { info, {0.3f, 0.35f, 0.3f}, {0.0f, 180.0f, 0.0f} };
	m_ModelSize = { 0.02f, 0.02f, 0.02f };

	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_TREE);

	//���_�V�F�[�_�����f���ɐݒ�
	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);

	m_Color = XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f);

	m_pCamera = Game3D::GetCamera();
}

void Tree::Update()
{
}
