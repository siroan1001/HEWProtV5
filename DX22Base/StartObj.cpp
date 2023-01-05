#include "StartObj.h"

StartObj::StartObj()
{
	m_pModel = new Model;
	//if (!m_pModel->Load("Assets/brock/brock.fbx", 0.03f))
	//{
	//	MessageBox(NULL, "���f���̐����Ɏ��s", "�G���[", MB_OK);
	//}
	if (!m_pModel->Load("Assets/�����c�߂߂�/MokotaMememe.pmx", 0.03f))
	{
		MessageBox(NULL, "���f���̐����Ɏ��s", "�G���[", MB_OK);
	}
	//���_�V�F�[�_�����f���ɐݒ�
	m_pModel->SetVertexShader(m_pVS);

	m_Info = { {-6.3f, 3.25f, 0.0f}, {0.3f, 1.0f, 0.3f}, {0.0f, 0.0f, 0.0f} };
}

Def::Info StartObj::GetInfo()
{
	Def::Info info = m_Info;
	info.size.x = 0.1f;
	return info;
}
