#pragma once
#include <dinput.h>
#include "Singleton.h"
#include "BaseObject.h"
#define KEYBOARD_BUFFER_SIZE 1024

class CGameKeyboard : public CSingleton<CGameKeyboard>
{
public:
	LPDIRECTINPUT8 di;
	LPDIRECTINPUTDEVICE8 keyboard;
	BYTE keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];

	//default init function
	CGameKeyboard();
	~CGameKeyboard();

	//init keyboard
	int Init(HINSTANCE hInstance, HWND hWnd);

	//2 function: scan keyboard, add key events to queue, check one by one
	void ProcessKeyboard();

	//handle key event when scanning keyboard
	void ProcessInput(float time_begin);

	//handle key down event
	void OnKeyDown(int KeyCode);

	//handle key up event
	void OnKeyUp(int KeyCode);

	//function points
	void(*Left_Button_Up)(void);
	void(*Left_Button_Down)(void);
	void(*Right_Button_Up)(void);
	void(*Right_Button_Down)(void);
	void(*Down_Button_Up)(void);
	void(*Down_Button_Down)(void);
	void(*Space_Button_Up)(void);
	void(*Space_Button_Down)(void);
	void(*X_Button_Up)(void);
	void(*X_Button_Down)(void);

	//Huy input object va input device
	void destroy();

	//check neu key duoc nhan
	//parameter example: DIK_LEFT
	bool IsKeyDown(int KeyCode);
	bool IsKeyUp(int KeyCode);

	//check neu key duoc tha ra
	//parameter example: DIK_LEFT
	//bool IsKeyUp(int);

	//get trang thai cua tat ca cac key
	//duoc dat trong ham if() trong vong lap while(true), sau khi da khoi tao input device
	void PollKeyboard();
};