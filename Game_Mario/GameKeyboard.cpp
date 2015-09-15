#include "GameKeyboard.h"

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
	result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&di, NULL);
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
	dipdw.dwData = 1024;

	result = keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(result)) return 0;

	result = keyboard->Acquire();
	if (FAILED(result)) return 0;

	return 1;
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

bool CGameKeyboard::IsKeyDown(int key)
{
	if (keyStates[key] & 0x80)
		return true;
	return false;
}

bool CGameKeyboard::IsKeyUp(int key)
{
	if (keyStates[key] & 0x80)
		return false;
	return true;
}

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
