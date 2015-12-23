﻿#pragma once
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
	down,
	drop
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
	bool m_collisionX; // 1: va chạm bên phải, -1: va chạm bên trái
	bool m_collisionY; // 1: va chạm phía dưới, -1: va chạm phía trên
	CBox mario;
	CBaseObject* m_pObject;
	ObjectName objectName;

	float magicCounter;	//biến đếm số lần thực hiện chuyển đổi
	int posIndex;		//index của mario cũ
	bool doingChanging;	//Mario đang thay đổi
	CSprite* currentSprite;	//Sprite hiện tại

	float timer;
	float deltaPosition;
	float masat;
	float preDeltaPosition;
	bool isSlowing;

	D3DXVECTOR2 accel;
	D3DXVECTOR2 maxVelocity;
	D3DXVECTOR2 maxAccel;
	D3DXVECTOR2 posMasat;
	ActionMario m_action;
public:
	
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
	void Reset();
	void changeMario(CSprite* mario, float number);
};