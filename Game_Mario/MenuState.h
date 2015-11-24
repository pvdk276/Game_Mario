#pragma once
//#include "BaseGameState.h"
#include "Sprite.h"
#include "GameWindow.h"


class CMenuState //: CBaseGameState
{
public:
	CMenuState();
	CMenuState(LPD3DXSPRITE);
	~CMenuState();
	void Render();
	CSprite* sprMenu;
};


