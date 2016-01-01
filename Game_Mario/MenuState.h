#pragma once
#include "BaseGameState.h"
#include "Sprite.h"
#include "GameWindow.h"
#include "PlayState.h"
#include "AboutState.h"

class CMenuState : public CBaseGameState
{
private:
	bool m_keyDown = false;
	bool m_keyUp = false;
	int m_indexMenu;
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


