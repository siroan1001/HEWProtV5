#include "debugbill.h"

DebugBill::DebugBill()
{
	m_billboard.push_back(new Billboard);
	Def::Info info = { {-0.7f, 5.0f, -0.3f}, {16.0f, 3.5f, 0.5f}, {0.0f, 0.0f, 0.0f} };
	m_billboard[0]->SetInfo(info);
}

DebugBill::~DebugBill()
{

}

void DebugBill::Draw()
{
	for (int i = 0; i < m_billboard.size(); i++)
	{
		m_billboard[i]->Draw();
	}
}
