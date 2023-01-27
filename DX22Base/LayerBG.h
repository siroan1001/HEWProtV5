//#pragma once
#ifndef _____LAYER_BG_H____
#define _____LAYER_BG_H____

#include "Layer.h"
#include "BG.h"

class LayerBG : public Layer
{
public:
	LayerBG();
	~LayerBG();
	void Update();
	void Draw();

	void Reset();

private:
	BG* m_pBG;

};

#endif // !
