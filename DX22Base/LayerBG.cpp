#include "LayerBG.h"
#include "Game3D.h"

LayerBG::LayerBG()
{
	m_pBG = new BG(BG::E_BG_KIND_FOREST);
}

LayerBG::~LayerBG()
{
	delete m_pBG;
}

void LayerBG::Update()
{
	m_pBG->Update();
}

void LayerBG::Draw()
{
	m_pBG->Draw();
}

void LayerBG::Reset()
{
	XMFLOAT3 cam = Game3D::GetCamera()->GetInfo().pos;
	m_pBG->SetPos(XMFLOAT3(cam.x, cam.y, -0.25f));
}
