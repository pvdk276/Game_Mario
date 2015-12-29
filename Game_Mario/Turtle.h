#pragma once

#include "LivingObject.h"
#include "Mario.h"

class CTurtle : public CLivingObject
{
private:
	int m_countCollision;
	float m_counttimer;
	bool beingShoot;
public: 
	CTurtle(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite);
	~CTurtle();

	void Update(float delta_time);
	void Render();
};
