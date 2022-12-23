//#pragma once
#ifndef _____LAYER_GAME_H____
#define _____LAYER_GAME_H____

#include "Layer.h"
#include "Stage.h"
#include "Player.h"
#include "Light.h"
#include "ShadowBlock.h"
#include "ReverseBlock.h"
#include "CameraBase.h"

class LayerGame	: public Layer
{
public:
	LayerGame(CameraBase*);
	~LayerGame();
	void Update();
	void Draw();

	void CheckCollision();

	Player* GetPlayer();

	void SetCamera(CameraBase* camera);

private:
	Stage* m_pStage;
	Player* m_pPlayer;
	Light* m_pLight;
	ShadowBlock* m_pShadowBlock;
	CameraBase* m_pCamera;
	ReverseBlock* m_pRvsBlock;
};

#endif // !_____LAYER_GAME_H____
