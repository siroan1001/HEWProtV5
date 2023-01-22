#include "Sprite.h"

MeshBuffer*					Sprite::m_pMesh;
ConstantBuffer*				Sprite::m_pBuf[2];
DirectX::XMFLOAT4X4			Sprite::m_matrix[3];
DirectX::XMFLOAT4			Sprite::m_param[3];
ID3D11ShaderResourceView*	Sprite::m_pTexture;
VertexShader*				Sprite::m_pVS;
PixelShader*				Sprite::m_pPS;
VertexShader*				Sprite::m_pDefVS;
PixelShader*				Sprite::m_pDefPS;
ConstantBuffer*             Sprite::m_pBufLig;
Lig::Light                  Sprite::m_ConBufLig;
Lig*                        Sprite::m_pLight;

void Sprite::Init()
{
	const char* VS = R"EOT(
struct VS_IN {
	float3 pos    : POSITION0;
	float2 uv     : TEXCOORD0;
    float3 normal : NORMAL;
};
struct VS_OUT {
	float4 pos    : SV_POSITION;
	float2 uv     : TEXCOORD0;
    float3 normal : NORMAL;
	float4 color  : COLOR0;
    float3 wPos   : TEXCOORD1;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
cbuffer Param : register(b1) {
	float2 offset;
	float2 size;
	float2 uvPos;
	float2 uvScale;
	float4 color;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos.xy *= size;
	vout.pos.xy += offset;
	vout.pos = mul(vout.pos, world);
    vout.wPos = vout.pos;
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
    vout.normal = mul(vin.normal, world);
	vout.uv = vin.uv;
	vout.uv *= uvScale;
	vout.uv += uvPos;
	vout.color = color;
	return vout;
})EOT";
	const char* PS = R"EOT(
struct PS_IN {
	float4 pos    : SV_POSITION;
	float2 uv     : TEXCOORD0;
    float3 normal : NORMAL;
	float4 color  : COLOR0;
    float3 wPos   : TEXCOORD1;
};
cbuffer LIGHT : register(b0) {
    float3 spPos;
    float3 spCol;
    float spRange;
    float3 spDir;
	float spAng;
	float3 eyePos;
	float3 amCol;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float3 CalcLambertFromLight(float3 Direction, float3 Color, float3 Pixelnormal);
float3 CalcPhongSpecularFromLight(float3 Direction, float3 Color, float3 wPos, float3 Pixelnormal);
float3 CalcLightFromSpotLight(PS_IN pin);
float4 main(PS_IN pin) : SV_TARGET {
    pin.normal = normalize(pin.normal);
    float3 spotLig = CalcLightFromSpotLight(pin);  
    float3 finalLig = spotLig + amCol;
    pin.color.rgb *= finalLig;
	return tex.Sample(samp, pin.uv) * pin.color;
}
float3 CalcLambertFromLight(float3 Direction, float3 Color, float3 Pixelnormal){
    float t = dot(Pixelnormal, Direction) * -1.0f; t = max(0.0f, t); return Color * t;
}
float3 CalcPhongSpecularFromLight(float3 Direction, float3 Color, float3 wPos, float3 Pixelnormal){
   float3 refVec = reflect(Direction, Pixelnormal); float3 toEye = eyePos - wPos; toEye = normalize(toEye);
   float t = dot(refVec, toEye); t = max(0.0f, t); t = pow(t, 3.0f); return Color * t;
}
float3 CalcLightFromSpotLight(PS_IN pin)
{
   float3 spIncidentVec = pin.wPos - spPos; spIncidentVec = normalize(spIncidentVec);
   float3 diffuseSpLig = CalcLambertFromLight(spIncidentVec, spCol, pin.normal); float3 specularSpLig = CalcPhongSpecularFromLight(spIncidentVec, spCol, pin.wPos, pin.normal);
   float3 distance = length(pin.wPos - spPos); float affect = 1.0f - 1.0f / spRange * distance; 
   if (affect < 0.0f) affect = 0.0f; 
   affect = pow(affect, 2.0f); diffuseSpLig *= affect; specularSpLig *= affect;
   float angle = dot(spIncidentVec, spDir); angle = abs(acos(angle)); affect = 1.0f - 1.0f / spAng * angle; 
   if (affect < 0.0f) affect = 0.0f;
   affect = pow(affect, 0.5f); diffuseSpLig *= affect; specularSpLig *= affect; 
   return diffuseSpLig + specularSpLig;
}
)EOT";

	struct Vertex
	{
		float pos[3];
		float uv[2];
		float normal[3];
	} vtx[] = {
		{{-0.5f, 0.5f, 0.0f},  {0.0f, 0.0f}, { 0.0f, 0.0f, -1.0f }},
		{{ 0.5f, 0.5f, 0.0f},  {1.0f, 0.0f}, { 0.0f, 0.0f, -1.0f }},
		{{-0.5f,-0.5f, 0.0f},  {0.0f, 1.0f}, { 0.0f, 0.0f, -1.0f }},
		{{ 0.5f,-0.5f, 0.0f},  {1.0f, 1.0f}, { 0.0f, 0.0f, -1.0f }},
	};

	// メッシュ
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxSize = sizeof(Vertex);
	desc.vtxCount = _countof(vtx);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	m_pMesh = new MeshBuffer(desc);

	// 定数バッファ
	m_pBuf[0] = new ConstantBuffer;
	m_pBuf[0]->Create(sizeof(m_matrix));
	m_pBuf[1] = new ConstantBuffer;
	m_pBuf[1]->Create(sizeof(m_param));

	// パラメーター
	m_param[0] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_param[1] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_param[2] = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	DirectX::XMStoreFloat4x4(&m_matrix[0], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_matrix[1], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_matrix[2], DirectX::XMMatrixIdentity());

	// シェーダー
	m_pDefVS = new VertexShader;
	m_pDefVS->Compile(VS);
	m_pDefPS = new PixelShader;
	m_pDefPS->Compile(PS);
	m_pVS = m_pDefVS;
	m_pPS = m_pDefPS;

	m_pLight = new Lig;
	m_pBufLig = new ConstantBuffer();
	m_pBufLig->Create(sizeof(m_ConBufLig));
	m_ConBufLig.eyePos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pLight->InitSpLig(m_ConBufLig);
	m_pLight->InitAmLig(m_ConBufLig);
	m_pBufLig->Write(&m_ConBufLig);
}
void Sprite::Uninit()
{
	delete m_pBufLig;
	delete m_pLight;
	delete m_pDefPS;
	delete m_pDefVS;
	delete m_pBuf[1];
	delete m_pBuf[0];
	delete m_pMesh;
}
void Sprite::Draw()
{
	m_pVS->Bind();
	m_pPS->Bind();
	m_pBuf[0]->Write(m_matrix);
	m_pBuf[0]->BindVS(0);
	m_pBuf[1]->Write(m_param);
	m_pBuf[1]->BindVS(1);
	m_pBufLig->Write(&m_ConBufLig);
	m_pBufLig->BindPS(0);
	SetTexturePS(m_pTexture, 0);
	m_pMesh->Draw();
}

void Sprite::SetOffset(DirectX::XMFLOAT2 offset)
{
	m_param[0].x = offset.x;
	m_param[0].y = offset.y;
}
void Sprite::SetSize(DirectX::XMFLOAT2 size)
{
	m_param[0].z = size.x;
	m_param[0].w = size.y;
}

void Sprite::SetUVPos(DirectX::XMFLOAT2 pos)
{
	m_param[1].x = pos.x;
	m_param[1].y = pos.y;
}
void Sprite::SetUVScale(DirectX::XMFLOAT2 scale)
{
	m_param[1].x = scale.x;
	m_param[1].y = scale.y;
}
void Sprite::SetColor(DirectX::XMFLOAT4 color)
{
	m_param[2] = color;
}
//--- ライトを定数バッファに設定
void Sprite::SetLig(Lig::Light lig)
{
	m_ConBufLig = lig;
	m_ConBufLig.amCol.x = 1.0f;
	m_ConBufLig.amCol.y = 1.0f;
	m_ConBufLig.amCol.z = 1.0f;
}
void Sprite::SetTexture(ID3D11ShaderResourceView* pTex)
{
	m_pTexture = pTex;
}
void Sprite::SetWorld(DirectX::XMFLOAT4X4 world)
{
	m_matrix[0] = world;
}
void Sprite::SetView(DirectX::XMFLOAT4X4 view)
{
	m_matrix[1] = view;
}
void Sprite::SetProjection(DirectX::XMFLOAT4X4 proj)
{
	m_matrix[2] = proj;
}
void Sprite::SetDefaultVertexShader()
{
	m_pVS = m_pDefVS;
}
void Sprite::SetDefaultPixelShader()
{
	m_pPS = m_pDefPS;
}
void Sprite::SetVertexShader(VertexShader* pVS)
{
	m_pVS = pVS;
}
void Sprite::SetPixelShader(PixelShader* pPS)
{
	m_pPS = pPS;
}
