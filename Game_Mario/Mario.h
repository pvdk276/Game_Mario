#pragma once
#include "Singleton.h"
#include "LivingObject.h"
#include "Sprite.h"
#include "Global.h"
#include "Box.h"
#include "Bullet.h"

enum ActionMario
{
	stand,
	jump,
	run,
	down,
	drop,
	dead
};

class CMario : public CSingleton<CMario>, public CLivingObject
{
private:
	bool m_collisionX; // 1: va chạm bên phải, -1: va chạm bên trái
	bool m_collisionY; // 1: va chạm phía dưới, -1: va chạm phía trên

	CBox mario;
	CBaseObject* m_pObject;
	ObjectName objectName;

	int magicCounter;	//biến đếm số lần thực hiện chuyển đổi
	int posIndex;		//index của mario cũ
	bool doingChanging;	//Mario đang thay đổi
	CSprite* currentSprite;	//Sprite hiện tại

	D3DXVECTOR2 prePosition;
	float deltaPosition;
	float masat;
	float preDeltaPosition;
	bool isSlowing;
	float value;
	D3DXVECTOR2 tVelocity;
	D3DXVECTOR2 preVelocity;
	D3DXVECTOR2 flagAccel;
	D3DXVECTOR2 posMasat;
	ActionMario m_action;

	CSprite* m_pSprBullet;
	CBullet* m_pBullet;
	bool isShooting;
	bool shoot;
	float timerShoot;

	void BeginMoving(float positionx, float velocityx, float accelx);
	void droping();
	void Jumping();
	void Standing();
	void Deading();
	void CheckCollision(CBox mario, float delta_time);
public:
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