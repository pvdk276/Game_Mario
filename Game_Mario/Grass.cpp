#include "Grass.h"

CGrass::CGrass(CSprite * _grass, D3DXVECTOR2 _position)
{
	this->sprite = _grass;
	this->position = _position;
	this->width = 100;
	this->height = 50;
}

CGrass::~CGrass()
{
}

void CGrass::Render()
{
	this->sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}

void CGrass::UpdateAnimation(float delta_time)
{
	this->sprite->SetTimeAnimation(TIME_ANIMATION);
	this->sprite->UpdateSprite(delta_time, 0, 2, 1);
}
