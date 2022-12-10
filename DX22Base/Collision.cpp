// Collision.cpp
// 当たり判定に関する部分
//（tureで衝突、falseで非衝突）
#include "Collision.h"


// 四角形同士の衝突判定を行う関数
bool Collision::RectAndRect(Stage::Info Obj1, Stage::Info Obj2)
{
	Stage::Info Obj1Info;	// 1つ目のオブジェクトの情報を保持するための変数
	Stage::Info Obj2Info;	// 2つ目のオブジェクトの情報を保持するための変数

	Obj1Info = Obj1;
	Obj2Info = Obj2;

	float Obj1Left = Obj1Info.pos.x - Obj1Info.size.x / 2.0f;	// オブジェクト１の左辺
	float Obj1Right = Obj1Info.pos.x + Obj1Info.size.x / 2.0f;	// オブジェクト１の右辺
	float Obj1Top = Obj1Info.pos.y - Obj1Info.size.y / 2.0f;	// オブジェクト１の上辺
	float Obj1Bottom = Obj1Info.pos.y + Obj1Info.size.y / 2.0f;	// オブジェクト１の底辺

	float Obj2Left = Obj2Info.pos.x - Obj2Info.size.x / 2.0f;	// オブジェクト２の左辺
	float Obj2Right = Obj2Info.pos.x + Obj2Info.size.x / 2.0f;	// オブジェクト２の右辺
	float Obj2Top = Obj2Info.pos.y - Obj2Info.size.y / 2.0f;	// オブジェクト２の上辺
	float Obj2Bottom = Obj2Info.pos.y + Obj2Info.size.y / 2.0f;	// オブジェクト２の底辺

	// 衝突判定
	if (Obj1Right >= Obj2Left && Obj1Left <= Obj2Right &&
		Obj1Bottom >= Obj2Top && Obj1Top <= Obj2Bottom)
	{
		return true;
	}

	return false;
}

// 四角形と円の衝突判定を行う関数(２つ目の引数に円の情報を入れること)
bool Collision::RectAndCircle(Stage::Info Obj1, Stage::Info Obj2, float Radius)
{
	Stage::Info Obj1Info;	// 1つ目のオブジェクトの情報を保持するための変数
	Stage::Info Obj2Info;	// 2つ目のオブジェクトの情報を保持するための変数

	Obj1Info = Obj1;
	Obj2Info = Obj2;

	bool nResult = false;	// 衝突の正誤用（これを戻り値にする）

	float Obj1Left = Obj1Info.pos.x - Obj1Info.size.x / 2.0f;	// オブジェクト１の左辺
	float Obj1Right = Obj1Info.pos.x + Obj1Info.size.x / 2.0f;	// オブジェクト１の右辺
	float Obj1Top = Obj1Info.pos.y - Obj1Info.size.y / 2.0f;	// オブジェクト１の上辺
	float Obj1Bottom = Obj1Info.pos.y + Obj1Info.size.y / 2.0f;	// オブジェクト１の底辺



	// 四角形の四辺に対して円の半径分だけ足したとき円が重なっていたら
	if ((Obj2Info.pos.x > Obj1Left - Radius) &&
		(Obj2Info.pos.x < Obj1Right + Radius) &&
		(Obj2Info.pos.y > Obj1Top - Radius) &&
		(Obj2Info.pos.y < Obj1Bottom + Radius))
	{
		nResult = true;
		float fl = Radius * Radius;


		// 左
		if (Obj2.pos.x < Obj1Left)
		{
			// 左上
			if ((Obj2Info.pos.y < Obj1Top))
			{
				if ((DistanceSqrf(Obj1Left, Obj1Top, Obj2Info.pos.x, Obj2Info.pos.y) >= fl))
				{
					nResult = false;
				}
			}
			else
			{
				// 左下
				if ((Obj2Info.pos.y > Obj1Bottom))
				{
					if ((DistanceSqrf(Obj1Left, Obj1Bottom, Obj2Info.pos.x, Obj2Info.pos.y) >= fl))
					{
						nResult = false;
					}
				}
			}
		}
		else
		{
			// 右
			if (Obj2Info.pos.x > Obj1Right)
			{
				// 右上
				if ((Obj2Info.pos.y < Obj1Top))
				{
					if ((DistanceSqrf(Obj1Right, Obj1Top, Obj2Info.pos.x, Obj2Info.pos.y) >= fl))
					{
						nResult = false;
					}
				}
				else
				{
					// 右下
					if ((Obj2Info.pos.y > Obj1Bottom))
					{
						if ((DistanceSqrf(Obj1Right, Obj1Bottom, Obj2Info.pos.x, Obj2Info.pos.y) >= fl))
						{
							nResult = false;
						}
					}
				}
			}
		}
	}

	return nResult;
}

// 円同士の衝突判定を行う関数
bool Collision::CircleAndCircle(Stage::Info Obj1, Stage::Info Obj2, float Radius1, float Radius2)
{
	Stage::Info Obj1Info;	// 1つ目のオブジェクトの情報を保持するための変数
	Stage::Info Obj2Info;	// 2つ目のオブジェクトの情報を保持するための変数

	Obj1Info = Obj1;
	Obj2Info = Obj2;

	float dx = Obj1.pos.x - Obj2.pos.x;
	float dy = Obj1.pos.y - Obj2.pos.y;
	float dr = dx * dx + dy * dy;

	float ar = Radius1 + Radius2;
	float dl = ar * ar;
	if (dr < dl)
	{
		return true;
	}

	return false;
}

// 平方根の計算の計算を多分軽くしてる関数です。
// いらなそうなら直してね
float Collision::DistanceSqrf(const float t_x1, const float t_y1, const float t_x2, const float t_y2)
{
	float dx = t_x2 - t_x1;
	float dy = t_y2 - t_y1;

	return (dx * dx) + (dy * dy);
}

//線同士の判定
//vtx1, vtx2, center, center
//Obj1にshadowBlockを設定する
Collision::Direction Collision::LineAndLine(Stage::Info Obj1, Stage::Info Obj2)
{
	XMFLOAT2 p1 = { Obj1.pos.x, Obj1.pos.y };
	XMFLOAT2 p2 = { Obj2.pos.x, Obj2.pos.y };
	XMFLOAT2 p3;
	XMFLOAT2 p4;

	//左
	p3 = {Obj1.pos.x + Obj1.size.x / 2.0f, Obj1.pos.y + Obj1.size.y / 2.0f};	//左上
	p4 = {Obj1.pos.x + Obj1.size.x / 2.0f, Obj1.pos.y - Obj1.size.y / 2.0f};	//左下

	if (((p1.x - p2.x) * (p3.y - p1.y) + (p1.y - p2.y) * (p1.x - p3.x))
		* ((p1.x - p2.x) * (p4.y - p1.y) + (p1.y - p2.y) * (p1.x - p4.x)) < 0)
	{
		if (((p3.x - p4.x) * (p1.y - p3.y) + (p3.y - p4.y) * (p3.x - p1.x))
			* ((p3.x - p4.x) * (p2.y - p3.y) + (p3.y - p4.y) * (p3.x - p2.x)) < 0)
		{
			return Collision::E_DIRECTION_L;
		}
	}

	//右
	p3 = { Obj1.pos.x - Obj1.size.x / 2.0f, Obj1.pos.y + Obj1.size.y / 2.0f };	//右上
	p4 = { Obj1.pos.x - Obj1.size.x / 2.0f, Obj1.pos.y - Obj1.size.y / 2.0f };	//右下

	if (((p1.x - p2.x) * (p3.y - p1.y) + (p1.y - p2.y) * (p1.x - p3.x))
		* ((p1.x - p2.x) * (p4.y - p1.y) + (p1.y - p2.y) * (p1.x - p4.x)) < 0)
	{
		if (((p3.x - p4.x) * (p1.y - p3.y) + (p3.y - p4.y) * (p3.x - p1.x))
			* ((p3.x - p4.x) * (p2.y - p3.y) + (p3.y - p4.y) * (p3.x - p2.x)) < 0)
		{
			return Collision::E_DIRECTION_R;
		}
	}

	//上
	p3 = { Obj1.pos.x + Obj1.size.x / 2.0f, Obj1.pos.y + Obj1.size.y / 2.0f };	//左上
	p4 = { Obj1.pos.x - Obj1.size.x / 2.0f, Obj1.pos.y + Obj1.size.y / 2.0f };	//右上

	if (((p1.x - p2.x) * (p3.y - p1.y) + (p1.y - p2.y) * (p1.x - p3.x))
		* ((p1.x - p2.x) * (p4.y - p1.y) + (p1.y - p2.y) * (p1.x - p4.x)) < 0)
	{
		if (((p3.x - p4.x) * (p1.y - p3.y) + (p3.y - p4.y) * (p3.x - p1.x))
			* ((p3.x - p4.x) * (p2.y - p3.y) + (p3.y - p4.y) * (p3.x - p2.x)) < 0)
		{
			return Collision::E_DIRECTION_U;
		}
	}

	//下
	p3 = { Obj1.pos.x + Obj1.size.x / 2.0f, Obj1.pos.y - Obj1.size.y / 2.0f };	//左下
	p4 = { Obj1.pos.x - Obj1.size.x / 2.0f, Obj1.pos.y - Obj1.size.y / 2.0f };	//右下

	if (((p1.x - p2.x) * (p3.y - p1.y) + (p1.y - p2.y) * (p1.x - p3.x))
		* ((p1.x - p2.x) * (p4.y - p1.y) + (p1.y - p2.y) * (p1.x - p4.x)) < 0)
	{
		if (((p3.x - p4.x) * (p1.y - p3.y) + (p3.y - p4.y) * (p3.x - p1.x))
			* ((p3.x - p4.x) * (p2.y - p3.y) + (p3.y - p4.y) * (p3.x - p2.x)) < 0)
		{
			return Collision::E_DIRECTION_U;
		}
	}

	return Collision::E_DIRECTION_MAX;
}
