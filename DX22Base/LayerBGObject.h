#pragma once

#include "Layer.h"
#include "Tree.h"

class LayerBGObject : public Layer
{
public:
	LayerBGObject();
	~LayerBGObject();
	void Update();
	void Draw();

	void Reset();

private:
	Tree* m_pTree;

};