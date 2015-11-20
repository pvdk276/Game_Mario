#pragma once

#include "BaseGameState.h"
#include "Timer.h"
#include "Singleton.h"
#include <vector>
//#include "MenuState.h"
//#include "PlayState.h"

/*C+==================================================================
Class:    CGameStateManager

Summary:  L?p CGameStateManager là l?p singletone ch?a ph??ng th?c ??
chuy?n ??i gi?a các GameState, l?u tr?ng thái, get GameState hi?n t?i.
==================================================================-C*/
class CGameStateManager : CSingleton<CGameStateManager>
{
private:

	CBaseGameState* m_pCurrentState;            /* State hi?n t?i c?a game */

	static CGameStateManager* s_instance;       /* Con tr? ??n th?c th? c?a s? duy nh?t c?a l?p */

												//??i t??ng qu?n lý tài nguyên Game
	//M?ng ch?a các State
	//vector<CBaseGameState*> m_aGameState;
public:
	CGameStateManager();
	~CGameStateManager();

	int Init(CBaseGameState* state);

	CBaseGameState* GetCurrentState();

	void ChangeState(CBaseGameState* state);

	static CGameStateManager* GetInstance();

	CBaseGameState* m_pNextState;
};
