#include "Cloud.h"

CCloud::CCloud(int id, D3DXVECTOR2 position, CSprite* sprite) : CDynamicObject(id, position, sprite)
{
	this->type = CLOUD;
	this->width = 150;
	this->height = 100;
}

CCloud::~CCloud()
{

}

void CCloud::Update(float delta_time)
{
	UpdateAnimation(delta_time, 0, 2, direction);
}
void CCloud::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, curIndex);
}