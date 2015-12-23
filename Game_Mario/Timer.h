#pragma once
#include <Windows.h>
#include "Global.h"
#include "Singleton.h"

class CTimer : public CSingleton<CTimer>
{
private:
	//Tick bắt đầu
	INT64 m_tickStart;
	//Tick kết thúc
	INT64 m_tickEnd;
	
	//Số tick trên giây của hệ thống
	INT64 m_tickPerSec;

	//Số giây giữa 2 tick của hệ thống
	float m_secondPerTick;

public:
	//Thời gian tính theo giây giữa 2 frame liên tiếp
	float m_deltaTime;

	CTimer();
	~CTimer();

	int Init();
	//bắt đầu đếm
	void StartCount();

	//Kết thúc đếm
	void EndCount();

};
