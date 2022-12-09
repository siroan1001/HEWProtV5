struct VS_IN
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORDO;
};

cbuffer WVP :register(b0)
{
	float4x4 world;		//ワールド変換行列
	float4x4 view;		//ビュー変換行列
	float4x4 proj;		//プロジェクション行列
}

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);	//ローカル座標からワールド座標へ変換
	vout.pos = mul(vout.pos, view);		//ワールド座標からビュー座標へ変換
	vout.pos = mul(vout.pos, proj);		//ビュー座標からプロジェクション座標へ変換
	vout.uv = vin.uv;
	return vout;
}