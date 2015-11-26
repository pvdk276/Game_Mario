#include "MenuState.h"
#include "GameGraphic.h"

int x = 100;
CMenuState::CMenuState()
{
	this->Init();
}

CMenuState::~CMenuState()
{

}

void CMenuState::Init()
{
	sprMenu = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/Background.png", 800, 600, 1, 1, NULL);
}

void CMenuState::Update(float deltaTime)
{
	x += 1;
}

void CMenuState::Render()
{
	sprMenu->Render(x, 100, 0, 0, 0);
}

void CMenuState::End()
{
	/*this->m_bFinished = true;
	delete m_pNextState;
	m_pNextState = new CPlayState();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);*/
}

