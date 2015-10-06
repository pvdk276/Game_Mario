#pragma once
#include "d3d9.h"
//#include "GameWindow.h"
#include "Timer.h"
#include "BinaryTree.h"
//#include "GameGraphic.h"
//#include "Graphic.h"
//#include "Input.h"
//#include "GameStateManager.h"

class CGame
{
private:
	CTimer* m_pTimer;
public:

	CGame();
	~CGame();
	int Init(HINSTANCE hInstance);

	void LoadResources();

	void Run();
};
