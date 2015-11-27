#include "Game.h"

#define FRAME_RATE 60
CGame::CGame()
{

}

CGame::~CGame()
{
	if (m_pTimer)
		delete m_pTimer;
}

int CGame::Init(HINSTANCE hInstance)
{
	if (!CGameWindow::getInstance()->Init(hInstance))
	{
		OutputDebugString("[Game.cpp] Cannot init Window.");
		return 0;
	}

	//Khởi tạo đối tượng GameGraphic
	if (!CGameGraphic::getInstance()->Init(CGameWindow::getInstance()->m_hWnd))
	{
		OutputDebugString("[Game.cpp] Cannot init Graphic.");
		return 0;
	}

	//Khởi tạo đối tượng keyboard
	if (!CGameKeyboard::getInstance()->Init(hInstance, CGameWindow::getInstance()->m_hWnd))
	{
		OutputDebugString("[Game.cpp] Cannot init Keyboard.");
		return 0;
	}

	//Khởi tạo đối tượng quản lý game state
	if (!CGameStateManager::getInstance()->Init(new CMenuState()))
	{
		OutputDebugString("[Game.cpp] Cannot init CGameStateManager.");
		return 0;
	}

	//	Khởi tạo đối tượng Timer
	m_pTimer = CTimer::GetInstance();
	m_pTimer->SetMaxFps((float)GAME_FPS);
	return 1;
}

void CGame::Run()
{
	MSG msg;
	int done = 0;
	m_pTimer->StartCount();

	float frame_start = GetTickCount();
	float tick_per_frame = 1000 / FRAME_RATE; 

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			float now = GetTickCount();
			float _DeltaTime = now - frame_start;
			if (_DeltaTime >= tick_per_frame)
			{
				frame_start = now;
				CGameKeyboard::getInstance()->PollKeyboard();
				CGameStateManager::getInstance()->GetCurrentState()->Run(_DeltaTime);
			}
		}
	}
}