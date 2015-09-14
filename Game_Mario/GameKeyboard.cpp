#include "GameKeyboard.h"

int GameKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT result;
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&di, NULL);
	if (result != DI_OK) return 0;

	result = di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (result != DI_OK) return 0;

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