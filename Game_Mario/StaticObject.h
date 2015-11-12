#pragma once

#include "BaseObject.h"
#include "Camera.h"

class CStaticObject : public CBaseObject
{
public:
	CStaticObject(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite* sprite);
	~CStaticObject();
	CBox GetBox();
	void UpdateAnimation(float delta_time);
	void Render();
};