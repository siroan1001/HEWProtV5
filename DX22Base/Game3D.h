#ifndef __GAME_3D_H__
#define __GAME_3D_H__

#include "SceneBace.h"
#include "CameraBase.h"

class Game3D
{
public:
	enum SceneKind
	{
		E_SCENE_KIND_TITLE = 0,
		E_SCENE_KIND_GAME,
		E_SCENE_KIND_RESULT,
		E_SCENE_KIND_CLEAR,

		E_SCENE_KIND_MAX
	};
	enum CameraKind
	{
		E_CAM_MAIN = 0,
		E_CAM_EVENT,
		E_CAM_DELAY,
		E_CAM_DEBUG,

		E_CAM_MAX
	};

public:
	Game3D();
	~Game3D();
	void Update();
	void Draw();
	static SceneBace* GetScene();
	static void SetScene(SceneKind nextScene);
	static CameraBase* GetCamera();

private:
	static SceneBace* m_pScene[E_SCENE_KIND_MAX];
	static SceneKind m_SceneKind;
	static CameraBase* m_pCamera[E_CAM_MAX];
	static CameraKind m_mainCamera;

};

#endif // __GAME_3D_H__