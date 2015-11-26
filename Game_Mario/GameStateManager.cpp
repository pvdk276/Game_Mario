#include "GameStateManager.h"
#include "GameGraphic.h"
CGameStateManager::CGameStateManager()
{
}

CGameStateManager::~CGameStateManager()
{
	if (m_currentState)
		delete m_currentState;
	if (m_pNextState)
		delete m_pNextState;
	/*if (m_pResourceManager)
		delete m_pResourceManager;*/
}

int CGameStateManager::Init(CBaseGameState* state)
{
	//m_pResourceManager = CResourcesManager::GetInstance();
	m_currentState = state;
	return 1;
}

CBaseGameState* CGameStateManager::GetCurrentState()
{
	if (m_currentState->m_bFinished)
		m_currentState = new CMenuState;
	return m_currentState;
}

void CGameStateManager::ChangeState(CBaseGameState* state)
{
	this->m_pNextState = state;
	/*if (!m_aGameState.empty())
	{
		m_aGameState.pop_back();
	}
	m_aGameState.push_back(state);
	CTimer::GetInstance()->StartCount();*/
}
