#pragma once
#include "Singleton.h"
#include "LivingObject.h"
#include "Sprite.h"
#include "Global.h"
#include "Box.h"

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
	SmallMario,
	BigMario,
	SuperMario
};
class CMario : public CSingleton<CMario>, public CLivingObject
{
private:
	bool m_collisionX = false;
	bool m_collisionY = false;
	float velocityY;
public:
	D3DXVECTOR2 accel;
	D3DXVECTOR2 maxVelocity;
	D3DXVECTOR2 maxAccel;
	ActionMario m_action;
	//D3DXVECTOR2 m_MaxVeloc;//luu tru maxveloc ban dau,khi va cham cho maxvecloc ve 0

	//D3DXVECTOR2 m_lastPos;
	//float gravity;
	//int state;

	CSprite* smallMario;
	CSprite* bigMario;
	CSprite* superMario;

	CMario();
	~CMario();

	void Init();
	void Render();
	void Update(float delta_time);
	void UpdatePosition(float delta_time);
	void UpdateAnimation(float delta_time);
};