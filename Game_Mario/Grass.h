#pragma once

#include "StaticObject.h"
#include "Global.h"

class CGrass : public CStaticObject
{
public:
	CGrass(CSprite* _grass, D3DXVECTOR2 _position);
	~CGrass();

	void Render();
	void UpdateAnimation(float delta_time);
};