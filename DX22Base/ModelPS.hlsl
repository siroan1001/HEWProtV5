struct PS_IN
{
	float4 pos    : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv     : TEXCOORD0;
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
cbuffer COLOR : register(b1) {
	float4 color;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float3 CalcLambertFromLight(float3 Direction, float3 Color, float3 Pixelnormal);
float3 CalcPhongSpecularFromLight(float3 Direction, float3 Color, float3 wPos, float3 Pixelnormal);
float3 CalcLightFromSpotLight(PS_IN pin);
float4 main(PS_IN pin) : SV_TARGET
{
	float4 finalColor = color;
	pin.normal = normalize(pin.normal);
	float3 spotLig = CalcLightFromSpotLight(pin);
	float3 finalLig = spotLig + amCol;
	finalColor.rgb *= finalLig;
	return tex.Sample(samp, pin.uv) * finalColor;
}
float3 CalcLambertFromLight(float3 Direction, float3 Color, float3 Pixelnormal) {
	float t = dot(Pixelnormal, Direction) * -1.0f; t = max(0.0f, t); return Color * t;
}
float3 CalcPhongSpecularFromLight(float3 Direction, float3 Color, float3 wPos, float3 Pixelnormal) {
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