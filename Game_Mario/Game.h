#pragma once
#include "d3d9.h"
#include "Timer.h"
#include "BinaryTree.h"
#include "Camera.h"
#include "FileUtils.h"
#include "GameWindow.h"
#include "GameGraphic.h"
#include "GameKeyboard.h"
#include "Mario.h"
#include "BinaryTree.h"
#include "Collision.h"
#include "BaseObject.h"
#include "MenuState.h"
#include "GameStateManager.h"

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
