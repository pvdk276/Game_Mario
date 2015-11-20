#pragma once

#include "DynamicObject.h"
#include "Camera.h"

class CLivingObject : public CDynamicObject
{
public:
	bool isDead;

	CLivingObject(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CLivingObject();

	virtual void Update(float delta_time) = 0;
	virtual void Render() = 0;

	std::string GetType();
};