#pragma once

#include "StaticObject.h"

class CCoinBrick : public CStaticObject
{
public:
	CCoinBrick(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CCoinBrick();

	void Update(float delta_time);
	void Render();
};
