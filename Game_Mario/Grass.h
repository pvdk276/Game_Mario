#pragma once

#include "DynamicObject.h"

class CGrass : public CDynamicObject
{
public:
	CGrass(CSprite* _grass, D3DXVECTOR2 _position);
	~CGrass();

	void Render();
	void UpdateAnimation(float delta_time);
};