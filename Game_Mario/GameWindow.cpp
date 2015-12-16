#include "GameWindow.h"

CGameWindow::CGameWindow()
{

}


CGameWindow::~CGameWindow()
{

}

CGameWindow* CGameWindow::s_instance = NULL;

int CGameWindow::Init(HINSTANCE hInstance)
{
	m_hInstance = hInstance;

	// T?o thu?c tính cho l?p c?a s?.
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = m_hInstance;

	wc.lpfnWndProc = (WNDPROC)CGameWindow::WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GAME_NAME; // C?n ?? là 1 h?ng l?u l?i tên. n?u b? l?i LPCWSTR vào properties c?a project set character set -> multi-byte
	wc.hIconSm = NULL;

	// ??ng ký l?p c?a s?.
	RegisterClassEx(&wc);

	RECT clientRect = { 0, 0, 750, 750 };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// T?o c?a s?.
	m_hWnd = CreateWindow(
		GAME_NAME,
		GAME_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		/*clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,*/
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		m_hInstance,
		NULL);

	if (!m_hWnd)
	{
		//int error = GetLastError();
		//trace(L"[ERORR] Failed to create window!!! Error code: %d.", error);
		//MessageBox(NULL, "Cannot create game window", "Error", MB_OK);
		return 0;
	}

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	return 1;
}

LRESULT CALLBACK CGameWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HINSTANCE CGameWindow::GetHInstance()
{
	return this->m_hInstance;
}

HWND CGameWindow::GetHWND()
{
	return m_hWnd;
}

CGameWindow* CGameWindow::GetInstance()
{
	if (s_instance == NULL)
		s_instance = new CGameWindow();

	return s_instance;
}
