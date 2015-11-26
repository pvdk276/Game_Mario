#pragma once
#include "BaseGameState.h"
#include "Sprite.h"
#include "GameStateManager.h"

class CPlayState : public CBaseGameState
{
private:
	CSprite* sprMenu;
	int x = 100;
public:
	CPlayState();
	~CPlayState();
	void Init();
	void Update(float deltaTime);
	void Render();
	void End();

};


