//#pragma once
#ifndef _____LAYER_GAME_H____
#define _____LAYER_GAME_H____

#include "SceneGame.h"
#include "Layer.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "BobbingEnemy.h"
#include "Light.h"
//#include "ShadowBlock.h"
//#include "ReverseBlock.h"
#include "StartObj.h"
#include "ChasingShadow.h"
#include "Goal.h"
#include "CameraBase.h"
#include "Obstacle.h"
#include "EnemyBase.h"

class LayerGame	: public Layer
{
//public:
//	enum EnemyKind
//	{
//		E_ENEMY_KIND_DEF_1 = 0,
//		E_ENEMY_KIND_ROUND_TRIP_1,
//
//		E_ENEMY_KIND_MAX,
//	};

public:
	LayerGame(CameraBase*, SceneGame::GameStatus*, SceneGame::StageNumber);
	~LayerGame();
	void Update();
	void Draw();

	void Reset();

	void CheckCollision();

	Player* GetPlayer();

	void SetCamera(CameraBase* camera);

private:
	Stage* m_pStage;
	Player* m_pPlayer;
	//Enemy* m_pEnemy;
	//BobbingEnemy* m_pBobbingEnemy;
	/*vector<Enemy*> m_pEnemys;*/
	Light* m_pLight;
	//ShadowBlock* m_pShadowBlock;
	CameraBase* m_pCamera;
	//ReverseBlock* m_pRvsBlock;
	StartObj* m_pStartObj;
	ChasingShadow* m_pChasingShadow;
	GoalObj* m_pGoalObj;
	Obstacle* m_pObstacle;
	SceneGame::GameStatus* m_GameStatus;
	//EnemyBase* m_pEnemyBase[E_ENEMY_KIND_MAX];
	vector<EnemyBase*> m_pEnemy;
};

#endif // !_____LAYER_GAME_H____
