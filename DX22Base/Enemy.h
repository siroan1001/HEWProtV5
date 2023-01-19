#ifndef _____ENEMY_H____
#define _____ENEMY_H____

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

class Enemy : public Object
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
	Enemy(Collision::Direction dire, XMFLOAT3 pos);
	void Update();

	void SetPos(XMFLOAT3 pos);

	void InitDirection(int num);

	void ResetMove();


	Def::Info GetOldInfo();
	Collision::Direction GetDirection();
	Collision::Direction GetStageCollistonDirection(int num);
	void SetStageCollisionDirection(Collision::Direction dire, int num);
	void SetDirection(Collision::Direction);

	void SetCollisionPlayer();


private:
	Def::Info m_OldInfo;//
	bool m_Ground;
	XMFLOAT3 m_Move;//
	Collision::Direction m_Direction;//		//êiÇÒÇ≈Ç¢ÇÈï˚å¸
	vector<Collision::Direction> m_StageDire;
	float m_Spead;
	bool m_IsColPlayer;//


};







#endif // !_____ENEMY_H____