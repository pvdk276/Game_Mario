#include "Timer.h"

CTimer::CTimer()
{
	
}

CTimer::~CTimer()
{

}

int CTimer::Init()
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&m_tickPerSec);
	m_secondPerTick = 1.0f / m_tickPerSec;
	m_deltaTime = 1.0f / GAME_FPS;

	return 1;
}

void CTimer::StartCount()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_tickStart);
}

void CTimer::EndCount()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_tickEnd);
	m_deltaTime = (m_tickEnd - m_tickStart) * m_secondPerTick;

	//Tính lại thời gian delta time nếu chưa khớp với thời gian giữa 2 frame liên tiếp
	while (m_deltaTime < 1.0f / GAME_FPS)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_tickEnd);
		m_deltaTime = (m_tickEnd - m_tickStart) * m_secondPerTick;
	}

	//Gán lại thời gian bắt đầu
	QueryPerformanceCounter((LARGE_INTEGER*)&m_tickStart);
}
