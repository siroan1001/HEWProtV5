#include "WinUtil.h"

//--- �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//--- �O���[�o���ϐ�
HWND g_hWnd;

HRESULT InitWindow(LPCSTR appName, LONG width, LONG height)
{
	//--- �ϐ��錾
	WNDCLASSEX wcex;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	// �E�B���h�N���X���̐ݒ�
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

	// �E�B���h�E�N���X���̓o�^
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Failed to RegisterClassEx", "Error", MB_OK);
		return 0;
	}

	// �E�B���h�E�̍쐬
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

	// �E�B���h�E�̕\��
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
	// �������b�Z�[�W�Ȃ�
	if (!PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
	{
		return APP_STATE_WAIT;
	}

	// ���b�Z�[�W�̏I��
	if (!GetMessage(&message, NULL, 0, 0))
	{
		return APP_STATE_QUIT;
	}

	// ���b�Z�[�W�̏���
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

// �E�B���h�E�v���V�[�W��
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