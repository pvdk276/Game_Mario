#include "Pipe.h"

CPipe::CPipe(CSprite * _mushroom, D3DXVECTOR2 _position)
{
	this->sprite = _mushroom;
	this->position = _position;
	this->width = 50;
	this->height = 50;
}

CPipe::~CPipe()
{
}

void CPipe::Render()
{
	this->sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}

void CPipe::UpdateAnimation(float delta_time)
{
}
