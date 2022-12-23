// Collision.h
// 当たり判定に関する部分

#ifndef _____COLLISION_H____
#define _____COLLISION_H____

#include <DirectXMath.h>
#include "Stage.h"

using namespace DirectX;

class Collision		// 当たり判定に関するクラス
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
	static bool RectAndRect(Object::Info, Object::Info);			// 四角形同士の衝突判定を行う関数
	static Direction RectAndRectDirection(Object::Info, Object::Info, Object::Info, Direction);			// 四角形同士の衝突判定を行う関数(四角１の今ポジ、四角１の後ポジ、四角２の今ポジ、四角２の後ポジ)
	static bool RectAndCircle(Object::Info, Object::Info, float);// 四角形と円の衝突判定を行う関数(２つ目の引数に円の情報を入れること)
	static bool CircleAndCircle(Object::Info, Object::Info, float, float);		// 円同士の衝突判定を行う関数
	static float DistanceSqrf(const float, const float, const float, const float);
	static Direction LineAndLine(Object::Info Obj1, Object::Info Obj2);


private:
	
};

#endif // !_____COLLISION_H____