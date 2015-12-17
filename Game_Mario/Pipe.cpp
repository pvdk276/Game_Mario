#include "Pipe.h"

CPipe::CPipe(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite1, CSprite* sprite2) : CStaticObject(id, position, sprite1)
{
	this->type = type;
	this->width = 100;
	this->height = 150;

	if (type == CARNIVOROUS_FLOWER_PIPE)
	{
		D3DXVECTOR2 pos(position.x, 125);
		flower = new CCarnivorousFlower(-1, pos, sprite2);
	}
}

CPipe::~CPipe()
{
}

void CPipe::Update(float delta_time)
{
	if(type == CARNIVOROUS_FLOWER_PIPE) flower->Update(delta_time);
}

void CPipe::Render()
{
	if(type == CARNIVOROUS_FLOWER_PIPE) flower->Render();
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}