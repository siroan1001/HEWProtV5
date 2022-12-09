// Collision.h
// �����蔻��Ɋւ��镔��

#ifndef _____COLLISION_H____
#define _____COLLISION_H____

#include <DirectXMath.h>
#include "Stage.h"

using namespace DirectX;

class Collision		// �����蔻��Ɋւ���N���X
{
public:
	static bool RectAndRect(Stage::Info, Stage::Info);			// �l�p�`���m�̏Փ˔�����s���֐�
	static bool RectAndCircle(Stage::Info, Stage::Info, float);// �l�p�`�Ɖ~�̏Փ˔�����s���֐�(�Q�ڂ̈����ɉ~�̏������邱��)
	static bool CircleAndCircle(Stage::Info, Stage::Info, float, float);		// �~���m�̏Փ˔�����s���֐�
	static float DistanceSqrf(const float, const float, const float, const float);

private:
	
};

#endif // !_____COLLISION_H____