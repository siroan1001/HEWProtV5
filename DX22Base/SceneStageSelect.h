//#pragma once
#ifndef _____SCENE_STAGE_SELECT_H____
#define _____SCENE_STAGE_SELECT_H____

#include "SceneBace.h"
#include "SceneGame.h"
#include "Game3D.h"
#include "BG.h"
#include "DirectX.h"
#include "Sprite.h" 

class SceneStageSelect : public SceneBace
{
public:
	SceneStageSelect(CameraBase* camera, SceneGame::StageNumber stagenumber);
	~SceneStageSelect();
	void Update();
	void Draw();
	void ReStart();
	void SetCamera(CameraBase* camera);
	static SceneGame::StageNumber GetStageNumber();
private:
	BG* m_pBG;
	CameraBase* m_pCamera;
	static SceneGame::StageNumber m_StageNumber;
};

#endif // !_____SCENE_STAGE_SELECT_H____
