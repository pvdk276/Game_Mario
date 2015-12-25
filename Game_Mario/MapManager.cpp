#include "MapManager.h"
#include "Sprite.h"
#include "GameGraphic.h"


void CMapManager::init()
{
	//Bonus
	coin = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Bonus/Coin.png", 50, 50, 2, 2, NULL);
	flower = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Bonus/Flower.png", 50, 50, 4, 4, NULL);
	mushroom = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Bonus/Mushroom.png", 50, 50, 2, 2, NULL);
	star = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Bonus/Star.png", 50, 50, 4, 4, NULL);

	//Bullet
	bullet = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Bullet/Bullet.png", 30, 30, 4, 4, NULL);
	machineBullet = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Bullet/MachineBullet.png", 75, 50, 4, 2, NULL);

	//Enemy
	carnivorousFlower = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Enemy/CarnivorousFlower.png", 50, 50, 3, 3, NULL);
	enemy = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Enemy/Enemy.png", 50, 50, 4, 4, NULL);
	turtle = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Enemy/Turtle.png", 50, 50, 11, 6, NULL);
	turtle2 = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Enemy/Turtle2.png", 50, 50, 4, 4, NULL);

	//Mario

	//Other
	bar = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/Bar.png", 200, 32, 1, 1, NULL);
	brick = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/Brick.png", 50, 50, 2, 2, NULL);
	cloud = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/Cloud.png", 150, 100, 3, 3, NULL);
	grass = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/Grass.png", 100, 50, 3, 3, NULL);
	land = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/Land.png", 50, 50, 3, 3, NULL);
	pipe = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/Pipe.png", 100, 150, 1, 1, NULL);
	horizontalPipe = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/HorizontalPipe.png", 150, 100, 1, 1, NULL);
	secretBlock = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/SecretBlock.png", 50, 50, 3, 3, NULL);
	spring = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/Spring.png", 50, 100, 3, 3, NULL);
	stone = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/Stone.png", 50, 50, 1, 1, NULL);
	tower = new CSprite(CGameGraphic::getInstance()->spriteHandler, "Resources/Images/Other/Tower.png", 300, 400, 1, 1, NULL);

}

void CMapManager::LoadResources()
{
	
}

CMapManager::CMapManager()
{
}


CMapManager::~CMapManager()
{
}
