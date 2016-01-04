#pragma once
#include "BaseGameState.h"
#include "Sprite.h"
#include "GameWindow.h"
#include "PlayState.h"
#include "SoundManagement.h"

class CWinnerState : public CBaseGameState, CAnimation
{
	CSprite* sprFireWork;
public:
	CWinnerState();
	~CWinnerState();
	void Init();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
	void End();

};


