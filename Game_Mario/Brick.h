#pragma once

#include "StaticObject.h"
#include "Sprite.h"

class CBrick : public CStaticObject
{
private:
	CSprite * _smallBrick[4];
	D3DXVECTOR2 _smallBrickPos[4];
	D3DXVECTOR2 maxVelocity;
	D3DXVECTOR2 maxAccel;
	float pos;	//lưu tọa độ cũ của brick
	int direct; //biến xét chiều di chuyển viên gạch
public:

	CBrick(int id, D3DXVECTOR2 position, CSprite* sprite);
	~CBrick();

	void Update(float delta_time);
	void Render();
};
