// Collision.cpp
// �����蔻��Ɋւ��镔��
//�iture�ŏՓˁAfalse�Ŕ�Փˁj
#include "Collision.h"
#include "Def.h"

using namespace DirectX;

// �l�p�`���m�̏Փ˔�����s���֐�
bool Collision::RectAndRect(Def::Info Obj1, Def::Info Obj2)
{
	Def::Info Obj1Info;	// 1�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�
	Def::Info Obj2Info;	// 2�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�	

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

//�l�p�`���m�̓����蔻�������Ăǂ̕������瓖����������Ԃ�
Collision::Direction Collision::RectAndRectDirection(Def::Info Nobj1, Def::Info Oobj1, Def::Info obj2, Collision::Direction dire)
{
	LinePos ObjLine[3];		//���̃|�W�V�������i�[

	//���̃L�����N�^�[�̍��W
	ObjLine[0].L = Nobj1.pos.x + Nobj1.size.x / 2.0f;
	ObjLine[0].R = Nobj1.pos.x - Nobj1.size.x / 2.0f;
	ObjLine[0].T = Nobj1.pos.y + Nobj1.size.y / 2.0f;
	ObjLine[0].B = Nobj1.pos.y - Nobj1.size.y / 2.0f;

	//�O�t���[���̃L�����N�^�[�̍��W
	ObjLine[1].L = Oobj1.pos.x + Oobj1.size.x / 2.0f;
	ObjLine[1].R = Oobj1.pos.x - Oobj1.size.x / 2.0f;
	ObjLine[1].T = Oobj1.pos.y + Oobj1.size.y / 2.0f;
	ObjLine[1].B = Oobj1.pos.y - Oobj1.size.y / 2.0f;

	//�u���b�N�̍��W
	ObjLine[2].L = obj2.pos.x + obj2.size.x / 2.0f;
	ObjLine[2].R = obj2.pos.x - obj2.size.x / 2.0f;
	ObjLine[2].T = obj2.pos.y + obj2.size.y / 2.0f;
	ObjLine[2].B = obj2.pos.y - obj2.size.y / 2.0f;

	//�������Ă��Ȃ����NULL��Ԃ�
	if (!(ObjLine[0].R < ObjLine[2].L && ObjLine[0].L > ObjLine[2].R &&
		ObjLine[0].B < ObjLine[2].T && ObjLine[0].T > ObjLine[2].B))
	{
		return E_DIRECTION_NULL;
	}

	//�O�t���[���̃L�����N�^�[�ƃu���b�N���������Ă邩�c���ʂɊi�[
	Hit Old = { false, false };

	if (ObjLine[1].R < ObjLine[2].L && ObjLine[1].L > ObjLine[2].R)
	{//��
		Old.x = true;
	}
	if (ObjLine[1].B < ObjLine[2].T && ObjLine[1].T > ObjLine[2].B)
	{//�c
		Old.y = true;
	}

	if (!Old.x && Old.y)
	{//�O�t���[���f�c�����������Ă����ꍇ�i�������̓�����j
		if (Nobj1.pos.x > obj2.pos.x)
		{//��
			return E_DIRECTION_L;
		}
		else if (Nobj1.pos.x <= obj2.pos.x)
		{//�E
			return E_DIRECTION_R;
		}
	}
	else if(Old.x && !Old.y)
	{//�O�t���[���f�������������Ă����ꍇ�i�c�����̓�����j
		if (Nobj1.pos.y > obj2.pos.y)
		{//��
			return E_DIRECTION_U;
		}
		else if (Nobj1.pos.y <= obj2.pos.y)
		{//��
			return E_DIRECTION_D;
		}
	}
	
	//�O�t���[���Ŋ��ɓ������Ă����ꍇ�O�t���[���Ɠ����������J��Ԃ�
	return dire;

}

// �l�p�`�Ɖ~�̏Փ˔�����s���֐�(�Q�ڂ̈����ɉ~�̏������邱��)
bool Collision::RectAndCircle(Def::Info Obj1, Def::Info Obj2, float Radius)
{
	Def::Info Obj1Info;	// 1�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�
	Def::Info Obj2Info;	// 2�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�

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
bool Collision::CircleAndCircle(Def::Info Obj1, Def::Info Obj2, float Radius1, float Radius2)
{
	Def::Info Obj1Info;	// 1�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�
	Def::Info Obj2Info;	// 2�ڂ̃I�u�W�F�N�g�̏���ێ����邽�߂̕ϐ�

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
Collision::Direction Collision::LineAndLine(Def::Info Obj1, Def::Info Obj2)
{
	XMFLOAT2 p1 = { Obj1.pos.x, Obj1.pos.y };
	XMFLOAT2 p2 = { Obj2.pos.x, Obj2.pos.y };
	XMFLOAT2 p3;
	XMFLOAT2 p4;

	XMFLOAT2 vtx[] = {
		{ Obj1.pos.x + Obj1.size.x / 2.0f, Obj1.pos.y + Obj1.size.y / 2.0f },	//����
		{ Obj1.pos.x + Obj1.size.x / 2.0f, Obj1.pos.y - Obj1.size.y / 2.0f },	//����
		{ Obj1.pos.x - Obj1.size.x / 2.0f, Obj1.pos.y + Obj1.size.y / 2.0f },	//�E��
		{ Obj1.pos.x - Obj1.size.x / 2.0f, Obj1.pos.y - Obj1.size.y / 2.0f }	//�E��
	};

	//��
	p3 = vtx[0];	//����
	p4 = vtx[1];	//����

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
	p3 = vtx[2];	//�E��
	p4 = vtx[3];	//�E��

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
	p3 = vtx[0];	//����
	p4 = vtx[2];	//�E��

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
	p3 = vtx[1];	//����
	p4 = vtx[3];	//�E��

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
