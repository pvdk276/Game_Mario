#pragma once
#include "Singleton.h"
#include "Sprite.h"
#include "Global.h"
class CScoreManagement : public CSingleton<CScoreManagement>
{
private:
	CSprite* numbers;
	int currentScore = 0;

public:

	void Init();
	void Update();
	void Render();
	void AddScore();
	~CScoreManagement();
};

