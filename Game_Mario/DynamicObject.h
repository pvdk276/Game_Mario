#pragma once

#include "BaseObject.h"
#include "Animation.h"
#include "Camera.h"

class CDynamicObject : public CBaseObject, public CAnimation
{
public:
	int direction;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 accel;
	D3DXVECTOR2 timer;
	bool isStatic;

	CDynamicObject(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CDynamicObject();

	virtual void Update(float delta_time) = 0;
	virtual void Render() = 0;

	CBox GetBox();
	std::string GetType();
};