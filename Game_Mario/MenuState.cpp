#include "MenuState.h"



CMenuState::CMenuState()
{ }
CMenuState::CMenuState(LPD3DXSPRITE spriteHandler)
{
	sprMenu = new CSprite(spriteHandler, "Resources/Images/Other/Background.png", 800, 600, 1, 1, NULL);
}

void CMenuState::Render()
{
	sprMenu->Render(100, 100, 0, 0, 0);
}
CMenuState::~CMenuState()
{
	
}
