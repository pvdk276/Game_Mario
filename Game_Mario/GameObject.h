#pragma once

#include "Box.h"
#include<d3d9.h>
#include<d3dx9.h>
#include"Sprite.h"


class CGameObject
{
protected:
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_veloc;
	D3DXVECTOR2 m_accel;
	RECT m_bound;
	CSprite *m_sprite;
	//max
	D3DXVECTOR2 m_maxVelocity;
	D3DXVECTOR2 m_maxAccelemeter;
	//
	D3DXVECTOR2 StartPostion;
public:
	int m_direct;
	int id;
	int typeId;
	float positionX;
	float positionY;
	float width;
	float height;
	float speedX;
	float speedY;

	CGameObject();

	CGameObject(int id, int typeId, float positionX, float positionY, float width, float height);
	virtual void Update( float);//update vi tri cua object va sprite tuong ung
	virtual void UpdatePosition( float);
	virtual void UpdateAnimation( float);
	virtual void Render() {}
	CBox GetBox();
};