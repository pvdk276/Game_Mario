#pragma once

#include "BaseGameState.h"
#include "Timer.h"
#include "Singleton.h"
#include <vector>
#include "MenuState.h"
//#include "PlayState.h"

class CGameStateManager : public CSingleton<CGameStateManager>
{
private:
	CBaseGameState* m_currentState;            //State hiện tại của game
public:
	CGameStateManager();
	~CGameStateManager();

	int Init(CBaseGameState* state);

	CBaseGameState* GetCurrentState();

	void ChangeState(CBaseGameState* state);
};
