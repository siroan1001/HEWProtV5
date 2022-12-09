#ifndef __CONSTANT_BUFFER_H__
#define __CONSTANT_BUFFER_H__

#include "DirectX.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	HRESULT Create(UINT size);
	void Write(const void* pData);
	void BindVS(UINT slot);
	void BindPS(UINT slot);

private:
	ID3D11Buffer* m_pBuffer;
};

#endif // __CONSTANT_BUFFER_H__