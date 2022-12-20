#pragma once
#ifndef __REVERSEBLOCK_H__
#define __REVERSEBLOCK_H__

#include "Stage.h"

class ReverseBlock : public Stage
{
public:
	ReverseBlock();
	~ReverseBlock();

	void Hit(int i);
private:
	bool flag;
};

#endif