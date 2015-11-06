#pragma once

#include "GameObject.h"

class CStaticObject : public CGameObject
{
public:
	CStaticObject();
	~CStaticObject();
	CBox GetBox();

	virtual void UpdateAnimation(float delta_time) = 0;
	virtual void Render() = 0;

};