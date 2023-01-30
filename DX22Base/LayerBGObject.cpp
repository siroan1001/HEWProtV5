#include "LayerBGObject.h"

LayerBGObject::LayerBGObject()
{
	m_pTree = new Tree;
}

LayerBGObject::~LayerBGObject()
{
	delete m_pTree;
}

void LayerBGObject::Update()
{
	m_pTree->Update();
}

void LayerBGObject::Draw()
{
	m_pTree->Draw();
}

void LayerBGObject::Reset()
{
}
