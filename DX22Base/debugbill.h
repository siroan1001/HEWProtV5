//#pragma once
#ifndef _____DEBUG_BILL_H____
#define _____DEBUG_BILL_H____

#include "Billboard.h"
#include <vector>

using namespace std;

class DebugBill
{
public:
	DebugBill();
	~DebugBill();
	void Draw();

private:
	vector<Billboard*> m_billboard;

};


#endif // !_____DEBUG_BILL_H____
