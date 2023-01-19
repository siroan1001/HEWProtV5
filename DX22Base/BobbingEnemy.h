#ifndef _____BOBBING_ENEMY_H____
#define _____BOBBING_ENEMY_H____

#include <DirectXMath.h>
#include "Model.h"
#include "ConstantBuffer.h"
#include "Stage.h"
#include "CameraBase.h"
#include "Collision.h"
#include <vector>
#include "Object.h"

using namespace DirectX;
using namespace std;

class BobbingEnemy : public Object
{
public:
	// ìGÇÃï˚å¸
	enum EnemyDirection
	{
		E_ENEMY_RIGHT,	// âE
		E_ENEMY_LEFT,	// ç∂
		E_PLAYER_DIRECTION_MAX
	};

	float m_life;
	bool m_use;
public:
	BobbingEnemy(Collision::Direction dire, XMFLOAT3 pos, XMFLOAT3 point, int flame);
	void Update();

	Def::Info GetOldInfo();
	Collision::Direction GetDirection();
	void SetDirection(Collision::Direction);

	void SetCollisionPlayer();

private:
	Def::Info m_OldInfo;
	XMFLOAT3 m_Move;
	Collision::Direction m_Direction;		//êiÇÒÇ≈Ç¢ÇÈï˚å¸
	/*vector<Collision::Direction> m_StageDire;*/
	bool m_IsColPlayer;
	XMFLOAT3 m_Start;
	XMFLOAT3 m_Point;
	int m_flame;
	int m_maxflame;
};







#endif // !_____ENEMY_H____