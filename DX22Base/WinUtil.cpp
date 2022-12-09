#include "WinUtil.h"

//--- プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//--- グローバル変数
HWND g_hWnd;

HRESULT InitWindow(LPCSTR appName, LONG width, LONG height)
{
	//--- 変数宣言
	WNDCLASSEX wcex;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	// ウィンドクラス情報の設定
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.hInstance = hInstance;
	wcex.lpszClassName = "Class Name";
	wcex.lpfnWndProc = WndProc;
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// ウィンドウクラス情報の登録
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Failed to RegisterClassEx", "Error", MB_OK);
		return 0;
	}

	// ウィンドウの作成
	RECT rect = { 0, 0, width, height };
	DWORD style = WS_CAPTION | WS_SYSMENU;
	DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;
	AdjustWindowRectEx(&rect, style, false, exStyle);
	g_hWnd = CreateWindowEx(
		exStyle, wcex.lpszClassName,
		appName, style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top,
		HWND_DESKTOP,
		NULL, hInstance, NULL
	);

	// ウィンドウの表示
	ShowWindow(g_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hWnd);

	return S_OK;
}

void UninitWindow()
{
}

AppState UpdateWindow()
{
	MSG message;
	// 処理メッセージなし
	if (!PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
	{
		return APP_STATE_WAIT;
	}

	// メッセージの終了
	if (!GetMessage(&message, NULL, 0, 0))
	{
		return APP_STATE_QUIT;
	}

	// メッセージの処理
	TranslateMessage(&message);
	DispatchMessage(&message);
	return APP_STATE_MESSAGE;
}

HWND GetHWND()
{
	return g_hWnd;
}

void Error(const char* mes)
{
	MessageBox(g_hWnd, mes, "Error", MB_OK | MB_ICONERROR);
	DestroyWindow(g_hWnd);
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}