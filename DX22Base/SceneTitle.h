#ifndef __SCENE_TITLE__
#define __SCENE_TITLE__

#include "SceneBace.h"
#include "SceneGame.h"
#include "Game3D.h"
//#include "TitleUI.h"
#include "BG.h"
#include "DirectX.h"
#include "Sprite.h"

class SceneTitle : public SceneBace
{
public:
	SceneTitle();
	~SceneTitle();

	void Update();
	void Draw();

	void ReStart();

private:

	//TitleUI* m_TitleUI;	//?
	BG* m_pBG;
};

#endif//__SCENE_TITLE__
