#include "GameOverState.h"
#include "GameGraphic.h"

CGameOverState::CGameOverState()
{
	this->Init();
}


CGameOverState::~CGameOverState()
{
}

void CGameOverState::Init()
{
	this->m_bFinished = false;
	this->LoadResource();
}

void CGameOverState::LoadResource()
{
	CGameGraphic::getInstance()->InitSurface("Resources/Images/Other/WaitScreen.png");
}

void CGameOverState::Update(float deltaTime)
{
	if (CGameKeyboard::getInstance()->IsKeyDown(DIK_SPACE))
	{
		this->End();
	}
}

void CGameOverState::Render()
{
	CGameGraphic::getInstance()->RenderBackbuffer(NULL, NULL);
}

void CGameOverState::End()
{
	this->m_bFinished = true;
	delete m_pNextState;
	m_pNextState = new CMenuState();
	CGameStateManager::getInstance()->ChangeState(m_pNextState);
}