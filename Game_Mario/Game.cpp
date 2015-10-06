#include "Game.h"
#include "Camera.h"
#include "FileUtils.h"
#include "GameWindow.h"
#include "GameGraphic.h"
#include "GameKeyboard.h"
#include "Mario.h"
#include "BinaryTree.h"

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

	CMario::getInstance()->smallMario = new CSprite(spriteHandler, "Resources/SmallMario.png", 50, 50, 10, 5, NULL);
	CMario::getInstance()->bigMario = new CSprite(spriteHandler, "Resources/BigMario.png", 50, 100, 10, 5, NULL);

	CBinaryTree::getInstance()->init("Resources/map1_ListObject.txt", "Resources/map1_BinaryTree.txt");
}

void moveLeft(float delta_time)
{
	
}

void moveRight(float delta_time)
{
	/*std::string s = std::to_string(delta_time);
	MessageBox(NULL, s.c_str(), "Error", MB_OK);*/

	if (CMario::getInstance()->state == STANDING)
	{
		CMario::getInstance()->gravity = 50;
		CMario::getInstance()->speedX = CMario::getInstance()->speedX + CMario::getInstance()->gravity * delta_time/1000;
		if (CMario::getInstance()->speedX >= 500) CMario::getInstance()->speedX = 500;
		CMario::getInstance()->state = RUNNING;
	}
	//MessageBox(NULL, "DIK_RIGHT", "Error", MB_OK);
}

void stop(float delta_time)
{
	if (CMario::getInstance()->state == RUNNING)
	{
		CMario::getInstance()->gravity = -0.001f;
		CMario::getInstance()->speedX = CMario::getInstance()->speedX + CMario::getInstance()->gravity * delta_time;
		if (CMario::getInstance()->speedX <= 0)
		{
			CMario::getInstance()->speedX = 0;
			CMario::getInstance()->state = STANDING;
		}
	}
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

				CBinaryTree::getInstance()->listCurrentObject->clear();
				CBinaryTree::getInstance()->loadListCurrentObject(CBinaryTree::getInstance()->rootNode, CCamera::getInstance()->positionX, CCamera::getInstance()->positionY, CCamera::getInstance()->width, CCamera::getInstance()->height);

				
				CGameKeyboard::getInstance()->ProcessKeyboard();
				CGameKeyboard::getInstance()->ProcessInput(_DeltaTime);
				CMario::getInstance()->Update(_DeltaTime);
				CCamera::getInstance()->Update(CMario::getInstance()->positionX, CMario::getInstance()->positionY);

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
			//	// Get Stage hi?n t?i và run.
			//	//CGameStateManager::GetInstance()->GetCurrentState()->Run(m_pTimer->GetTime());
			//}
		}
	}
}