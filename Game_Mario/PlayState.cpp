#include "PlayState.h"
#include "GameGraphic.h"

CPlayState::CPlayState()
{
	this->Init();
}

CPlayState::~CPlayState()
{

}

void CPlayState::Init()
{
	this->x = 100;
	this->m_bFinished = false;
	sprMenu = new CSprite(CGameGraphic::getInstance()->getSpriteHander(), "Resources/Images/Other/Background.png", 800, 600, 1, 1, NULL);
}

void CPlayState::Update(float deltaTime)
{
	x += 1;
}

void CPlayState::Render()
{
	sprMenu->Render(100, x, 0, 0, 0);
}

void CPlayState::End()
{
	this->m_bFinished = true;
	delete m_pNextState;
	m_pNextState = new CMenuState();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}

