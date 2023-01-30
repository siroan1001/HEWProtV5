#include "DirectX.h"

//--- グローバル変数
ID3D11Device* g_pDevice;
ID3D11DeviceContext* g_pContext;
IDXGISwapChain* g_pSwapChain;
ID3D11RenderTargetView* g_pRTV;
ID3D11DepthStencilView* g_pDSV;

ID3D11Device* GetDevice()
{
	return g_pDevice;
}
ID3D11DeviceContext* GetContext()
{
	return g_pContext;
}
IDXGISwapChain* GetSwapChain()
{
	return g_pSwapChain;
}

HRESULT InitDX(HWND hWnd, UINT width, UINT height, bool fullscreen)
{
	HRESULT	hr = E_FAIL;

	// スワップチェインの設定
	// スワップチェインとは、ウインドウへの表示ダブルバッファを管理する
	// マルチサンプリング、リフレッシュレートが設定できる
	// 複数のバックバッファが作成できる
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));					// ゼロクリア
	sd.BufferDesc.Width = width;						// バックバッファの幅
	sd.BufferDesc.Height = height;						// バックバッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// バックバッファフォーマット(R,G,B,A)
	sd.SampleDesc.Count = 1;		// マルチサンプルの数
	sd.BufferDesc.RefreshRate.Numerator = 1000;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バックバッファの使用方法
	sd.BufferCount = 1;									// バックバッファの数
	sd.OutputWindow = hWnd;			// 関連付けるウインドウ
	sd.Windowed = fullscreen ? FALSE : TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	// ドライバの種類
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// GPUで描画
		D3D_DRIVER_TYPE_WARP,		// 高精度(低速
		D3D_DRIVER_TYPE_REFERENCE,	// CPUで描画
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// 機能レベル
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,		// DirectX11.1対応GPUレベル
		D3D_FEATURE_LEVEL_11_0,		// DirectX11対応GPUレベル
		D3D_FEATURE_LEVEL_10_1,		// DirectX10.1対応GPUレベル
		D3D_FEATURE_LEVEL_10_0,		// DirectX10対応GPUレベル
		D3D_FEATURE_LEVEL_9_3,		// DirectX9.3対応GPUレベル
		D3D_FEATURE_LEVEL_9_2,		// DirectX9.2対応GPUレベル
		D3D_FEATURE_LEVEL_9_1		// Direct9.1対応GPUレベル
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,					// ディスプレイデバイスのアダプタ（NULLの場合最初に見つかったアダプタ）
			driverType,				// デバイスドライバのタイプ
			NULL,					// ソフトウェアラスタライザを使用する場合に指定する
			createDeviceFlags,		// デバイスフラグ
			featureLevels,			// 機能レベル
			numFeatureLevels,		// 機能レベル数
			D3D11_SDK_VERSION,		// 
			&sd,					// スワップチェインの設定
			&g_pSwapChain,			// IDXGIDwapChainインタフェース	
			&g_pDevice,				// ID3D11Deviceインタフェース
			&featureLevel,		// サポートされている機能レベル
			&g_pContext);		// デバイスコンテキスト
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		return hr;
	}

	//--- レンダーターゲット作成
	// バックバッファのポインタを取得
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	// バックバッファへのポインタを指定してレンダーターゲットビューを作成
	if (SUCCEEDED(hr))
	{
		hr = g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRTV);
		g_pContext->OMSetRenderTargets(1, &g_pRTV, nullptr);
	}

	//深度バッファ用のテクスチャ作成
	D3D11_TEXTURE2D_DESC dsvTexDesc = {};
	pBackBuffer->GetDesc(&dsvTexDesc);
	dsvTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	ID3D11Texture2D* pDSVTex;
	hr = g_pDevice->CreateTexture2D(&dsvTexDesc, nullptr, &pDSVTex);
	if (FAILED(hr))	return hr;

	//深度バッファの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = dsvTexDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	hr = g_pDevice->CreateDepthStencilView(pDSVTex, &dsvDesc, &g_pDSV);
	if (FAILED(hr))	return hr;

	//描画先（レンダーターゲット）と深度バッファを設定
	g_pContext->OMSetRenderTargets(1, &g_pRTV, g_pDSV);

	//--- ビューポート
	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	g_pContext->RSSetViewports(1, &viewPort);

	return S_OK;
}

void UninitDX()
{
	g_pContext->ClearState();
	g_pContext->Release();

	g_pSwapChain->SetFullscreenState(false, NULL);
	g_pSwapChain->Release();

	g_pDevice->Release();
}
void BeginDrawDX()
{
	float color[4] = { 0.8f, 0.8f, 0.9f, 1.0f };
	g_pContext->ClearRenderTargetView(g_pRTV, color);
	//深度バッファの内容を毎フレームクリア
	//クリアしないと依然書き込んだ情報が残って
	//新しく3Dを描画しようとしても、裏にいるとみなされて深度テストされる
	g_pContext->ClearDepthStencilView(g_pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
void EndDrawDX()
{
	g_pSwapChain->Present(0, 0);
}

void EnableDepth(bool enable)
{
	if (enable)
	{
		g_pContext->OMSetRenderTargets(1, &g_pRTV, g_pDSV);
	}
	else
		g_pContext->OMSetRenderTargets(1, &g_pRTV, nullptr);
}

