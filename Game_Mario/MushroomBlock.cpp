#include "MushroomBlock.h"

CMushroomBlock::CMushroomBlock(CSprite * _mushroom, D3DXVECTOR2 _position)
{
	this->sprite = _mushroom;
	this->position = _position;
	this->width = 50;
	this->height = 50;
}

CMushroomBlock::~CMushroomBlock()
{
}

void CMushroomBlock::Render()
{
	this->sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}

void CMushroomBlock::UpdateAnimation(float delta_time)
{

}
