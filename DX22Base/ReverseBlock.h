#pragma once
#ifndef __REVERSEBLOCK_H__
#define __REVERSEBLOCK_H__

#include "Stage.h"
#include "Collision.h"
#include <vector>

class ReverseBlock : public Stage
{
public:
	ReverseBlock();
	~ReverseBlock();

	Collision::Direction GetDirection(int i);

	void Hit(int i);
private:
	vector<Collision::Direction> m_dire;
};

#endif