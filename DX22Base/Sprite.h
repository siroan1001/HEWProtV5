#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <DirectXMath.h>
#include "MeshBuffer.h"
#include "ConstantBuffer.h"
#include "Shader.h"

class Sprite
{
public:
	static void Init();
	static void Uninit();
	static void Draw();

	static void SetOffset(DirectX::XMFLOAT2 offset);
	static void SetSize(DirectX::XMFLOAT2 size);
	static void SetUVPos(DirectX::XMFLOAT2 pos);
	static void SetUVScale(DirectX::XMFLOAT2 scale);
	static void SetColor(DirectX::XMFLOAT4 color);
	static void SetTexture(ID3D11ShaderResourceView* pTex);

	static void SetWorld(DirectX::XMFLOAT4X4 world);
	static void SetView(DirectX::XMFLOAT4X4 view);
	static void SetProjection(DirectX::XMFLOAT4X4 proj);

	static void SetDefaultVertexShader();
	static void SetDefaultPixelShader();
	static void SetVertexShader(VertexShader* pVS);
	static void SetPixelShader(PixelShader* pPS);

private:
	static MeshBuffer* m_pMesh;
	static ConstantBuffer* m_pBuf[2];
	static DirectX::XMFLOAT4X4 m_matrix[3];
	static DirectX::XMFLOAT4 m_param[3];
	static ID3D11ShaderResourceView* m_pTexture;
	static VertexShader* m_pVS;
	static PixelShader* m_pPS;
	static VertexShader* m_pDefVS;
	static PixelShader* m_pDefPS;
};

#endif // __SPRITE_H__