#pragma once
#include <dinput.h>

class GameKeyboard
{
public:
	LPDIRECTINPUT8 di;
	LPDIRECTINPUTDEVICE8 keyboard;
	BYTE keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[1024];

	int Init(HINSTANCE hInstance, HWND hWnd);
};