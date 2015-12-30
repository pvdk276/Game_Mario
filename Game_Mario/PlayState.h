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
#include "ScoreManagement.h"

class CPlayState : public CBaseGameState
{
private:
	CSprite* sprMenu;
	int status;
public:
	CPlayState();
	~CPlayState();
	void Init();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
	void End();
};