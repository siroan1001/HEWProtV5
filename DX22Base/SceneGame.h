#pragma once

#ifndef _____SCENE_GAME_H____
#define _____SCENE_GAME_H____

#include "SceneBace.h"
#include "BlendState.h"
#include "Layer.h"


class SceneGame : public SceneBace
{
public:
	//enum CameraKind
	//{
	//	E_CAM_MAIN = 0,
	//	E_CAM_EVENT,
	//	E_CAM_DELAY,
	//	E_CAM_DEBUG,

	//	E_CAM_MAX
	//};
	enum LayerKind
	{
		E_LAYER_BG = 0,
		E_LAYER_BUCK_OBJECT,
		E_LAYER_GAME,
		E_LAYER_UI,
		E_LAYER_RESULT,

		E_LAYER_MAX
	};
	enum GameStatus
	{
		E_GAME_STATUS_NOME = 0,
		E_GAME_STATUS_START,
		E_GAME_STATUS_NORMAL,
		E_GAME_STATUS_GAMEOVER,
		E_GAME_STATUS_GOAL,
		E_GAME_STATUS_PAUSE,

		E_GAME_STATUS_MAX
	};
	enum StageNumber
	{
		E_STAGE_NUMBER_STAGE_1 = 0,
		E_STAGE_NUMBER_STAGE_2,
		E_STAGE_NUMBER_STAGE_3,

		E_STAGE_NUMBER_STAGE_MAX
	};

public:
	SceneGame(StageNumber);
	~SceneGame();
	void Update();
	void Draw();

	void ReStart();

	//static CameraBase* GetCamera();
	static GameStatus GetGameStatus();
	static void SetGameStatus(GameStatus);
	static StageNumber* GetStageNum();
	static Layer* GetLayer(LayerKind);


	//void CameraReset();

	void SetStageNumber(StageNumber stagenumber);
private:
	void StageTutoRial();
	void Stage1();
	void UninitStage1();
	void Stage2();
	void Stage3();
	void Stage4();

private:
	BlendState* m_pBlend;
	//static CameraBase* m_pCamera[E_CAM_MAX];
	//static CameraKind m_mainCamera;
	static Layer* m_pLayer[E_LAYER_MAX];
	static GameStatus m_GameStatus;
	//EffectManager* m_pEffect;
	static StageNumber m_StageNuber;

};

#endif // !_____SCENE_GAME_H____
