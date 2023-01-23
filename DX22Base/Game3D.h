#ifndef __GAME_3D_H__
#define __GAME_3D_H__

#include "SceneBace.h"

class Game3D
{
public:
	enum SceneKind
	{
		E_SCENE_KIND_TITLE = 0,
		E_SCENE_KIND_GAME,

		E_SCENE_KIND_MAX
	};

public:
	Game3D();
	~Game3D();
	void Update();
	void Draw();
	static void SetScene(SceneKind nextScene);

private:
	static SceneBace* m_pScene[E_SCENE_KIND_MAX];
	static SceneKind m_SceneKind;

};

#endif // __GAME_3D_H__