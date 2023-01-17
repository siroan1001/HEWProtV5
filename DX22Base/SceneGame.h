#pragma once

#ifndef _____SCENE_GAME_H____
#define _____SCENE_GAME_H____

#include "SceneBace.h"
#include "BlendState.h"
#include "CameraBase.h"
#include "Stage.h"
#include "Player.h"
#include "ShadowBlock.h"
#include "Light.h"
#include "Layer.h"

class SceneGame : public SceneBace
{
public:
	enum CameraKind
	{
		E_CAM_MAIN = 0,
		E_CAM_EVENT,
		E_CAM_DELAY,
		E_CAM_DEBUG,

		E_CAM_MAX
	};
	enum LayerKind
	{
		E_LAYER_BG = 0,
		E_LAYER_BUCK_OBJECT,
		E_LAYER_GAME,
		E_LAYER_UI,

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

public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

	static CameraBase* GetCamera();
	static GameStatus GetGameStatus();
	static void SetGameStatus(GameStatus);

private:
	BlendState* m_pBlend;
	static CameraBase* m_pCamera[E_CAM_MAX];
	static CameraKind m_mainCamera;
	Layer* m_pLayer[E_LAYER_MAX];
	static GameStatus m_GameStatus;

};

#endif // !_____SCENE_GAME_H____
