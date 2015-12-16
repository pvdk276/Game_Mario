#include "Brick.h"
#include "GameGraphic.h"

CBrick::CBrick(int id, D3DXVECTOR2 position, CSprite* sprite) : CStaticObject(id, position, sprite)
{
	this->type = BRICK;
	this->width = 50;
	this->height = 50;
	
	maxVelocity = D3DXVECTOR2(0.0f, 120.0f);
	maxAccel = D3DXVECTOR2(0, -9.8);

	this->isDead = false;
	this->isCollision = false;
	this->pos = position.y;
	this->direct = 1;
	//gach no
	_smallBrick[0] = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/ExploredBrick.png", 26, 24, 1, 1, NULL);
	_smallBrick[1] = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/ExploredBrick.png", 26, 24, 1, 1, NULL);
	_smallBrick[2] = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/ExploredBrick.png", 26, 24, 1, 1, NULL);
	_smallBrick[3] = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/ExploredBrick.png", 26, 24, 1, 1, NULL);
	//set position for small brick
	_smallBrickPos[0] = D3DXVECTOR2(position.x-this->width/4, position.y + this->height/4);//trai tren
	_smallBrickPos[1] = D3DXVECTOR2(position.x + this->width / 4, position.y + this->height / 4);//phai tren
	_smallBrickPos[2] = D3DXVECTOR2(position.x + this->width / 4, position.y - this->height / 4);//phai duoi
	_smallBrickPos[3] = D3DXVECTOR2(position.x - this->width / 4, position.y - this->height / 4);//trai duoi
}

CBrick::~CBrick()
{
	for (int i = 0; i < 4; i++)
	{
		if (_smallBrick[i] != NULL)
		{
			delete _smallBrick[i];
			_smallBrick[i] = NULL;
		}
	}
}

void CBrick::Update(float delta_time)
{
	if (this->isDead) 
	{	
		for (int i = 0; i < 4; i++)
		{
			if (i == 0 || i==3) // mảnh bên trái
			{
				_smallBrickPos[i].x -= 2.5f;
			}
			else if (i == 1 || i == 2)
			{
				_smallBrickPos[i].x += 2.5f;	
			}
			maxVelocity.y += maxAccel.y * delta_time;
			_smallBrickPos[i].y += maxVelocity.y * delta_time;
		}
	}
	if (this->isCollision)
	{
		position.y += direct;
		if (position.y > pos + 5)
			direct = -1;
		if (position.y == pos)
		{
			this->isCollision = false;
			direct = 1;
		}
			
	}

}

void CBrick::Render()
{
	if(!this->isDead)
		sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
	else
	{
		for (int i = 0; i < 4; i++)
		{
			_smallBrick[i]->Render(_smallBrickPos[i].x, _smallBrickPos[i].y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
		}
	}
	
}