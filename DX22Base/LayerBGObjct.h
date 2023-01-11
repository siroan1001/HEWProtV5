//#pragma once
#ifndef _____LAYER_BG_OBJECT_H____
#define _____LAYER_BG_OBJECT_H____

#include "Layer.h"
#include "debugbill.h"

class LayerBGObject : public Layer
{
public:
	LayerBGObject();
	~LayerBGObject();
	void Update();
	void Draw();

private:
	DebugBill* m_pDebug;

};

#endif // !