#pragma once

#include "StaticObject.h"

class CCoinBrick : public CStaticObject
{
public:
	CCoinBrick(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CCoinBrick();

	void Update();
	void Render();
};
