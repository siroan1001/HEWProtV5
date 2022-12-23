#include "MeshBuffer.h"
#include <crtdbg.h>

MeshBuffer::MeshBuffer(Description desc)
	: m_pVtxBuf(nullptr)
	, m_pIdxBuf(nullptr)
	, m_desc(desc)
{
	_ASSERT_EXPR(SUCCEEDED(CreateVertexBuffer()),
		L"Create failed vertex buffer.");
	_ASSERT_EXPR(SUCCEEDED(CreateIndexBuffer()),
		L"Create failed index buffer.");
}
MeshBuffer::~MeshBuffer()
{
	if (m_pVtxBuf)
	{
		m_pVtxBuf->Release();
		m_pVtxBuf = nullptr;
	}
	if (m_pIdxBuf)
	{
		m_pIdxBuf->Release();
		m_pIdxBuf = nullptr;
	}
}
void MeshBuffer::Write(void* pVtx)
{
#if 0 // ポリライン実装時に解禁
	if (!m_desc.isWrite) { return; }

	ID3D11DeviceContext* pContext = DirectX11::GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;

	if (FAILED(pContext->Map(m_pVtxBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource)))
	{
		return;
	}

	rsize_t size = m_desc.vtxCount * m_desc.vtxSize;
	memcpy_s(mapResource.pData, size, pVtx, size);
	pContext->Unmap(m_pVtxBuf, 0);
#endif
}
void MeshBuffer::Draw()
{
	ID3D11DeviceContext* pContext = GetContext();

	pContext->IASetPrimitiveTopology(m_desc.topology);

	UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, &m_pVtxBuf, &m_desc.vtxSize, &offset);

	if (m_pIdxBuf)
	{
		DXGI_FORMAT format;
		switch (m_desc.idxSize)
		{
		default: _ASSERT_EXPR(false, "undefined index size."); break;
		case 1: format = DXGI_FORMAT_R8_UINT; break;
		case 2: format = DXGI_FORMAT_R16_UINT; break;
		case 4: format = DXGI_FORMAT_R32_UINT; break;
		}
		pContext->IASetIndexBuffer(m_pIdxBuf, format, 0);
		pContext->DrawIndexed(m_desc.idxCount, 0, 0);
	}
	else
	{
		pContext->Draw(m_desc.vtxCount, 0);
	}
}

HRESULT MeshBuffer::CreateVertexBuffer()
{
	//--- 作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = m_desc.vtxSize * m_desc.vtxCount;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (m_desc.isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	//--- バッファの初期値を設定
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = m_desc.pVtx;

	//--- 頂点バッファの作成
	return GetDevice()->CreateBuffer(&bufDesc, &subResource, &m_pVtxBuf);
}
HRESULT MeshBuffer::CreateIndexBuffer()
{
	if (m_desc.pIdx == nullptr)	return S_OK;

	// バッファの情報を設定
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = m_desc.idxSize * m_desc.idxCount;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// バッファの初期データ
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = m_desc.pIdx;

	// インデックスバッファ生成
	return GetDevice()->CreateBuffer(&bufDesc, &subResource, &m_pIdxBuf);
}