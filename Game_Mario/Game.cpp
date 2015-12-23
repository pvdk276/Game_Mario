#include "Game.h"

CGame::CGame()
{

}

CGame::~CGame()
{
}

int CGame::Init(HINSTANCE hInstance)
{
	//Khởi tạo GameWindow
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

	////Khởi tạo đối tượng quản lý thời gian
	CTimer::getInstance()->Init();

	return 1;
}

void CGame::Run()
{
	MSG msg;
	int done = 0;
	/*float frame_start = GetTickCount();;

	float tick_per_frame = 1000 / GAME_FPS;
	

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		float now = GetTickCount();
		float _DeltaTime = now - frame_start;
		if (_DeltaTime >= tick_per_frame)
		{
			frame_start = now;
			CGameStateManager::getInstance()->GetCurrentState()->Run(_DeltaTime);
		}
		CGameKeyboard::getInstance()->PollKeyboard();
	}*/

	CTimer::getInstance()->StartCount();
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
			if (CTimer::getInstance()->m_deltaTime >= 1.0f / GAME_FPS)
			{
				char    buf[4096], *p = buf;
				sprintf(p, "Update at detatime is:  %f\n", CTimer::getInstance()->m_deltaTime);
				OutputDebugString(p);
				//OutputDebugString("Update!!!!!!\n + ",);
				CGameStateManager::getInstance()->GetCurrentState()->Run(CTimer::getInstance()->m_deltaTime);
				CTimer::getInstance()->EndCount();
			}
		}
		CGameKeyboard::getInstance()->PollKeyboard();
	}

}