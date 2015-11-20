#include "GameStateManager.h"

CGameStateManager* CGameStateManager::s_instance = nullptr;

CGameStateManager::CGameStateManager()
{
}

CGameStateManager::~CGameStateManager()
{
	if (m_pCurrentState)
		delete m_pCurrentState;
	if (m_pNextState)
		delete m_pNextState;
	/*if (m_pResourceManager)
		delete m_pResourceManager;*/
}

int CGameStateManager::Init(CBaseGameState* state)
{
	//m_pResourceManager = CResourcesManager::GetInstance();
	m_pCurrentState = state;
	return 1;
}

CBaseGameState* CGameStateManager::GetCurrentState()
{
	/*if (m_pCurrentState->m_bFinished)
		m_pCurrentState = m_aGameState[0];*/
	return m_pCurrentState;
}

CGameStateManager* CGameStateManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new CGameStateManager();
	}

	return s_instance;
}

void CGameStateManager::ChangeState(CBaseGameState* state)
{
	/*this->m_pNextState = state;
	if (!m_aGameState.empty())
	{
		m_aGameState.pop_back();
	}
	m_aGameState.push_back(state);
	CTimer::GetInstance()->StartCount();*/
}
