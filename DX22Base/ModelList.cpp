#include "ModelList.h"

Model* ModelList::m_ModelList[E_MODEL_LIST_CONST_MAX];

void ModelList::Init()
{
	m_ModelList[E_MODEL_LIST_CONST_BOX] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_BOX]->Load("Assets/box/box.fbx", 1.0f);
	m_ModelList[E_MODEL_LIST_CONST_PLAYER] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_PLAYER]->Load("Assets/‚à‚±“c‚ß‚ß‚ß/MokotaMememe.pmx", 1.0f);
}

void ModelList::Uninit()
{
	for (int i = 0; i < E_MODEL_LIST_CONST_MAX; i++)
	{
		if (!m_ModelList[i])	continue;
		delete m_ModelList[i];
	}
}

Model * ModelList::GetModel(ModelListConst listconst)
{
	return m_ModelList[listconst];
}
