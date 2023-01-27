#ifndef __SCENE_CLEAR__
#define __SCENE_CLEAR__

#include "SceneBace.h"
#include "SceneGame.h"
#include "Game3D.h"
#include "BG.h"
#include "ClearBillboard.h"
#include "DirectX.h"
#include "Sprite.h"

class SceneClear : public SceneBace
{
private:
	enum ClearStatus
	{
		E_CLEAR_STATUS_NOME = 0,
		E_CLEAR_STATUS_START,
		E_CLEAR_STATUS_NORMAL,
		E_CLEAR_STATUS_MAX
	};
public:
	SceneClear();
	~SceneClear();

	void Update();
	void Draw();

	void ReStart();

private:
	static ClearStatus m_ClearStatus;
	ClearBillboard* m_pClearBill;
	BG* m_pBG;
	int m_flame;
};

#endif//__SCENE_CLEAR__


