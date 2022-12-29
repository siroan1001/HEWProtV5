// Collision.h
// �����蔻��Ɋւ��镔��

#ifndef _____COLLISION_H____
#define _____COLLISION_H____

#include <DirectXMath.h>
#include "Stage.h"
#include "Def.h"

using namespace DirectX;

class Collision		// �����蔻��Ɋւ���N���X
{
public:
	enum Direction
	{
		E_DIRECTION_NULL = 0,
		E_DIRECTION_L,
		E_DIRECTION_R,
		E_DIRECTION_U,
		E_DIRECTION_D,

		E_DIRECTION_MAX
	};

	struct LinePos
	{
		float L;
		float R;
		float T;
		float B;
	};

	struct Hit
	{
		bool x;
		bool y;
	};

public:
	static bool RectAndRect(Def::Info, Def::Info);			// �l�p�`���m�̏Փ˔�����s���֐�
	static Direction RectAndRectDirection(Def::Info, Def::Info, Def::Info, Direction);			// �l�p�`���m�̏Փ˔�����s���֐�(�l�p�P�̍��|�W�A�l�p�P�̌�|�W�A�l�p�Q�̍��|�W�A�l�p�Q�̌�|�W)
	static bool RectAndCircle(Def::Info, Def::Info, float);// �l�p�`�Ɖ~�̏Փ˔�����s���֐�(�Q�ڂ̈����ɉ~�̏������邱��)
	static bool CircleAndCircle(Def::Info, Def::Info, float, float);		// �~���m�̏Փ˔�����s���֐�
	static float DistanceSqrf(const float, const float, const float, const float);
	static Direction LineAndLine(Def::Info Obj1, Def::Info Obj2);


private:
	
};

#endif // !_____COLLISION_H____