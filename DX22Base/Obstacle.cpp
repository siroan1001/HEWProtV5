#include "Obstacle.h"
#include "ModelList.h"

Obstacle::Obstacle()
{
	m_Info = { {-6.0f, 4.7f, 0.0f}, {1.0f, 1.0f, 0.3f}, {0.0f, 0.0f, 0.0f} };;
	m_ModelSize.x = 1.0f;
	m_ModelSize.y = 1.0f;
	m_ModelSize.z = 0.1f;

	//m_pModel = new Model;
	//if (!m_pModel->Load("Assets/box/box.fbx", 1.0f))
	//{
	//	MessageBox(NULL, "���f���̐����Ɏ��s", "�G���[", MB_OK);
	//}
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_BOX);

	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);
}

void Obstacle::Update()
{

}