#pragma once
#include <Windows.h>
#include "Global.h"

/*C+==================================================================
Class:    CTimer

Summary:  L?p CTimer g?m c�c thu?c t�nh v� ph??ng th?c t�nh to�n
v� x? l� th?i gian trong v�ng l?p game c?ng nh? trong
c�c h�m Update c?a c�c ??i t??ng game
==================================================================-C*/

class CTimer
{
public:
	//Th?i ?i?m b?t ??u ??m
	__int64 m_nTimeStart;
	//Th?i ?i?m k?t th�c ??m
	__int64 m_nTimeEnd;

	static CTimer* GetInstance();

	/*M+==================================================================
	Method:	    CTimer::~CTimer

	Summary:	Ph??ng th?c h?y
	==================================================================-M*/
	~CTimer();

	/*M+==================================================================
	Method:	    CTimer::GetSecondPerTick

	Summary:	Ph??ng th?c l?y v? kho?ng th?i gian (t�nh theo gi�y)
	gi?a 2 tick li�n ti?p
	==================================================================-M*/
	void GetSecondPerTick();

	/*M+==================================================================
	Method:	    CTimer::StartCount

	Summary:	Ph??ng th?c b?t ??u ??m
	==================================================================-M*/
	void StartCount();

	/*M+==================================================================
	Method:	    CTimer::EndCount

	Summary:	Ph??ng th?c k?t th�c ??m
	==================================================================-M*/
	void EndCount();

	/*M+==================================================================
	Method:	    CTimer::SetMaxFps

	Summary:	Ph??ng th?c g�n th?i gian frame

	Param:		maxFps - Th?i gian frame
	==================================================================-M*/
	void SetMaxFps(float maxFps);

	/*M+==================================================================
	Method:	    CTimer::GetTime

	Summary:	Ph??ng th?c tr? v? kho?ng th?i gian gi?a 2 frame li�n ti?p
	==================================================================-M*/
	float GetTime();


private:
	/*M+==================================================================
	Method:	    CTimer::CTimer

	Summary:	Ph??ng th?c kh?i t?o
	==================================================================-M*/
	CTimer();
	//S? tick tr�n m?t gi�y
	__int64 m_nCountPerSec;
	//T? l? gi?a tick v� gi�y (s? gi�y gi?a 2 tick li�n ti?p)
	float m_fTimeScale;
	//S? Frame tr�n m?t gi�y t?i ?a
	float m_fLockFps;
	//Th?i gian delta time t�nh theo gi�y gi?a 2 frame li�n ti?p
	float m_fDeltaTime;
	//Th?i gian delta time trong m?t gi�y
	int m_nFrameRate;

	static CTimer* s_TimerInstance;
};
