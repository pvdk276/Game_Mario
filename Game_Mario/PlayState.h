#pragma once
#include "BaseGameState.h"
#include "BinaryTree.h"
#include "Collision.h"
#include "BaseObject.h"
#include "Sprite.h"
#include "GameStateManager.h"
#include "Camera.h"
#include "Mario.h"
#include "GameOverState.h"
#include "WinnerState.h"
#include "ScoreManagement.h"
#include "Singleton.h"

class CPlayState : public CBaseGameState, public CSingleton<CPlayState>
{
private:
	int m_status;
	int m_id_map;
public:
	CPlayState();
	~CPlayState();
	void Init();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
	void End();

	
};