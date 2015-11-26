#pragma once
#include "BaseGameState.h"
#include "Sprite.h"
#include "GameWindow.h"
#include "PlayState.h"

class CMenuState : public CBaseGameState
{
private:
	
	CSprite* sprMenu;
public:
	CMenuState();
	~CMenuState();
	void Init();
	void Update(float deltaTime);
	void Render();
	void End();
	
};


