#pragma once

#include "BaseObject.h"
#include "Camera.h"

class CDynamicObject : public CBaseObject
{
public:
	float timeAnimation;

	CDynamicObject(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite* sprite, float timeAnimation);
	~CDynamicObject();

	void UpdateAnimation(float delta_time);
	void Render();
};