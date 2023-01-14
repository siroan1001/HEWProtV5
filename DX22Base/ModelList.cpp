#include "ModelList.h"

Model* ModelList::m_ModelList[E_MODEL_LIST_CONST_MAX];

void ModelList::Init()
{
	Model* model = new Model;
	for (int i = 0; i < E_MODEL_LIST_CONST_MAX; i++)
	{
		m_ModelList[i] = model;
	}
	m_ModelList[E_MODEL_LIST_CONST_BOX]->Load("Assets/box/box.fbx", 1.0f);
	m_ModelList[E_MODEL_LIST_CONST_PLAYER]->Load("Assets/‚à‚±“c‚ß‚ß‚ß/MokotaMememe.pmx", 1.0f);
}

void ModelList::Uninit()
{
	for (int i = 0; i < E_MODEL_LIST_CONST_MAX; i++)
	{
		delete m_ModelList[i];
	}
}

Model * ModelList::GetModel(ModelListConst listconst)
{
	return m_ModelList[listconst];
}
