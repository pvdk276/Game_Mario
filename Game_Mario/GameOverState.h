#pragma once
#include "BaseGameState.h"
#include "Sprite.h"
#include "Camera.h"
#include "MenuState.h"
class CGameOverState : public CBaseGameState
{
private:
	CSprite* m_sprite;
public:
	CGameOverState();
	~CGameOverState();
	void Init();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
	void End();

};
