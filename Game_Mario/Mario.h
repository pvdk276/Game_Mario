#pragma once
#include "Singleton.h"
#include "LivingObject.h"
#include "Sprite.h"
#include "Global.h"

#define TIME_ANIMATION  1.6f
#define MAXHEIGHT  450
enum ActionMario
{
	stand,
	jump,
	run,
	down
};
enum StatusMario
{
	mariosmall,
	mariobig,
	mariogun
};
class CMario : public CSingleton<CMario>, public CLivingObject
{
private:
	

public:
	ActionMario m_action;
	//D3DXVECTOR2 m_MaxVeloc;//luu tru maxveloc ban dau,khi va cham cho maxvecloc ve 0

	//D3DXVECTOR2 m_lastPos;
	//float gravity;
	//int state;

	CSprite* smallMario;
	CSprite* bigMario;
	CSprite* currentSprite;

	CMario();
	~CMario();

	void Render();
	void Update(float delta_time);
	void UpdatePosition(float delta_time);
	void UpdateAnimation(float delta_time);
};