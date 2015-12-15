#include "Brick.h"
#include "GameGraphic.h"

CBrick::CBrick(int id, D3DXVECTOR2 position, CSprite* sprite) : CStaticObject(id, position, sprite)
{
	this->type = BRICK;
	this->width = 50;
	this->height = 50;

	maxVelocity = D3DXVECTOR2(0.0f, 20.0f);
	maxAccel = D3DXVECTOR2(0.0f, 9.8f);

	this->isCollision = false;
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
	 if (this->isCollision) 
	{
		for (int i = 0; i < 4; i++)
		{
			if (i == 0 || i == 3) // m?nh b�n tr�i
			{
				_smallBrickPos[i].x -= 1.5f;
			}
			else
			{
				_smallBrickPos[i].x += 1.5f;
			}
			_smallBrickPos[i].y -= maxVelocity.y * delta_time + 1.0f / 2 * maxAccel.y * delta_time * delta_time;
		}
	}
}

void CBrick::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
	if (this->isCollision)
	{
		for (int i = 0; i < 4; i++)
		{
			_smallBrick[i]->Render(_smallBrickPos[i].x, _smallBrickPos[i].y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
		}
	}
	
}