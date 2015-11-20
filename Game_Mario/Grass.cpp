#include "Grass.h"
CGrass::CGrass(int id, D3DXVECTOR2 position, CSprite* sprite) : CDynamicObject(id, position, sprite)
{
	this->type = GRASS;
	this->width = 100;
	this->height = 50;
	direction = 1;
}

CGrass::~CGrass()
{

}

void CGrass::Update(float delta_time)
{
	UpdateAnimation(delta_time, 0, 2, direction);
}
void CGrass::Render()
{
	if (curTime == 0)
	{
		sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
	}	
}


