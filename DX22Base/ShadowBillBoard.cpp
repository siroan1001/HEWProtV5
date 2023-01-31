#include "ShadowBillBoard.h"
#include "ModelList.h"

ShadowBillBoard::ShadowBillBoard(Billboard::Info info)
{
	m_pTex = ModelList::GetTexture();
	m_Info = info;
}
