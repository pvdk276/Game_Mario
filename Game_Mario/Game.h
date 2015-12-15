#pragma once
#include "d3d9.h"
#include "BinaryTree.h"
#include "GameWindow.h"
#include "GameGraphic.h"
#include "GameKeyboard.h"
#include "GameStateManager.h"

class CGame
{
public:

	CGame();
	~CGame();
	int Init(HINSTANCE hInstance);
	void Run();
};
