#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "DirectXTex.h"

HRESULT InitTexture(ID3D11Device* pDevice);
void UninitTexture();
HRESULT LoadTextureFromFile(const char* fileName, ID3D11ShaderResourceView** ppTex);
HRESULT CreateRenderTarget(float width, float height, ID3D11ShaderResourceView** ppTex, ID3D11RenderTargetView** ppRenderTarget);

#endif // __TEXTURE_H__