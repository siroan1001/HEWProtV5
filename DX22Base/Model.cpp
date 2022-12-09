#include "Model.h"

VertexShader* Model::m_pDefVS = nullptr;
PixelShader* Model::m_pDefPS = nullptr;
unsigned int Model::m_shaderRef = 0;

//--- プロトタイプ宣言
void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps);

Model::Model()
{
	if (m_shaderRef == 0)
	{
		MakeModelDefaultShader(&m_pDefVS, &m_pDefPS);
	}
	m_pVS = m_pDefVS;
	m_pPS = m_pDefPS;
	++m_shaderRef;
}
Model::~Model()
{
	for (unsigned int i = 0; i < m_meshNum; ++i)
	{
		delete[] m_pMeshes[i].pVertices;
		delete[] m_pMeshes[i].pIndices;
		delete m_pMeshes[i].pMesh;
	}
	delete[] m_pMeshes;

	--m_shaderRef;
	if (m_shaderRef <= 0)
	{
		delete m_pDefPS;
		delete m_pDefVS;
	}
}

void Model::SetVertexShader(VertexShader* vs)
{
	m_pVS = vs;
}
void Model::SetPixelShader(PixelShader* ps)
{
	m_pPS = ps;
}
const Model::Mesh* Model::GetMesh(unsigned int index)
{
	if (index >= GetMeshNum())
	{
		return &m_pMeshes[index];
	}
	return nullptr;
}
uint32_t Model::GetMeshNum()
{
	return m_meshNum;
}

void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps)
{
	const char* ModelVS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos.z += 0.5f;
	vout.pos.y -= 0.8f;
	vout.uv = vin.uv;
	return vout;
})EOT";
	const char* ModelPS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET
{
	return tex.Sample(samp, pin.uv);
})EOT";
	*vs = new VertexShader();
	(*vs)->Compile(ModelVS);
	*ps = new PixelShader();
	(*ps)->Compile(ModelPS);
}