#pragma once

#include "StaticObject.h"
#include "Global.h"

class CCoin : public CStaticObject
{
public:
	CCoin(CSprite* _coin, D3DXVECTOR2 _position);
	~CCoin();

	void Render();
	void UpdateAnimation(float delta_time);
};