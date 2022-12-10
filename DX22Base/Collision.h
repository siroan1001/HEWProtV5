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
		E_DIRECTION_L,
		E_DIRECTION_R,
		E_DIRECTION_U,
		E_DIRECTION_D,

		E_DIRECTION_MAX
	};

public:
	static bool RectAndRect(Stage::Info, Stage::Info);			// 四角形同士の衝突判定を行う関数
	static bool RectAndCircle(Stage::Info, Stage::Info, float);// 四角形と円の衝突判定を行う関数(２つ目の引数に円の情報を入れること)
	static bool CircleAndCircle(Stage::Info, Stage::Info, float, float);		// 円同士の衝突判定を行う関数
	static float DistanceSqrf(const float, const float, const float, const float);
	static Direction LineAndLine(Stage::Info Obj1, Stage::Info Obj2);


private:
	
};

#endif // !_____COLLISION_H____