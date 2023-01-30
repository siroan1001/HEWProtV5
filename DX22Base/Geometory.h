#ifndef __GEOMETORY_H__
#define __GEOMETORY_H__

#include "DirectX.h"
#include <DirectXMath.h>
#include "Lig.h"

HRESULT InitGeometory();
void UninitGeometory();

void SetGeometoryTranslate(float x, float y, float z);
void SetGeometoryRotation(float x, float y, float z);
void SetGeometoryScaling(float x, float y, float z);
void SetGeometoryVPMatrix(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj, DirectX::XMFLOAT3 eyePos);
void SetGeometoryColor(DirectX::XMFLOAT4 color);
void SetGeometoryPtLigPos(DirectX::XMFLOAT3 PtLigPos);
void SetGeometorySpLigPos(DirectX::XMFLOAT3 pos);
Lig::Light GetLig();

void DrawBox();
void DrawSphere();
void DrawCylinder();
void DrawCone();
void DrawCapsule();
void DrawArrow();

float GetCylinderRadius();

#endif // __GEOMETORY_H__