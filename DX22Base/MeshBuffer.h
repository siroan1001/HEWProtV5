#ifndef __MESH_BUFFER_H__
#define __MESH_BUFFER_H__

#include "DirectX.h"

class MeshBuffer
{
public:
	struct Description
	{
		const void* pVtx;
		UINT vtxSize;
		UINT vtxCount;
		bool isWrite;
		const void* pIdx;
		UINT idxSize;
		UINT idxCount;
		D3D11_PRIMITIVE_TOPOLOGY topology;
	};
public:
	MeshBuffer(Description desc);
	~MeshBuffer();

	void Write(void* pVtx);
	void Draw();

private:
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();

private:
	ID3D11Buffer* m_pVtxBuf;
	ID3D11Buffer* m_pIdxBuf;
	Description m_desc;
};

#endif // __MESH_BUFFER_H__