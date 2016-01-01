#pragma once
#include "BaseGameState.h"
#include "Sprite.h"
#include "Camera.h"
#include "MenuState.h"
#include "ScoreManagement.h"

class CGameOverState : public CBaseGameState
{
private:
	CSprite* m_pNumbers;
	int m_Life;
	bool m_isGameOver;
	float m_timer;
public:
	CGameOverState();
	~CGameOverState();
	void Init();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
	void End();

};
