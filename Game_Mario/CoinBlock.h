#pragma once

#include "StaticObject.h"

class CCoinBlock : public CStaticObject
{
public:
	CCoinBlock(CSprite* _coinBlock, D3DXVECTOR2 _position);
	~CCoinBlock();

	void Render();
	void UpdateAnimation(float delta_time);
};
