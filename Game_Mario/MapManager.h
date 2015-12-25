#pragma once
#include "Singleton.h"
#include "Sprite.h"

class CMapManager : public CSingleton<CMapManager>
{
public:
	int map_num;
	void init();
	void LoadResources();
	CMapManager();
	~CMapManager();

	//Bonus
	CSprite* coin;
	CSprite* flower;
	CSprite* mushroom;
	CSprite* star;

	//Bullet
	CSprite* bullet;
	CSprite* machineBullet;

	//Enemy
	CSprite* carnivorousFlower;
	CSprite* enemy;
	CSprite* turtle;
	CSprite* turtle2;

	//Mario

	//Other
	CSprite* bar;
	CSprite* brick;
	CSprite* cloud;
	CSprite* grass;
	CSprite* land;
	CSprite* pipe;
	CSprite* horizontalPipe;
	CSprite* secretBlock;
	CSprite* spring;
	CSprite* stone;
	CSprite* tower;
};

