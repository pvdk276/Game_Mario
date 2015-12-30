#pragma once
#include "Singleton.h"

class CBonusManager :public CSingleton<CBonusManager>
{
private:
	int m_currentPoint;
public:
	CBonusManager();
	~CBonusManager();
	int GetPoint();
	int AddPoint();
	void Reset();

	void Init();
	void Update();
	void Render();
};

