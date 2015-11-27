#pragma once
#include "BaseGameState.h"
#include "Sprite.h"
#include "GameWindow.h"
#include "PlayState.h"
#include "GameKeyboard.h"

class CMenuState : public CBaseGameState
{
private:
	int x;
	CSprite* sprMenu;
public:
	CMenuState();
	~CMenuState();
	void Init();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
	void End();
	
};


