#pragma once

#include "BaseObject.h"
#include "Camera.h"

class CStaticObject : public CBaseObject
{
public:
	CStaticObject(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CStaticObject();

	CBox GetBox();

	virtual void Update() = 0;
	virtual void Render() = 0;

	std::string GetType();
};