#include <windows.h>
#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CGame* pGame;
	// Khởi tạo game
	pGame = new CGame();
	pGame->Init(hInstance);
	// Chạy game
	pGame->Run();

	return 0;
}
