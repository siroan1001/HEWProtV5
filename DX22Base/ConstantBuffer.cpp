#include "ConstantBuffer.h"


ConstantBuffer::ConstantBuffer()
	: m_pBuffer(nullptr)
{
}
ConstantBuffer::~ConstantBuffer()
{
	if (m_pBuffer)
	{
		m_pBuffer->Release();
		m_pBuffer = nullptr;
	}
}
HRESULT ConstantBuffer::Create(UINT size)
{
	/* 定数バッファ作成時の注意
	定数バッファの大きさは4バイト区切り(
	4バイトアライメント)でないと作成できない
	*/
	HRESULT hr;

	// 作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// バッファの作成
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pBuffer);

	return hr;
}
void ConstantBuffer::Write(const void* pData)
{
	// 定数バッファへの書き込み
	ID3D11DeviceContext* pContext = GetContext();
	pContext->UpdateSubresource(
		m_pBuffer, 0, nullptr, pData, 0, 0
	);
}
void ConstantBuffer::BindVS(UINT slot)
{
	/*
	定数バッファのデータを送る際、
	どの位置に格納するかを1つ目の引数(StartSlot)に
	指定する。
	hlslのコードではregister(bX)でバッファの格納
	位置を決めておく。
	*/
	ID3D11DeviceContext* pContext = GetContext();
	pContext->VSSetConstantBuffers(slot, 1, &m_pBuffer);
}
void ConstantBuffer::BindPS(UINT slot)
{
	ID3D11DeviceContext* pContext = GetContext();
	pContext->PSSetConstantBuffers(slot, 1, &m_pBuffer);
}
