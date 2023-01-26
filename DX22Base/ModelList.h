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

		E_MODEL_LIST_CONST_MAX
	};

public:
	static void Init();
	static void Uninit();

	static Model* GetModel(ModelListConst);

private:
	static Model* m_ModelList[E_MODEL_LIST_CONST_MAX];

};