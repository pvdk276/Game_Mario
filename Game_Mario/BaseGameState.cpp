#include "BaseGameState.h"
#include "GameGraphic.h"
CBaseGameState::CBaseGameState()
{
	this->m_pNextState = nullptr;
}

CBaseGameState::~CBaseGameState()
{
	if (m_pNextState)
		delete m_pNextState;
}

void CBaseGameState::Run(float deltaTime)
{
	// Update thế giới
	this->Update(deltaTime);

	// Vẽ thế giới
	if (CGameGraphic::getInstance()->beginRender())
	{
		this->Render();
		CGameGraphic::getInstance()->endRender();
	}	
}