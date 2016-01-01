#pragma once
#include "Singleton.h"
#include "Sprite.h"
#include "Global.h"
class CScoreManagement : public CSingleton<CScoreManagement>
{
private:
	CSprite* m_pNumbers;
	CSprite* m_pMarioIcon;
	CSprite* m_pLevel;
	int m_currentScore;
	int m_currentLife;
	int m_currentLevel;
public:

	int Init();
	void Update();
	void Render();
	void AddScore();
	int SubtractLife();
	int AddLife();
	int GetLife();
	void SetLevel(int level);
	int GetLevel();
	~CScoreManagement();
};

