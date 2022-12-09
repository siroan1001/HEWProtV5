#ifndef __GEOMETORY_H__
#define __GEOMETORY_H__

#include "DirectX.h"
#include <DirectXMath.h>

HRESULT InitGeometory();
void UninitGeometory();
void SetGeometoryTranslate(float x, float y, float z);
void SetGeometoryRotation(float x, float y, float z);
void SetGeometoryScaling(float x, float y, float z);
void SetGeometoryVPMatrix(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj);
void DrawBox();
void DrawSphere();
void DrawCylinder();
void DrawCone();
void DrawCapsule();
void DrawArrow();

float GetCylinderRadius();

#endif // __GEOMETORY_H__