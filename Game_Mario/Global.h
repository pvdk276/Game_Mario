#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include <cmath>

enum ObjectName
{
	LEFT_LAND,
	CENTER_LAND,
	RIGHT_LAND,
	CLOUD,
	GRASS,
	BRICK,
	COIN_BRICK,

	//bonus
	COIN,
	FLOWER,
	RED_MUSHROOM,
	GREEN_MUSHROOM,
	STAR,

	//block
	COIN_BLOCK,
	FLOWER_BLOCK,
	RED_MUSHROOM_BLOCK,
	GREEN_MUSHROOM_BLOCK,
	STAR_BLOCK,

	PIPE,
	PIPE_DOWN,
	PIPE_UP,
	CARNIVOROUS_FLOWER_PIPE,

	STONE,
	SPRING,
	BAR,

	//enemy
	ENEMY,
	WING_TURTLE,
	TURTLE,
	FIRE_TURTLE,
	CARNIVOROUS_FLOWER
};

#define TIME_ANIMATION  1.6f
#define STANDING 1
#define RUNNING 2
#define MARIO_GRAVITY = 0.5f

#define GAME_NAME "Game_Mario"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GAME_FPS 60
#define GRAVITY  -600.0f

#define PI 3.14159265f

#pragma region path object
#define pLAND "Resources/Images/Other/Land.png"
#define pCLOUD "Resources/Images/Other/Cloud.png"
#define pGRASS "Resources/Images/Other/Grass.png"
#define pBRICK "Resources/Images/Other/Brick.png"
#define pBAR "Resources/Images/Other/Bar.png"
#define pPIPE "Resources/Images/Other/Pipe.png"
#define pHORIZONTALPIPE "Resources/Images/Other/HorizontalPipe.png"
#define pSECRETBLOCK "Resources/Images/Other/SecretBlock.png"
#define pSPRING "Resources/Images/Other/Spring.png"
#define pSTONE "Resources/Images/Other/Stone.png"
#define pTOWER "Resources/Images/Other/Tower.png"
#define pCARNIVOROUSFLOWER "Resources/Images/Enemy/CarnivorousFlower.png"
#define pENEMY "Resources/Images/Enemy/Enemy.png"
#define pTURTLE "Resources/Images/Enemy/Turtle.png"
#define pTURTLE2 "Resources/Images/Enemy/Turtle2.png"
#define pMACHINEBULLET "Resources/Images/Bullet/MachineBullet.png"
#define pBULLET "Resources/Images/Bullet/Bullet.png"
#define pSTAR "Resources/Images/Bullet/Star.png"
#define pMUSHROOM "Resources/Images/Bullet/Mushroom.png"
#define pCOIN "Resources/Images/Bullet/Coin.png"
#define pFLOWER "Resources/Images/Bullet/Flower.png"
#pragma endregion
#pragma region path audio
#define pBACKMUSIC "Resources/Audio/BackMusic.wav"
#define pBONUSAPPEAR "Resources/Audio/BonusAppear.wav"
#define pBRICKBROKEN "Resources/Audio/BrickBroken.wav"
#define pBULLETBREAK "Resources/Audio/BulletBreak.wav"
#define pDYING "Resources/Audio/Dying.wav"
#define pENEMYDIE "Resources/Audio/EnemyDie.wav"
#define pEXTRALFE "Resources/Audio/ExtraLife.wav"
#define pFINISHMAP "Resources/Audio/FinishMap.wav"
#define pGAMEOVER "Resources/Audio/GameOver.wav"
#define pGETCOIN "Resources/Audio/GetCoin.wav"
#define pHEADSHOOT "Resources/Audio/HeadShoot.wav"
#define pJUMP "Resources/Audio/Jump.wav"
#define pLEVELUP "Resources/Audio/LevelUp.wav"
#define pMENUCHANGE "Resources/Audio/MenuChange.wav"
#define pMENUMUSIC "Resources/Audio/MenuMusic.wav"
#define pPAUSE "Resources/Audio/Pause.wav"
#define pPIPE "Resources/Audio/pipe.wav"
#define pSHOOT "Resources/Audio/Shoot.wav"
#define pSMALLER "Resources/Audio/Smaller.wav"
#define pSOUND1 "Resources/Audio/sound1.wav"
#define pSTANDUP "Resources/Audio/StandUp.wav"
#define pWIN "Resources/Audio/Win.wav"
#pragma endregion

#pragma region path map
#define pTILE "Resources/Maps/tiles.png"
#define pMAP1 "Resources/Maps/map1.txt"
#define pMAP1_LISTOBJECT "Resources/Maps/map1_ListObject.txt"
#define pMAP1_BINARYTREE "Resources/Maps/map1_BinaryTree.txt"

#pragma endregion







