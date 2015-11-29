#pragma once

#include "LivingObject.h"

class CTurtle : public CLivingObject
{
public: 
	CTurtle(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite);
	~CTurtle();

	void Update(float delta_time);
	void Render();
};
