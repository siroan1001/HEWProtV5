#include "StartObj.h"
#include "ModelList.h"

StartObj::StartObj()
{
	m_pModel = new Model;
	//if (!m_pModel->Load("Assets/brock/brock.fbx", 0.03f))
	//{
	//	MessageBox(NULL, "モデルの生成に失敗", "エラー", MB_OK);
	//}
	//if (!m_pModel->Load("Assets/もこ田めめめ/MokotaMememe.pmx", 0.03f))
	//{
	//	MessageBox(NULL, "モデルの生成に失敗", "エラー", MB_OK);
	//}
	m_pModel = ModelList::GetModel(ModelList::E_MODEL_LIST_CONST_BOX);
	//頂点シェーダをモデルに設定
	m_pModel->SetVertexShader(m_pVS);

	m_Info = { {-6.3f, 3.25f, 0.0f}, {0.3f, 1.0f, 0.3f}, {0.0f, 0.0f, 0.0f} };
	m_ModelSize = { 0.3f, 1.0f, 0.3f };
}

Def::Info StartObj::GetInfo()
{
	Def::Info info = m_Info;
	info.size.x = 0.1f;
	return info;
}
