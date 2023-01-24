#ifndef __SCENE_RESULT__
#define __SCENE_RESULT__

#include "SceneBace.h"
#include "SceneGame.h"
#include "Game3D.h"
#include "BG.h"
#include "ResultBillboard.h"
#include "DirectX.h"
#include "Sprite.h"

class SceneResult : public SceneBace
{
private:
	enum ResultStatus
	{
		E_RESULT_STATUS_NOME = 0,
		E_RESULT_STATUS_START,
		E_RESULT_STATUS_NORMAL,
		E_GAME_STATUS_MAX
	};
public:
	SceneResult();
	~SceneResult();

	void Update();
	void Draw();

private:
	static ResultStatus m_ResultStatus;
	ResultBillboard* m_pResultBill;
	BG* m_pBG;
	int m_flame;
};

#endif//__SCENE_RESULT__

