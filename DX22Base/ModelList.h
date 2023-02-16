#pragma once

#include "Model.h"

class ModelList
{
public:
	enum ModelListConst
	{
		E_MODEL_LIST_CONST_BOX = 0,
		E_MODEL_LIST_CONST_PLAYER,
		E_MODEL_LIST_CONST_ENEMY,
		E_MODEL_LIST_CONST_GHOST,
		E_MODEL_LIST_CONST_SHADOWBLOCK,
		E_MODEL_LIST_CONST_GROUND,
		E_MODEL_LIST_CONST_GRASS,
		E_MODEL_LIST_CONST_FLAG,
		E_MODEL_LIST_CONST_TREE,

		E_MODEL_LIST_CONST_MAX
	};

public:
	static void Init();
	static void Uninit();

	static Model* GetModel(ModelListConst);
	static ID3D11ShaderResourceView* GetTexture();

private:
	static Model* m_ModelList[E_MODEL_LIST_CONST_MAX];
	static ID3D11ShaderResourceView* m_pTex;

};