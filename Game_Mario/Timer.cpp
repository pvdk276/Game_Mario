/*+========================================================
File:		Timer.cpp
Sumary:		Hi?n th?c hóa các ph??ng th?c c?a l?p CTimer
========================================================+*/

#include "Timer.h"

CTimer* CTimer::s_TimerInstance = NULL;

CTimer::CTimer()
{
	this->GetSecondPerTick();
	m_nFrameRate = 0;
	m_fDeltaTime = 0.0f;
}

CTimer::~CTimer()
{

}

void CTimer::GetSecondPerTick()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_nCountPerSec);
	m_fTimeScale = 1.0f / m_nCountPerSec;
}

void CTimer::StartCount()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_nTimeStart);
}

void CTimer::EndCount()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_nTimeEnd);
	m_fDeltaTime = (m_nTimeEnd - m_nTimeStart) * m_fTimeScale;
	//Tính l?i th?i gian delta time n?u ch?a kh?p v?i th?i gian gi?a 2 frame liên ti?p
	if (m_fLockFps > 0.0f)
	{
		while (m_fDeltaTime < 1.0f / m_fLockFps)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&m_nTimeEnd);
			m_fDeltaTime = (m_nTimeEnd - m_nTimeStart) * m_fTimeScale;
		}
	}
	//Gán l?i th?i ?i?m b?t ??u
	QueryPerformanceCounter((LARGE_INTEGER*)&m_nTimeStart);
}

float CTimer::GetTime()
{
	return m_fDeltaTime;
}



void CTimer::SetMaxFps(float maxFps)
{
	m_fLockFps = maxFps;
}

CTimer* CTimer::GetInstance()
{
	if (!s_TimerInstance)
		s_TimerInstance = new CTimer();
	return s_TimerInstance;
}
