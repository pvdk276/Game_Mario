#pragma once

#include "BaseGameState.h"
#include "Timer.h"
#include "Singleton.h"
#include <vector>
//#include "MenuState.h"
//#include "PlayState.h"

/*C+==================================================================
Class:    CGameStateManager

Summary:  L?p CGameStateManager l� l?p singletone ch?a ph??ng th?c ??
chuy?n ??i gi?a c�c GameState, l?u tr?ng th�i, get GameState hi?n t?i.
==================================================================-C*/
class CGameStateManager : CSingleton<CGameStateManager>
{
private:

	CBaseGameState* m_pCurrentState;            /* State hi?n t?i c?a game */

	static CGameStateManager* s_instance;       /* Con tr? ??n th?c th? c?a s? duy nh?t c?a l?p */

												//??i t??ng qu?n l� t�i nguy�n Game
	//M?ng ch?a c�c State
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
