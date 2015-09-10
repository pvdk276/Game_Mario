#pragma once
#include <Windows.h>
#include "Global.h"

/*C+==================================================================
Class:    CTimer

Summary:  L?p CTimer g?m các thu?c tính và ph??ng th?c tính toán
và x? lý th?i gian trong vòng l?p game c?ng nh? trong
các hàm Update c?a các ??i t??ng game
==================================================================-C*/

class CTimer
{
public:
	//Th?i ?i?m b?t ??u ??m
	__int64 m_nTimeStart;
	//Th?i ?i?m k?t thúc ??m
	__int64 m_nTimeEnd;

	static CTimer* GetInstance();

	/*M+==================================================================
	Method:	    CTimer::~CTimer

	Summary:	Ph??ng th?c h?y
	==================================================================-M*/
	~CTimer();

	/*M+==================================================================
	Method:	    CTimer::GetSecondPerTick

	Summary:	Ph??ng th?c l?y v? kho?ng th?i gian (tính theo giây)
	gi?a 2 tick liên ti?p
	==================================================================-M*/
	void GetSecondPerTick();

	/*M+==================================================================
	Method:	    CTimer::StartCount

	Summary:	Ph??ng th?c b?t ??u ??m
	==================================================================-M*/
	void StartCount();

	/*M+==================================================================
	Method:	    CTimer::EndCount

	Summary:	Ph??ng th?c k?t thúc ??m
	==================================================================-M*/
	void EndCount();

	/*M+==================================================================
	Method:	    CTimer::SetMaxFps

	Summary:	Ph??ng th?c gán th?i gian frame

	Param:		maxFps - Th?i gian frame
	==================================================================-M*/
	void SetMaxFps(float maxFps);

	/*M+==================================================================
	Method:	    CTimer::GetTime

	Summary:	Ph??ng th?c tr? v? kho?ng th?i gian gi?a 2 frame liên ti?p
	==================================================================-M*/
	float GetTime();


private:
	/*M+==================================================================
	Method:	    CTimer::CTimer

	Summary:	Ph??ng th?c kh?i t?o
	==================================================================-M*/
	CTimer();
	//S? tick trên m?t giây
	__int64 m_nCountPerSec;
	//T? l? gi?a tick và giây (s? giây gi?a 2 tick liên ti?p)
	float m_fTimeScale;
	//S? Frame trên m?t giây t?i ?a
	float m_fLockFps;
	//Th?i gian delta time tính theo giây gi?a 2 frame liên ti?p
	float m_fDeltaTime;
	//Th?i gian delta time trong m?t giây
	int m_nFrameRate;

	static CTimer* s_TimerInstance;
};
