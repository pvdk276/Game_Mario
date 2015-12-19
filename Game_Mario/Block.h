#pragma once

#include "DynamicObject.h"
#include "Bonus.h"

class CBlock : public CDynamicObject
{
private:
	float pos;	//lưu tọa độ cũ của object
	int direct; //biến xét chiều di chuyển
public:
	CBlock(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2);
	~CBlock();

	void Update(float delta_time);
	void Render();
	CBonus* bonus;
};
