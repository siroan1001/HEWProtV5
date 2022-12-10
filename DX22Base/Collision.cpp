// Collision.cpp
// �����蔻��Ɋւ��镔��
//�iture�ŏՓˁAfalse�Ŕ�Փˁj
#include "Collision.h"


// �l�p�`���m�̏Փ˔�����s���֐�
bool Collision::RectAndRect(Stage::Info Obj1, Stage::Info Obj2)
{
	Stage::Info Obj1Info;	// 1�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�
	Stage::Info Obj2Info;	// 2�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�

	Obj1Info = Obj1;
	Obj2Info = Obj2;

	float Obj1Left = Obj1Info.pos.x - Obj1Info.size.x / 2.0f;	// �I�u�W�F�N�g�P�̍���
	float Obj1Right = Obj1Info.pos.x + Obj1Info.size.x / 2.0f;	// �I�u�W�F�N�g�P�̉E��
	float Obj1Top = Obj1Info.pos.y - Obj1Info.size.y / 2.0f;	// �I�u�W�F�N�g�P�̏��
	float Obj1Bottom = Obj1Info.pos.y + Obj1Info.size.y / 2.0f;	// �I�u�W�F�N�g�P�̒��

	float Obj2Left = Obj2Info.pos.x - Obj2Info.size.x / 2.0f;	// �I�u�W�F�N�g�Q�̍���
	float Obj2Right = Obj2Info.pos.x + Obj2Info.size.x / 2.0f;	// �I�u�W�F�N�g�Q�̉E��
	float Obj2Top = Obj2Info.pos.y - Obj2Info.size.y / 2.0f;	// �I�u�W�F�N�g�Q�̏��
	float Obj2Bottom = Obj2Info.pos.y + Obj2Info.size.y / 2.0f;	// �I�u�W�F�N�g�Q�̒��

	// �Փ˔���
	if (Obj1Right >= Obj2Left && Obj1Left <= Obj2Right &&
		Obj1Bottom >= Obj2Top && Obj1Top <= Obj2Bottom)
	{
		return true;
	}

	return false;
}

// �l�p�`�Ɖ~�̏Փ˔�����s���֐�(�Q�ڂ̈����ɉ~�̏������邱��)
bool Collision::RectAndCircle(Stage::Info Obj1, Stage::Info Obj2, float Radius)
{
	Stage::Info Obj1Info;	// 1�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�
	Stage::Info Obj2Info;	// 2�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�

	Obj1Info = Obj1;
	Obj2Info = Obj2;

	bool nResult = false;	// �Փ˂̐���p�i�����߂�l�ɂ���j

	float Obj1Left = Obj1Info.pos.x - Obj1Info.size.x / 2.0f;	// �I�u�W�F�N�g�P�̍���
	float Obj1Right = Obj1Info.pos.x + Obj1Info.size.x / 2.0f;	// �I�u�W�F�N�g�P�̉E��
	float Obj1Top = Obj1Info.pos.y - Obj1Info.size.y / 2.0f;	// �I�u�W�F�N�g�P�̏��
	float Obj1Bottom = Obj1Info.pos.y + Obj1Info.size.y / 2.0f;	// �I�u�W�F�N�g�P�̒��



	// �l�p�`�̎l�ӂɑ΂��ĉ~�̔��a�������������Ƃ��~���d�Ȃ��Ă�����
	if ((Obj2Info.pos.x > Obj1Left - Radius) &&
		(Obj2Info.pos.x < Obj1Right + Radius) &&
		(Obj2Info.pos.y > Obj1Top - Radius) &&
		(Obj2Info.pos.y < Obj1Bottom + Radius))
	{
		nResult = true;
		float fl = Radius * Radius;


		// ��
		if (Obj2.pos.x < Obj1Left)
		{
			// ����
			if ((Obj2Info.pos.y < Obj1Top))
			{
				if ((DistanceSqrf(Obj1Left, Obj1Top, Obj2Info.pos.x, Obj2Info.pos.y) >= fl))
				{
					nResult = false;
				}
			}
			else
			{
				// ����
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
			// �E
			if (Obj2Info.pos.x > Obj1Right)
			{
				// �E��
				if ((Obj2Info.pos.y < Obj1Top))
				{
					if ((DistanceSqrf(Obj1Right, Obj1Top, Obj2Info.pos.x, Obj2Info.pos.y) >= fl))
					{
						nResult = false;
					}
				}
				else
				{
					// �E��
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

// �~���m�̏Փ˔�����s���֐�
bool Collision::CircleAndCircle(Stage::Info Obj1, Stage::Info Obj2, float Radius1, float Radius2)
{
	Stage::Info Obj1Info;	// 1�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�
	Stage::Info Obj2Info;	// 2�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�

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

// �������̌v�Z�̌v�Z�𑽕��y�����Ă�֐��ł��B
// ����Ȃ����Ȃ璼���Ă�
float Collision::DistanceSqrf(const float t_x1, const float t_y1, const float t_x2, const float t_y2)
{
	float dx = t_x2 - t_x1;
	float dy = t_y2 - t_y1;

	return (dx * dx) + (dy * dy);
}

//�����m�̔���
//vtx1, vtx2, center, center
//Obj1��shadowBlock��ݒ肷��
Collision::Direction Collision::LineAndLine(Stage::Info Obj1, Stage::Info Obj2)
{
	XMFLOAT2 p1 = { Obj1.pos.x, Obj1.pos.y };
	XMFLOAT2 p2 = { Obj2.pos.x, Obj2.pos.y };
	XMFLOAT2 p3;
	XMFLOAT2 p4;

	//��
	p3 = {Obj1.pos.x + Obj1.size.x / 2.0f, Obj1.pos.y + Obj1.size.y / 2.0f};	//����
	p4 = {Obj1.pos.x + Obj1.size.x / 2.0f, Obj1.pos.y - Obj1.size.y / 2.0f};	//����

	if (((p1.x - p2.x) * (p3.y - p1.y) + (p1.y - p2.y) * (p1.x - p3.x))
		* ((p1.x - p2.x) * (p4.y - p1.y) + (p1.y - p2.y) * (p1.x - p4.x)) < 0)
	{
		if (((p3.x - p4.x) * (p1.y - p3.y) + (p3.y - p4.y) * (p3.x - p1.x))
			* ((p3.x - p4.x) * (p2.y - p3.y) + (p3.y - p4.y) * (p3.x - p2.x)) < 0)
		{
			return Collision::E_DIRECTION_L;
		}
	}

	//�E
	p3 = { Obj1.pos.x - Obj1.size.x / 2.0f, Obj1.pos.y + Obj1.size.y / 2.0f };	//�E��
	p4 = { Obj1.pos.x - Obj1.size.x / 2.0f, Obj1.pos.y - Obj1.size.y / 2.0f };	//�E��

	if (((p1.x - p2.x) * (p3.y - p1.y) + (p1.y - p2.y) * (p1.x - p3.x))
		* ((p1.x - p2.x) * (p4.y - p1.y) + (p1.y - p2.y) * (p1.x - p4.x)) < 0)
	{
		if (((p3.x - p4.x) * (p1.y - p3.y) + (p3.y - p4.y) * (p3.x - p1.x))
			* ((p3.x - p4.x) * (p2.y - p3.y) + (p3.y - p4.y) * (p3.x - p2.x)) < 0)
		{
			return Collision::E_DIRECTION_R;
		}
	}

	//��
	p3 = { Obj1.pos.x + Obj1.size.x / 2.0f, Obj1.pos.y + Obj1.size.y / 2.0f };	//����
	p4 = { Obj1.pos.x - Obj1.size.x / 2.0f, Obj1.pos.y + Obj1.size.y / 2.0f };	//�E��

	if (((p1.x - p2.x) * (p3.y - p1.y) + (p1.y - p2.y) * (p1.x - p3.x))
		* ((p1.x - p2.x) * (p4.y - p1.y) + (p1.y - p2.y) * (p1.x - p4.x)) < 0)
	{
		if (((p3.x - p4.x) * (p1.y - p3.y) + (p3.y - p4.y) * (p3.x - p1.x))
			* ((p3.x - p4.x) * (p2.y - p3.y) + (p3.y - p4.y) * (p3.x - p2.x)) < 0)
		{
			return Collision::E_DIRECTION_U;
		}
	}

	//��
	p3 = { Obj1.pos.x + Obj1.size.x / 2.0f, Obj1.pos.y - Obj1.size.y / 2.0f };	//����
	p4 = { Obj1.pos.x - Obj1.size.x / 2.0f, Obj1.pos.y - Obj1.size.y / 2.0f };	//�E��

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
