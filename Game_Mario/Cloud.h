#pragma once

#include "StaticObject.h"
#include "Global.h"

class CCloud : public CStaticObject
{
public:
	CCloud(CSprite* _cloud,D3DXVECTOR2 _position);
	~CCloud();

	void Render();
	void UpdateAnimation(float delta_time);
};