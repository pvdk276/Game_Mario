#include "Game.h"
#include "Camera.h"
#include "FileUtils.h"
#include "GameWindow.h"
#include "GameGraphic.h"
#include "GameKeyboard.h"
#include "Mario.h"

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

	if (!CGameGraphic::getInstance()->Init(CGameWindow::getInstance()->m_hWnd))
	{
		OutputDebugString("[Game.cpp] Cannot init Graphic.");
		return 0;
	}

	if (!CGameKeyboard::getInstance()->Init(hInstance, CGameWindow::getInstance()->m_hWnd))
	{
		OutputDebugString("[Game.cpp] Cannot init Keyboard.");
		return 0;
	}



	//Kh?i t?o ??i t??ng Input.
	//if (!CInput::GetInstance()->Init(pGameWindow->GetHInstance(), pGameWindow->GetHWND()))
	//{
	//	OutputDebugString("[Game.cpp] Cannot init CInput.");
	//	return 0;
	//}
	////Kh?i t?o ??i t??ng qu?n l� GameState.
	//if (!CGameStateManager::GetInstance()->Init(new CMenuState()))
	//{
	//	OutputDebugString("[Game.cpp] Cannot init CGameStateManager.");
	//	return 0;
	//}
	//	Kh?i t?o ??i t??ng timer
	m_pTimer = CTimer::GetInstance();
	m_pTimer->SetMaxFps((float)GAME_FPS);
	return 1;
}

void CGame::LoadResources()
{
	LPD3DXSPRITE spriteHandler;
	HRESULT result = D3DXCreateSprite(CGameGraphic::getInstance()->d3ddv, &spriteHandler);
	if (FAILED(result))
	{
		MessageBox(NULL, "Cannot create sprite", "Error", MB_OK);
		return;
	}

	CCamera::getInstance()->matrix = CFileUtils::getInstance()->LoadMatrix(15, 166, "Resources/map1.txt");
	CCamera::getInstance()->m = 15;
	CCamera::getInstance()->n = 166;
	CCamera::getInstance()->sprite = new CSprite(spriteHandler, "Resources/tiles.png", 50, 50, 216, 18, NULL);

	CMario::getInstance()->smallMario = new CSprite(spriteHandler, "Resources/SmallMario.png", 50, 50, 10, 5, NULL);
	CMario::getInstance()->bigMario = new CSprite(spriteHandler, "Resources/BigMario.png", 50, 100, 10, 5, NULL);
}

void moveLeft()
{
	CMario::getInstance()->speedX = -0.3f;
}

void moveRight()
{
	CMario::getInstance()->speedX = 0.3f;
}

void stop()
{
	//CMario::getInstance()->speedX = 0.0f;
}

void CGame::Run()
{
	MSG msg;
	int done = 0;
	m_pTimer->StartCount();

	LoadResources();
	CGameKeyboard::getInstance()->moveLeft = &moveLeft;
	CGameKeyboard::getInstance()->moveRight = &moveRight;
	CGameKeyboard::getInstance()->stop = &stop;

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
				
				CGameKeyboard::getInstance()->ProcessKeyboard();
				CGameKeyboard::getInstance()->ProcessInput();
				CMario::getInstance()->Update(_DeltaTime);
				CCamera::getInstance()->Update(CMario::getInstance()->positionX, CMario::getInstance()->positionY);
				//CMario::getInstance()->Update(_DeltaTime);

				if (CGameGraphic::getInstance()->d3ddv->BeginScene())
				{
					CCamera::getInstance()->Render();

					CMario::getInstance()->Render();

					CGameGraphic::getInstance()->d3ddv->EndScene();
				}
				CGameGraphic::getInstance()->d3ddv->Present(NULL, NULL, NULL, NULL);
			}
			

			//if (m_pTimer->GetTime() < 1.0f)
			//{
			//	m_pTimer->EndCount();
			//	if (CGameGraphic::getInstance()->d3ddv->BeginScene())
			//	{
			//		CGameGraphic::getInstance()->d3ddv->ColorFill(CGameGraphic::getInstance()->backBuffer, NULL, D3DCOLOR_XRGB(255, 0, 0));
			//		CCamera::getInstance()->Render();

			//		CGameGraphic::getInstance()->d3ddv->EndScene();
			//	}
			//	CGameGraphic::getInstance()->d3ddv->Present(NULL, NULL, NULL, NULL);
			//	
			//	// Get Stage hi?n t?i v� run.
			//	//CGameStateManager::GetInstance()->GetCurrentState()->Run(m_pTimer->GetTime());
			//}
		}
	}
}

