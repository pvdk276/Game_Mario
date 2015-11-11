#pragma once

#include "StaticObject.h"

class CCoinBrick : public CStaticObject
{
public:
	CCoinBrick(CSprite* _coinBrick, D3DXVECTOR2 _position);
	~CCoinBrick();

	void Render();
	void UpdateAnimation(float delta_time);
};
