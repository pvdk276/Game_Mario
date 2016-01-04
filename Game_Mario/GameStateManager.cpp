#include "GameStateManager.h"
#include "GameGraphic.h"
CGameStateManager::CGameStateManager()
{
}

CGameStateManager::~CGameStateManager()
{
	if (m_currentState)
		delete m_currentState;
}

int CGameStateManager::Init(CBaseGameState* state)
{
	m_currentState = state;
	return 1;
}

CBaseGameState* CGameStateManager::GetCurrentState()
{
	return m_currentState;
}

void CGameStateManager::ChangeState(CBaseGameState* state)
{
	this->m_currentState = state;
}
