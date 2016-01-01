#include "AboutState.h"
#include "GameGraphic.h"


CAboutState::CAboutState()
{
	this->Init();
}


CAboutState::~CAboutState()
{
}

void CAboutState::Init()
{
	this->m_bFinished = false;
	this->LoadResource();
}

void CAboutState::LoadResource()
{
	CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/AboutBackground.png");
}

void CAboutState::Update(float deltaTime)
{
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_ESCAPE))
	{
		this->End();
	}
}

void CAboutState::Render()
{
	CGameGraphic::getInstance()->RenderBackbuffer(NULL, NULL);
}

void CAboutState::End()
{
	this->m_bFinished = true;
	delete m_pNextState;
	m_pNextState = new CMenuState();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}
