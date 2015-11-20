#include "BaseGameState.h"

CBaseGameState::CBaseGameState()
{
	this->m_pNextState = NULL;
}

CBaseGameState::~CBaseGameState()
{
	if (m_pNextState)
		delete m_pNextState;
}

void CBaseGameState::Run(float deltaTime)
{
	// Update th? gi?i.
	Update(deltaTime);

	// V? th? gi?i
}