#pragma once
#include "BaseGameState.h"
#include "MenuState.h"
#include "Sprite.h"
#include "Camera.h"

class CAboutState:public CBaseGameState
{
private:
	CSprite* m_sprite;
public:
	CAboutState();
	~CAboutState();
	void Init();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
	void End();
};

