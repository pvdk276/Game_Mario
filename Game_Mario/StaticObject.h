#pragma once

#include "GameObject.h"
#include "Camera.h"

class CStaticObject : public CGameObject
{
public:
	CSprite *sprite;

	CStaticObject();
	~CStaticObject();
	CBox GetBox();
	virtual void UpdateAnimation(float delta_time) = 0;
	virtual void Render() = 0;

};