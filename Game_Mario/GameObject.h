#pragma once

#include "Box.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"


class CGameObject
{
public:
	int direct;
	int id;
	int typeId;

	D3DXVECTOR2 position;
	float width;
	float height;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 maxVelocity;
	D3DXVECTOR2 accel;
	D3DXVECTOR2 maxAccel;

	CGameObject();
	CGameObject(int id, int typeId, float positionX, float positionY, float width, float height);
	~CGameObject();

	virtual void Update(float delta_time) {}	//update vi tri cua object va sprite tuong ung
	virtual void UpdatePosition(float delta_time) {}
	virtual void UpdateAnimation(float delta_time) {}
	virtual void Render() {}
	CBox GetBox();
};