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
	/* �萔�o�b�t�@�쐬���̒���
	�萔�o�b�t�@�̑傫����4�o�C�g��؂�(
	4�o�C�g�A���C�����g)�łȂ��ƍ쐬�ł��Ȃ�
	*/
	HRESULT hr;

	// �쐬����o�b�t�@�̏��
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// �o�b�t�@�̍쐬
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pBuffer);

	return hr;
}
void ConstantBuffer::Write(const void* pData)
{
	// �萔�o�b�t�@�ւ̏�������
	ID3D11DeviceContext* pContext = GetContext();
	pContext->UpdateSubresource(
		m_pBuffer, 0, nullptr, pData, 0, 0
	);
}
void ConstantBuffer::BindVS(UINT slot)
{
	/*
	�萔�o�b�t�@�̃f�[�^�𑗂�ہA
	�ǂ̈ʒu�Ɋi�[���邩��1�ڂ̈���(StartSlot)��
	�w�肷��B
	hlsl�̃R�[�h�ł�register(bX)�Ńo�b�t�@�̊i�[
	�ʒu�����߂Ă����B
	*/
	ID3D11DeviceContext* pContext = GetContext();
	pContext->VSSetConstantBuffers(slot, 1, &m_pBuffer);
}
void ConstantBuffer::BindPS(UINT slot)
{
	ID3D11DeviceContext* pContext = GetContext();
	pContext->PSSetConstantBuffers(slot, 1, &m_pBuffer);
}
