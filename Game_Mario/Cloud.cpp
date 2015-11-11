#include "Cloud.h"

CCloud::CCloud(CSprite * _cloud, D3DXVECTOR2 _position)
{
	this->sprite = _cloud;
	this->position = _position;
	this->width = 150;
	this->height = 100;
}

CCloud::~CCloud()
{
}

void CCloud::Render()
{
	this->sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 1);
}

void CCloud::UpdateAnimation(float delta_time)
{
	this->sprite->SetTimeAnimation(TIME_ANIMATION);
	this->sprite->UpdateSprite(delta_time, 0, 2, 1);
}
