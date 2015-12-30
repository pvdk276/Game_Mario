#pragma once

#include "BaseObject.h"
#include "Camera.h"

class CStaticObject : public CBaseObject
{
public:
	CStaticObject(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CStaticObject();
	CBox GetBox();
	virtual void Update() {};
	virtual void Render(float delta_time) {};

	std::string GetType();
};