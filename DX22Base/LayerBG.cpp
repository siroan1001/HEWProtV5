#include "LayerBG.h"

LayerBG::LayerBG()
{
	m_pBG = new BG;
}

LayerBG::~LayerBG()
{
	delete m_pBG;
}

void LayerBG::Update()
{
}

void LayerBG::Draw()
{
	m_pBG->Draw();
}
