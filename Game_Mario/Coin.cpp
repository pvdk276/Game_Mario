#include "Coin.h"

CCoin::CCoin(int id, D3DXVECTOR2 position, CSprite* sprite) : CDynamicObject(id, position, sprite)
{
	this->type = COIN;
	this->width = 50;
	this->height = 50;
	direction = 1;
}

CCoin::~CCoin()
{

}

void CCoin::Update(float delta_time)
{
	UpdateAnimation(delta_time, 0, 1, direction);
}
void CCoin::Render()
{
	if (curTime == 0)
	{
		sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
	}
}