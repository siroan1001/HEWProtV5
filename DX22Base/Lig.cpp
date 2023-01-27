#include "Lig.h"

void Lig::InitPtLig(Light& light)
{
	light.ptPos = XMFLOAT3(0.0f, 0.0f, 0.0f); light.ptCol = XMFLOAT3(1.0f, 0.0f, 0.0f);
	light.ptRange = 0.3f;
}
void Lig::InitSpLig(Lig::Light& light){
	light.spPos = XMFLOAT3(0.0f, 5.0f, -5.0f); light.spCol = XMFLOAT3(10.0f, 0.0f, 0.0f); 
	light.spDir = XMFLOAT3(0.0f, 0.0f, -1.0f); XMVECTOR spVec = XMLoadFloat3(&light.spDir); spVec = XMVector3Normalize(spVec); XMStoreFloat3(&light.spDir, spVec);
	light.spRange = 13.0f; light.spAng = XMConvertToRadians(1.7f);
}
void Lig::InitAmLig(Lig::Light& light){
	light.amCol = XMFLOAT3(0.05f, 0.05f, 0.05f);
}