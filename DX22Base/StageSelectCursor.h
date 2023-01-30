//#pragma once
#ifndef _____STAGE_SELECT_CURSOR_H____
#define _____STAGE_SELECT_CURSOR_H____

#include "Billboard.h"
#include "SceneGame.h"

class StageSelectCursor : public Billboard
{
public:
	StageSelectCursor();
	void Update();

	SceneGame::StageNumber GetStageNum();

private:
	XMFLOAT3 m_TargetPos[SceneGame::E_STAGE_NUMBER_STAGE_MAX];
	SceneGame::StageNumber m_StageNum;
	bool m_MoveFlag;
};

#endif // !_____STAGE_SELECT_CURSOR_H____
