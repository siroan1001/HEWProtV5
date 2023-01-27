//#pragma once
#ifndef _____LAYER_RESULT_H____
#define _____LAYER_RESULT_H____

#include "Layer.h"
#include "ResultBillboard.h"
#include "ClearBillboard.h"

class LayerResult : public Layer
{
public:
	LayerResult();
	~LayerResult();
	void Update();
	void Draw();

	void Reset();

private:
	ResultBillboard* m_pResultBill;
	ClearBillboard* m_pClearBill;
};

#endif // !
