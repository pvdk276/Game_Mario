#pragma once
#include "BaseGameState.h"
#include "MenuState.h"

class CGuideState :public CBaseGameState
{
public:
	CGuideState();
	~CGuideState();
	void Init();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
	void End();
};

