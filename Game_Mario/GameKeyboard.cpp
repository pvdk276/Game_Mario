#include "GameKeyboard.h"
#include "GameWindow.h"

CGameKeyboard::CGameKeyboard()
{
	di = NULL;
	keyboard = NULL;
}

CGameKeyboard::~CGameKeyboard()
{
	destroy();
}

int CGameKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT result;
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&di, NULL);
	if (result != DI_OK)
	{
		OutputDebugString("[GameKeyboard.cpp] Error when create input object.");
		return 0;
	}

	result = di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (result != DI_OK)
	{
		OutputDebugString("[GameKeyboard.cpp] Error when create input device.");
		return 0;
	}

	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	result = keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	result = keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(result))
	{
		MessageBox(NULL, "Cannot set property keyboard", "Error", MB_OK);
		return 0;
	}

	result = keyboard->Acquire();
	if (FAILED(result))
	{
		MessageBox(NULL, "Cannot acquire keyboard", "Error", MB_OK);
		return 0;
	}

	return 1;
}

void CGameKeyboard::ProcessKeyboard()
{
	//scanning keyboard
	keyboard->GetDeviceState(sizeof(keyStates), keyStates);
	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(CGameWindow::getInstance()->m_hWnd, WM_QUIT, 0, 0);
	}

	//add key event to queue and handle one by one
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT result = keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	for (int i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
		{
			OnKeyDown(KeyCode);
		}
		else OnKeyUp(KeyCode);
	}
}

void CGameKeyboard::ProcessInput(float time_begin)
{

}

void CGameKeyboard::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_LEFT: Left_Button_Down(); break;
	case DIK_RIGHT: Right_Button_Down(); break;
	case DIK_DOWN: Down_Button_Down(); break;
	case DIK_SPACE: Space_Button_Down(); break;
	case DIK_X: X_Button_Down(); break;
	}
}

void CGameKeyboard::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_LEFT: Left_Button_Up(); break;
	case DIK_RIGHT: Right_Button_Up(); break;
	case DIK_DOWN: Down_Button_Up(); break;
	case DIK_SPACE: Space_Button_Up(); break;
	case DIK_X: X_Button_Up(); break;
	}
}

void CGameKeyboard::destroy()
{
	if (keyboard != NULL)
	{
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = NULL;
	}

	if (di != NULL)
	{
		di->Release();
		di = NULL;
	}
}

bool CGameKeyboard::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

//bool CGameKeyboard::IsKeyUp(int KeyCode)
//{
//	if (keyStates[key] & 0x80)
//		return false;
//	return true;
//}

void CGameKeyboard::PollKeyboard()
{
	keyboard->Poll();
	if (keyboard->GetDeviceState(sizeof(keyStates), (LPVOID)&keyStates))
	{
		//keyboard device lost, try to re-acquire
		keyboard->Acquire();
		keyboard->GetDeviceState(sizeof(keyStates), (LPVOID)&keyStates);
	}
	else
	{
		keyboard->GetDeviceState(sizeof(keyStates), (LPVOID)&keyStates);
	}

}
