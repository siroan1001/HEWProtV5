#include "ShadowBillBoard.h"

ShadowBillBoard::ShadowBillBoard(XMFLOAT3 pos)
{
	LoadTextureFromFile("Assets/ShadowBlock.png", &m_pTex);
	m_Info.Pos = pos;
}
