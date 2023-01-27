//#pragma once
#ifndef _____SCENE_STAGE_SELECT_H____
#define _____SCENE_STAGE_SELECT_H____

#include "SceneBace.h"
#include "BG.h"
//#include 

class SceneStageSelect : public SceneBace
{
public:
	SceneStageSelect();
	~SceneStageSelect();
	void Update();
	void Draw();

	void ReStart();

private:


};

#endif // !_____SCENE_STAGE_SELECT_H____
