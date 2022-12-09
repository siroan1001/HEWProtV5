#ifndef __GAME_3D_H__
#define __GAME_3D_H__

#include "CameraBase.h"
#include "Stage.h"
#include "Player.h"
#include "ShadowBlock.h"
#include "Light.h"

class Game3D
{
public:
	Game3D();
	~Game3D();

	void Update();
	void Draw();

	void CheckCollision();

private:
	enum CameraKind
	{
		//E_CAM_PLAYER = 0,
		//E_CAM_DEBUG,
		//E_CAM_EVENT,
		//E_MAX_CAMERA

		E_CAM_MAIN = 0,
		E_CAM_DEBUG,

		E_CAM_MAX
	};

	CameraBase* m_pCamera[E_CAM_MAX];
	Stage* m_pStage;
	Player* m_pPlayer;
	Light* m_pLight;
	ShadowBlock* m_pShadowBlock;
	CameraKind m_mainCamera;
	bool m_cylinderFlag;
};

#endif // __GAME_3D_H__