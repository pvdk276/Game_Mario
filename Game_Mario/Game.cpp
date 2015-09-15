#include "Game.h"
#include "Camera.h"
#include "FileUtils.h"
#include "GameWindow.h"
#include "GameGraphic.h"
#include "GameKeyboard.h"

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
	//CGameWindow* pGameWindow = CGameWindow::GetInstance();

	//// Kh?i t?o c?a s? game.
	//if (!pGameWindow->Init(hInstance))
	//{
	//	OutputDebugString("[Game.cpp] Cannot init pGameWindow.");
	//	return 0;
	//}

	//CGameGraphic* graphic = new CGameGraphic();
	//// Kh?i t?o thi?t b? d3ddevice game.
	//if (!graphic->Init(pGameWindow->GetHWND()))
	//{
	//	OutputDebugString("[Game.cpp] Cannot init CGraphic.");
	//	return 0;
	//}
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

	if (!CGameGraphic::getInstance()->Init(CGameWindow::getInstance()->m_hWnd))
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
	////Kh?i t?o ??i t??ng qu?n lí GameState.
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
}

void CGame::Run()
{
	MSG msg;
	int done = 0;
	m_pTimer->StartCount();

	LoadResources();

	float frame_start = GetTickCount();
	float tick_per_frame = 1000 / 30; //FRAME RATE = 30

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

				if (CGameGraphic::getInstance()->d3ddv->BeginScene())
				{
					//CGameGraphic::getInstance()->d3ddv->ColorFill(CGameGraphic::getInstance()->backBuffer, NULL, D3DCOLOR_XRGB(255, 0, 0));
					CCamera::getInstance()->Render();

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
			//	// Get Stage hi?n t?i và run.
			//	//CGameStateManager::GetInstance()->GetCurrentState()->Run(m_pTimer->GetTime());
			//}
		}
	}
}