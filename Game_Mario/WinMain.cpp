#include <windows.h>
#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CGame* pGame;
	// Kh?i t?o game.
	pGame = new CGame();
	pGame->Init(hInstance);
	// Ch?y game.
	pGame->Run();

	return 0;
}
