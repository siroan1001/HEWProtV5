#include "ModelList.h"
#include "DirectXTex/Texture.h"

Model* ModelList::m_ModelList[E_MODEL_LIST_CONST_MAX]; 
ID3D11ShaderResourceView* ModelList::m_pTex;

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
	m_ModelList[E_MODEL_LIST_CONST_SHADOWBLOCK]->Load("Assets/shadowblock/shadowblock.fbx", 1.0f);
	m_ModelList[E_MODEL_LIST_CONST_GROUND] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_GROUND]->Load("Assets/stage1/stage.fbx", 1.0f);
	m_ModelList[E_MODEL_LIST_CONST_GRASS] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_GRASS]->Load("Assets/grass/grass.fbx", 1.0f);
	m_ModelList[E_MODEL_LIST_CONST_FLAG] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_FLAG]->Load("Assets/flag/flag.fbx", 1.0f);
	m_ModelList[E_MODEL_LIST_CONST_TREE] = new Model;
	m_ModelList[E_MODEL_LIST_CONST_TREE]->Load("Assets/tree/tree.fbx", 1.0f);

	LoadTextureFromFile("Assets/0d99778f81248d9d.png", &m_pTex);
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

ID3D11ShaderResourceView * ModelList::GetTexture()
{
	return m_pTex;
}
