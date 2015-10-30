#pragma once

#include "Box.h"
#include<d3d9.h>
#include<d3dx9.h>
#include"Sprite.h"


class CGameObject
{
//protected:
//	D3DXVECTOR2 m_pos;
//	D3DXVECTOR2 m_veloc;
//	D3DXVECTOR2 m_accel;
//	RECT m_bound;
//	CSprite *m_sprite;
//	//max
//	D3DXVECTOR2 m_maxVelocity;
//	D3DXVECTOR2 m_maxAccelemeter;
//	//
//	D3DXVECTOR2 StartPostion;
public:
	int direct;
	int id;
	int typeId;
	/*float positionX;
	float positionY;*/
	D3DXVECTOR2 position;
	float width;
	float height;
	/*float speedX;
	float speedY;*/
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 maxVelocity;
	/*float maxSpeedX;
	float maxSpeedY;*/
	/*float accelX;
	float accelY;*/
	D3DXVECTOR2 accel;
	D3DXVECTOR2 maxAccel;
	/*float maxAccelX;
	float maxAccelY;*/

	CGameObject();
	CGameObject(int id, int typeId, float positionX, float positionY, float width, float height);
	~CGameObject();

	virtual void Update(float delta_time) {}	//update vi tri cua object va sprite tuong ung
	virtual void UpdatePosition(float delta_time) {}
	virtual void UpdateAnimation(float delta_time) {}
	virtual void Render() {}
	CBox GetBox();
};