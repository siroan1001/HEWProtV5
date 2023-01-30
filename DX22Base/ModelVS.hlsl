struct VS_IN
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORDO;
	float3 wPos : TEXCOORD1;
};

cbuffer WVP :register(b0)
{
	float4x4 world;		//���[���h�ϊ��s��
	float4x4 view;		//�r���[�ϊ��s��
	float4x4 proj;		//�v���W�F�N�V�����s��
}

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);	//���[�J�����W���烏�[���h���W�֕ϊ�
	vout.wPos = vout.pos;
	vout.pos = mul(vout.pos, view);		//���[���h���W����r���[���W�֕ϊ�
	vout.pos = mul(vout.pos, proj);		//�r���[���W����v���W�F�N�V�������W�֕ϊ�
	vout.normal = mul(vin.normal, world);
	vout.uv = vin.uv;
	return vout;
}