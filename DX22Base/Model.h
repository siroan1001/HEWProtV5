#ifndef __MODEL_H__
#define __MODEL_H__

#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"

class Model
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
	};
	struct Material
	{
		DirectX::XMFLOAT4 diffuse;
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 specular;
		ID3D11ShaderResourceView* pTexture;
	};
	struct Mesh
	{
		Vertex* pVertices;
		unsigned int vertexNum;
		unsigned int* pIndices;
		unsigned int indexNum;
		unsigned int materialID;
		MeshBuffer* pMesh;
	};
public:
	Model();
	~Model();

	bool Load(const char* file, float scale = 1.0f, bool flip = false, bool anime = false);
	void Draw();

	void SetVertexShader(VertexShader* vs);
	void SetPixelShader(PixelShader* ps);

	const Mesh* GetMesh(unsigned int index);
	unsigned int GetMeshNum();

private:
	static VertexShader* m_pDefVS;
	static PixelShader* m_pDefPS;
	static unsigned int m_shaderRef;
private:
	Mesh* m_pMeshes;
	unsigned int m_meshNum;
	Material* m_pMaterials;
	unsigned int m_materialNum;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
};


#endif // __MODEL_H__