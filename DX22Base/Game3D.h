#ifndef __GAME_3D_H__
#define __GAME_3D_H__

#include "CameraBase.h"
#include "Stage.h"
#include "Player.h"
#include "ShadowBlock.h"
#include "Light.h"
#include "Layer.h"

class Game3D
{
public:
	enum CameraKind
	{
		E_CAM_MAIN = 0,
		E_CAM_DEBUG,

		E_CAM_MAX
	};
	enum LayerKind
	{
		E_LAYER_BG = 0,
		E_LAYER_BUCK_OBJECT,
		E_LAYER_GAME,
		E_LAYER_UI,

		E_LAYER_MAX,
	};

public:
	Game3D();
	~Game3D();
	void Update();
	void Draw();

private:
	CameraBase* m_pCamera[E_CAM_MAX];
	CameraKind m_mainCamera;
	Layer* m_pLayer[E_LAYER_MAX];

};

#endif // __GAME_3D_H__