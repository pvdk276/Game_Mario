#include "Pipe.h"

CPipe::CPipe(int id, D3DXVECTOR2 position, CSprite* sprite) : CStaticObject(id, position, sprite)
{
	this->type = PIPE;
	this->width = 100;
	this->height = 150;
}

CPipe::~CPipe()
{
}

void CPipe::Update(float delta_time)
{
}

void CPipe::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}