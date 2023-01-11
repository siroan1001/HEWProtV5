#include "LayerBGObjct.h"

LayerBGObject::LayerBGObject()
{
	m_pDebug = new DebugBill;
}

LayerBGObject::~LayerBGObject()
{
	delete m_pDebug;
}

void LayerBGObject::Update()
{
	//m_pDebug.
}

void LayerBGObject::Draw()
{
	m_pDebug->Draw();
}
