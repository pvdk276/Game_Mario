#pragma once
#include <dinput.h>
#include "Singleton.h"
#include "GameObject.h"
#define KEYBOARD_BUFFER_SIZE 1024

class CGameKeyboard : public CSingleton<CGameKeyboard>
{
public:
	LPDIRECTINPUT8 di;
	LPDIRECTINPUTDEVICE8 keyboard;
	BYTE keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];

	CGameKeyboard();
	~CGameKeyboard();

	//Khoi tao input object va input device
	int Init(HINSTANCE hInstance, HWND hWnd);

	void ProcessKeyboard();
	void ProcessInput(float time_begin);

	void OnKeyDown(int KeyCode);

	void OnKeyUp(int KeyCode);

	void(*moveLeft)(float time_begin);
	void(*moveRight)(float time_begin);
	void(*stop)(float time_begin);

	//Huy input object va input device
	void destroy();

	//check neu key duoc nhan
	//parameter example: DIK_LEFT
	bool IsKeyDown(int KeyCode);

	//check neu key duoc tha ra
	//parameter example: DIK_LEFT
	//bool IsKeyUp(int);

	//get trang thai cua tat ca cac key
	//duoc dat trong ham if() trong vong lap while(true), sau khi da khoi tao input device
	void PollKeyboard();
};