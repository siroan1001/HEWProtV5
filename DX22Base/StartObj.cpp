#include "StartObj.h"
#include "ModelList.h"

StartObj::StartObj()
{
	m_pModel = new Model;
	//if (!m_pModel->Load("Assets/brock/brock.fbx", 0.03f))
	//{
	//	MessageBox(NULL, "���f���̐����Ɏ��s", "�G���[", MB_OK);
	//}
	//if (!m_pModel->Load("Assets/�����c�߂߂�/MokotaMememe.pmx", 0.03f))
	//{
	//	MessageBox(NULL, "���f���̐����Ɏ��s", "�G���[", MB_OK);
	//}
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_FLAG);
	//���_�V�F�[�_�����f���ɐݒ�
	m_pModel->SetVertexShader(m_pVS);
	m_pModel->SetPixelShader(m_pPS);

	m_Info = { {-6.3f, 3.25f, 0.0f}, {0.3f, 1.0f, 0.3f}, {0.0f, 0.0f, 0.0f} };
	m_ModelSize = { 0.05f, 0.05f, 0.05f };

	m_Color = XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f);
}

Def::Info StartObj::GetInfo()
{
	Def::Info info = m_Info;
	info.size.x = 0.1f;
	return info;
}
