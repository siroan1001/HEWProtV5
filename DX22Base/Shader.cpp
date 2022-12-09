#include "Shader.h"
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

//----------
// 基本クラス
Shader::Shader(Kind kind)
	: m_kind(kind)
{
}
Shader::~Shader()
{
}
HRESULT Shader::Load(const char* pFileName)
{
	HRESULT hr = E_FAIL;

	// ファイルを読み込む
	FILE* fp;
	fp = fopen(pFileName, "rb");
	if (!fp) { return hr; }

	// ファイルのサイズを調べる
	int fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	// メモリに読み込み
	fseek(fp, 0, SEEK_SET);
	char* pData = new char[fileSize];
	fread(pData, fileSize, 1, fp);
	fclose(fp);

	// シェーダー作成
	hr = MakeShader(pData, fileSize);

	// 終了処理
	if (pData) { delete[] pData; }
	return hr;
}
HRESULT Shader::Compile(const char* pCode)
{
	static const char* pTargetList[] =
	{
		"vs_5_0",
		"ps_5_0"
	};

	HRESULT hr;
	ID3DBlob* pBlob;
	ID3DBlob* error;
	UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	hr = D3DCompile(pCode, strlen(pCode), nullptr, nullptr, nullptr,
		"main", pTargetList[m_kind], compileFlag, 0, &pBlob, &error);
	if (FAILED(hr)) { return hr; }

	// シェーダ作成
	hr = MakeShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize());
	if (pBlob) pBlob->Release();
	if (error) error->Release();
	return hr;
}



//----------
// 頂点シェーダ
VertexShader::ILList VertexShader::m_ilList;
void VertexShader::ReleaseInputLayout()
{
	ILList::iterator it = m_ilList.begin();
	while (it != m_ilList.end())
	{
		it->second->Release();
		++it;
	}
}

VertexShader::VertexShader()
	: Shader(Shader::VertexShader)
	, m_pVS(nullptr)
	, m_pInputLayout(nullptr)
{
}
VertexShader::~VertexShader()
{
	if (m_pVS)
	{
		m_pVS->Release();
		m_pVS = nullptr;
	}
}
void VertexShader::Bind(void)
{
	ID3D11DeviceContext* pContext = GetContext();
	pContext->VSSetShader(m_pVS, NULL, 0);
	pContext->IASetInputLayout(m_pInputLayout);
}
HRESULT VertexShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	// シェーダー作成
	hr = pDevice->CreateVertexShader(pData, size, NULL, &m_pVS);
	if (FAILED(hr)) { return hr; }



	/*
	シェーダ作成時にシェーダリフレクションを通してインプットレイアウトを取得
	セマンティクスの配置などから識別子を作成
	識別子が登録済→再利用、なければ新規作成
	https://blog.techlab-xe.net/dxc-shader-reflection/
	*/

	ID3D11ShaderReflection* pReflection;
	D3D11_SHADER_DESC shaderDesc;
	D3D11_INPUT_ELEMENT_DESC* pInputDesc;
	D3D11_SIGNATURE_PARAMETER_DESC sigDesc;
	std::string key = "";

	DXGI_FORMAT formats[][4] =
	{
		{
			DXGI_FORMAT_R32_UINT,
			DXGI_FORMAT_R32G32_UINT,
			DXGI_FORMAT_R32G32B32_UINT,
			DXGI_FORMAT_R32G32B32A32_UINT,
		}, {
			DXGI_FORMAT_R32_SINT,
			DXGI_FORMAT_R32G32_SINT,
			DXGI_FORMAT_R32G32B32_SINT,
			DXGI_FORMAT_R32G32B32A32_SINT,
		}, {
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_R32G32B32_FLOAT,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
		},
	};

	hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) { return hr; }

	pReflection->GetDesc(&shaderDesc);
	pInputDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
	for (int i = 0; i < shaderDesc.InputParameters; ++i)
	{
		pReflection->GetInputParameterDesc(i, &sigDesc);
		pInputDesc[i].SemanticName = sigDesc.SemanticName;
		pInputDesc[i].SemanticIndex = sigDesc.SemanticIndex;

		// http://marupeke296.com/TIPS_No17_Bit.html
		BYTE elementCount = sigDesc.Mask;
		elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
		elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);

		switch (sigDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			pInputDesc[i].Format = formats[0][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_SINT32:
			pInputDesc[i].Format = formats[1][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			pInputDesc[i].Format = formats[2][elementCount - 1];
			break;
		}
		pInputDesc[i].InputSlot = 0;
		pInputDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
		pInputDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInputDesc[i].InstanceDataStepRate = 0;

		key += sigDesc.SemanticName;
		key += '0' + sigDesc.SemanticIndex;
	}

	ILList::iterator it = m_ilList.begin();
	while (it != m_ilList.end())
	{
		if (it->first == key)
		{
			m_pInputLayout = it->second;
			break;
		}
		++it;
	}
	if (it == m_ilList.end())
	{
		hr = pDevice->CreateInputLayout(
			pInputDesc, shaderDesc.InputParameters,
			pData, size, &m_pInputLayout
		);
		if (SUCCEEDED(hr))
		{
			m_ilList.insert(ILKey(key, m_pInputLayout));
		}
	}

	delete[] pInputDesc;
	return hr;
}
//----------
// ピクセルシェーダ
PixelShader::PixelShader()
	: Shader(Shader::PixelShader)
	, m_pPS(nullptr)
{
}
PixelShader::~PixelShader()
{
	if (m_pPS)
	{
		m_pPS->Release();
		m_pPS = nullptr;
	}
}
void PixelShader::Bind(void)
{
	ID3D11DeviceContext* pContext = GetContext();
	pContext->PSSetShader(m_pPS, nullptr, 0);
}
HRESULT PixelShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	hr = pDevice->CreatePixelShader(pData, size, NULL, &m_pPS);
	return hr;
}

void SetTextureVS(ID3D11ShaderResourceView* pTex, UINT slot)
{
	GetContext()->VSSetShaderResources(slot, 1, &pTex);
}
void SetTexturePS(ID3D11ShaderResourceView* pTex, UINT slot)
{
	GetContext()->PSSetShaderResources(slot, 1, &pTex);
}