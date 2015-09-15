#pragma once
#include <dinput.h>
#include "Singleton.h"

class CGameKeyboard : public CSingleton<CGameKeyboard>
{
public:
	LPDIRECTINPUT8 di;
	LPDIRECTINPUTDEVICE8 keyboard;
	BYTE keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[1024];

	CGameKeyboard();
	~CGameKeyboard();

	//Khoi tao input object va input device
	int Init(HINSTANCE hInstance, HWND hWnd);

	//Huy input object va input device
	void destroy();

	//check neu key duoc nhan
	//parameter example: DIK_LEFT
	bool IsKeyDown(int);

	//check neu key duoc tha ra
	//parameter example: DIK_LEFT
	bool IsKeyUp(int);

	//get trang thai cua tat ca cac key
	//duoc dat trong ham if() trong vong lap while(true), sau khi da khoi tao input device
	void PollKeyboard();
};