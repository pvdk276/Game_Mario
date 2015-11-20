#include "MushroomBlock.h"

CMushroomBlock::CMushroomBlock(int id, D3DXVECTOR2 position, CSprite* sprite) : CDynamicObject(id, position, sprite)
{
	this->type = MUSHROOM_BLOCK;
	this->width = 50;
	this->height = 50;
	this->direction = 1;
}

CMushroomBlock::~CMushroomBlock()
{
}

void CMushroomBlock::Update(float delta_time)
{
	UpdateAnimation(delta_time, 0, 1, direction);
}

void CMushroomBlock::Render()
{
	if (curTime == 0) sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}
