#include "SamplerState.h"


SamplerState::SamplerState()
	: m_pState(nullptr)
{
}
SamplerState::~SamplerState()
{
	if (m_pState)
	{
		m_pState->Release();
		m_pState = nullptr;
	}
}

HRESULT SamplerState::Create(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address)
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = filter;
	desc.AddressU = address;
	desc.AddressV = address;
	desc.AddressW = address;
	return GetDevice()->CreateSamplerState(&desc, &m_pState);
}
void SamplerState::Bind()
{
	GetContext()->PSSetSamplers(0, 1, &m_pState);
}