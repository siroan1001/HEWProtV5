#include "LayerBGObject.h"
#include "Game3D.h"

LayerBGObject::LayerBGObject()
{
	float camposx = Game3D::GetCamera()->GetLook().x;
	for (int i = 0; i < 30; i++)
	{
		//Def::Info info = {}
		XMFLOAT3 pos = { camposx, 3.0f, -0.75 };
		m_pTree[i] = new Tree(pos, 1.0f);
		camposx += 2.5f;
	}
}

LayerBGObject::~LayerBGObject()
{
	for (int i = 0; i < 30; i++)
		delete m_pTree[i];
}

void LayerBGObject::Update()
{
	for (int i = 0; i < 30; i++)
	m_pTree[i]->Update();
}

void LayerBGObject::Draw()
{
	for (int i = 0; i < 30; i++)
	m_pTree[i]->Draw();
}

void LayerBGObject::Reset()
{
}
