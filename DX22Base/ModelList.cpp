#include "ModelList.h"

Model* ModelList::m_ModelList[E_MODEL_LIST_CONST_MAX];

void ModelList::Init()
{
	m_ModelList[E_MODEL_LIST_CONST_BOX] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_BOX]->Load("Assets/box/box.fbx", 1.0f);
	m_ModelList[E_MODEL_LIST_CONST_PLAYER] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_PLAYER]->Load("Assets/player_fi/player.fbx", 1.0f);
	m_ModelList[E_MODEL_LIST_CONST_ENEMY] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_ENEMY]->Load("Assets/Enemy/Enemy.fbx", 1.0f);
	m_ModelList[E_MODEL_LIST_CONST_GHOST] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_GHOST]->Load("Assets/ghost_v3/ghost.fbx", 1.0f);
	m_ModelList[E_MODEL_LIST_CONST_SHADOWBLOCK] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_SHADOWBLOCK]->Load("Assets/shadowblock/shadow.fbx", 1.0f);
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
