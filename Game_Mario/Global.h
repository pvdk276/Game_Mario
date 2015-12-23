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

#define TIME_ANIMATION  0.5f	//Tính bằng giây
#define STANDING 1
#define RUNNING 2
#define MARIO_GRAVITY = 0.5f

#define GAME_NAME "Game_Mario"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GAME_FPS 60
#define GRAVITY  -600.0f

#define PI 3.14159265f

#pragma region Các h?ng s? ID ki?u ??i t??ng game

#define ID_GRASS_CAN_FALL           0
#define ID_GRASS					2
#define ID_WATER	 				1
#define ID_SBOX						3

#define ID_ROCKMAN					10
#define ID_TILE						11
#define ID_RUNNING_MAN				12
#define ID_ITEM_BLOCK               13
#define ID_ITEM_FLYING              14
#define ID_ENEMY_SNIPER				15
#define ID_ENEMY_SHELTER			16
#define ID_BRIDGE					17
#define ID_GUN_BLOCK				18
#define ID_GUN_MACHINE				19
#define ID_BOSS_ONE					20
#define ID_BOSS_ONE_ENEMY			21
#define ID_BOSS_ONE_GUN_LEFT		22
#define ID_BOSS_ONE_GUN_RIGHT		23
#define ID_BOSS_ONE_HEART			24
#define ID_STONE_FLYING				25
#define ID_STONE_FALLING_POINT		26
#define ID_STONE_FALLING			27
#define ID_FIRE						28
#define ID_ENEMY_DIVER				29
#define ID_ENEMY_MACHINE			30
#define ID_GRENADE					31
#define ID_TANK					    32
#define ID_BOSS_THREE				33
#define ID_BOSS_THREE_CHILD			34
#define ID_BOSS_THREE_BULLET		35
#define ID_BOSS_TWO					36
#define ID_BOSS_TWO_BULLET			37
#define ID_BOSS_TWO_ARM_HEAD		38
#define ID_BOSS_TWO_ARM_BODY		39
#define ID_BOSS_THREE_DOOR			40
#define ID_BOSS_TWO_LEFT_HAND		41
#define ID_BOSS_TWO_RIGHT_HAND		42


#define ID_R_BULLET					200
#define ID_M_BULLET					201
#define ID_S_BULLET					202
#define ID_F_BULLET					203
#define ID_L_BULLET					204
#define ID_ENEMY_SMALL_WHITE_BULLET	205
#define ID_ENEMY_SMALL_RED_BULLET	206
#define ID_ENEMY_BIG_BULLET			207
#define ID_BOSS_ONE_BULLET			208
#define ID_ENEMY_DIVER_BULLET		209


#define ID_M_ITEM					300
#define ID_B_ITEM					301
#define ID_F_ITEM					302
#define ID_S_ITEM					303
#define ID_L_ITEM					304
#define ID_R_ITEM					305
#define ID_EAGLE_ITEM				306

#define ID_SMALL_EXPLOSION			400
#define ID_BIG_EXPLOSION			401
#define ID_BULLET_EXPLOSION		    402
#define ID_ENEMY_EXPLOSION          403
#define ID_ENEMY_FALL_IN_WATER      404

#pragma endregion

#pragma region Các h?ng s? ID c?a sprite

#define	ID_SPRITE_ROCKMAN_STAND				0
#define	ID_SPRITE_ROCKMAN_STAND_FIRE		1
#define ID_SPRITE_ROCKMAN_PREPARE_RUN		2
#define ID_SPRITE_ROCKMAN_RUN				3
#define ID_SPRITE_ROCKMAN_RUN_FIRE			4
#define ID_SPRITE_ROCKMAN_JUMP				5
#define ID_SPRITE_ROCKMAN_JUMP_FIRE			6
#define ID_SPRITE_ROCKMAN_STAIR				7
#define ID_SPRITE_ROCKMAN_STAIR_FIRE		8
#define ID_SPRITE_ROCKMAN_STAIR_END			9
#define ID_SPRITE_ROCKMAN_START 			10
#define ID_SPRITE_BILL_SWIM_HIDE			11
#define ID_SPRITE_BILL_SWIM_STAND			12
#define	ID_SPRITE_BILL_SWIM_FIRE            13
#define	ID_SPRITE_BILL_SWIM_LOOK_TOP        14
#define	ID_SPRITE_BILL_SWIM_LOOK_ABOVE		15
#define	ID_SPRITE_BILL_SWIM_GRASS_UP	sz	16
#define ID_SPRITE_BILL_DYING				17
#define ID_SPRITE_BILL_DIE					18

#define ID_SPRITE_R_BULLET					19
#define ID_SPRITE_S1_BULLET					20
#define ID_SPRITE_S2_BULLET					21
#define ID_SPRITE_S3_BULLET					22
#define ID_SPRITE_L_BULLET					23
#define ID_SPRITE_F_BULLET					24
#define ID_SPRITE_ENEMY_SMALL_WHITE_BULLET	25

#define ID_SPRITE_BULLET_EXPLOSION		    26

#define ID_SPRITE_FLY_ITEM					27
#define ID_SPRITE_M_ITEM					28
#define ID_SPRITE_B_ITEM					29
#define ID_SPRITE_F_ITEM					30
#define ID_SPRITE_S_ITEM					31
#define ID_SPRITE_L_ITEM					32
#define ID_SPRITE_R_ITEM					33

#define ID_SPRITE_SMALL_EXPLOSION			34
#define ID_SPRITE_BIG_EXPLOSION				35

#define ID_SPRITE_ITEM_BLOCK_CLOSE		    36
#define ID_SPRITE_ITEM_BLOCK_CHANGING		37
#define ID_SPRITE_ITEM_BLOCK_OPEN		    38

#define ID_SPRITE_ENEMY_SNIPER_STAND		39
#define ID_SPRITE_ENEMY_SNIPER_STAND_FIRE	40
#define ID_SPRITE_ENEMY_SNIPER_TOP			41
#define ID_SPRITE_ENEMY_SNIPER_TOP_FIRE		42
#define ID_SPRITE_ENEMY_SNIPER_BOT			43
#define ID_SPRITE_ENEMY_SNIPER_BOT_FIRE		44

#define ID_SPRITE_ENEMY_EXPLOSION		    45

#define ID_SPRITE_ENEMY_SHELTER_HIDE		46
#define ID_SPRITE_ENEMY_SHELTER_RISE		47
#define ID_SPRITE_ENEMY_SHELTER_SIT			48
#define ID_SPRITE_ENEMY_SHELTER_STAND		49
#define ID_SPRITE_ENEMY_SHELTER_STAND_FIRE  50
#define ID_SPRITE_ENEMY_SHELTER_BOT			51
#define ID_SPRITE_ENEMY_SHELTER_BOT_FIRE	52
#define ID_SPRITE_ENEMY_SHELTER_DIE			53

#define ID_SPRITE_GUN_BLOCK_GUN				54
#define ID_SPRITE_GUN_BLOCK_BASE_CLOSE		55
#define ID_SPRITE_GUN_BLOCK_BASE_CHANGING	56
#define ID_SPRITE_GUN_BLOCK_BASE_OPEN		57

#define ID_SPRITE_GUN_MACHINE_CHANGE_QUATER	58
#define ID_SPRITE_GUN_MACHINE_CHANGE_HAFT	59
#define ID_SPRITE_GUN_MACHINE_LEFT			60
#define ID_SPRITE_GUN_MACHINE_TOP			61
#define ID_SPRITE_GUN_MACHINE_UP			62

#define ID_SPRITE_BOSS_ONE_HEART			63
#define ID_SPRITE_BOSS_ONE_GUN_LEFT_FIRE	64
#define ID_SPRITE_BOSS_ONE_GUN_LEFT_REFIRE	65
#define ID_SPRITE_BOSS_ONE_GUN_RIGHT_FIRE	66
#define ID_SPRITE_BOSS_ONE_GUN_RIGHT_REFIRE	67

#define ID_SPRITE_BRIDGE1					68
#define ID_SPRITE_BRIDGE2					69
#define ID_SPRITE_BRIDGE3					70
#define ID_SPRITE_BRIDGE4					71
#define ID_SPRITE_BRIDGE5					72

#define ID_SPRITE_ENEMY_RUN					73
#define ID_SPRITE_ENEMY_JUMP				74
#define ID_SPRITE_ENEMY_DIE					75

#define ID_SPRITE_STONE_FLYING              76
#define ID_SPRITE_STONE_FALLING             77
#define ID_SPRITE_FIRE			            78

#define ID_SPRITE_ENEMY_DIVER_DIVE			79
#define ID_SPRITE_ENEMY_DIVER_FIRE		    80

#define ID_SPRITE_ENEMY_MACHINE_STAND		81
#define ID_SPRITE_ENEMY_MACHINE_FIRE		82

#define ID_SPRITE_GRENADE					83

#define ID_SPRITE_TANK_LEFT_1				84
#define ID_SPRITE_TANK_LEFT_RUN_1			85
#define ID_SPRITE_TANK_BOT_1				86
#define ID_SPRITE_TANK_BOT_RUN_1			87
#define ID_SPRITE_TANK_DOWN_1				88
#define ID_SPRITE_TANK_DOWN_RUN_1			89
#define ID_SPRITE_TANK_LEFT_2				90
#define ID_SPRITE_TANK_LEFT_RUN_2			91
#define ID_SPRITE_TANK_BOT_2				92
#define ID_SPRITE_TANK_BOT_RUN_2			93
#define ID_SPRITE_TANK_DOWN_2				94
#define ID_SPRITE_TANK_DOWN_RUN_2			95
#define ID_SPRITE_TANK_LEFT_3				96
#define ID_SPRITE_TANK_LEFT_RUN_3			97
#define ID_SPRITE_TANK_BOT_3				98
#define ID_SPRITE_TANK_BOT_RUN_3			99
#define ID_SPRITE_TANK_DOWN_3				100
#define ID_SPRITE_TANK_DOWN_RUN_3			101
#define ID_SPRITE_TANK_LEFT_4				102
#define ID_SPRITE_TANK_LEFT_RUN_4			103
#define ID_SPRITE_TANK_BOT_4				104
#define ID_SPRITE_TANK_BOT_RUN_4			105
#define ID_SPRITE_TANK_DOWN_4				106
#define ID_SPRITE_TANK_DOWN_RUN_4			107

#define ID_SPRITE_ENEMY_SMALL_RED_BULLET	108

#define ID_SPRITE_BOSS_THREE_APPEARING		110

#define ID_SPRITE_ENEMY_FALL_IN_WATER		109

#define ID_SPRITE_BOSS_THREE_APPEARING		110
#define ID_SPRITE_BOSS_THREE_APPEARED		111
#define ID_SPRITE_BOSS_THREE_OPENING		112
#define ID_SPRITE_BOSS_THREE_OPENED			113
#define ID_SPRITE_BOSS_THREE_CLOSING		114
#define ID_SPRITE_BOSS_THREE_CHILD			115

#define ID_SPRITE_BOSS_TWO_BULLET			116
#define ID_SPRITE_BOSS_TWO_ARM_HEAD			117
#define ID_SPRITE_BOSS_TWO_ARM_BODY			118
#define ID_SPRITE_BOSS_THREE_DOOR			119
#define ID_SPRITE_BOSS_ONE_DIE				120
#define ID_SPRITE_EAGLE_ITEM				121
#define ID_SPRITE_BOSS_THREE_DIE			122


#define ID_SPRITE_BOSS_TWO_MOUTH_CLOSING	123
#define ID_SPRITE_BOSS_TWO_MOUTH_OPENING	124
#define ID_SPRITE_BOSS_TWO_MOUTH_OPENED		125
#define ID_SPRITE_BOSS_TWO_HIDE				126
#define ID_SPRITE_BOSS_TWO_APPEAR			127
#define ID_SPRITE_BOSS_TWO_DIE				128


// Debug box sprite.
#define ID_TEXTURE_BILL_BOX					900
#define ID_TEXTURE_WATER_BOX				901
#define ID_TEXTURE_GROUND_BOX				902



#pragma endregion

#pragma region Các h?ng s? ID c?a texture

#define ID_TEXTURE_BILL						0


////??nh ngh?a ID c?a hình ch?a tile các map
#define ID_TEXTURE_MAP1_TILES				101
#define ID_TEXTURE_MAP2_TILES				102
#define ID_TEXTURE_MAP3_TILES				103

#define ID_TEXTURE_ICON_ROCK_MAN			6969
#define ID_TEXTURE_ICON_ROCK_MAN_GRAY		6970
#define ID_TEXTURE_BACKGROUND_2				6971
#define ID_TEXTURE_BACKGROUND_3				6972
#define ID_TEXTURE_BACKGROUND_4 			6973
#define ID_TEXTURE_GAME_TITLE 				6974

#pragma endregion

#pragma region Các h?ng s? ID c?a sound

#define ID_SOUND_OP_THEME					0
#define ID_SOUND_LEVEL1_THEME				1
#define ID_SOUND_LEVEL2_THEME				2
#define ID_SOUND_LEVEL3_THEME				3
#define ID_SOUND_END_THEME					4
#define ID_SOUND_CONTRA_FIRE				5
#define ID_SOUND_CONTRA_DEAD				6
#define ID_SOUND_FALL						7
#define ID_SOUND_GUN_UP						8
#define ID_SOUND_BOSS_DEAD					9
#define ID_SOUND_GAME_OVER_THEME			10

#pragma endregion

#pragma region Các h?ng s? ID c?a Level

#define ID_LEVEL1							1
#define ID_LEVEL2							2
#define ID_LEVEL3							3
#define ID_END_GAME							4

#pragma endregion

#pragma region Các h?ng chu?i ???ng d?n c?a file map

#define MAP1_PATH							"Resources\\Data\\Map1.txt"
#define MAP2_PATH							"Resources\\Data\\Map2.txt"
#define MAP3_PATH							"Resources\\Data\\Map3.txt"

#pragma endregion

#pragma region Các h?ng chu?i ???ng d?n c?a file resource

#define TEXTURE_PATH						"Resources\\Data\\PlayTextureData.txt"
#define SPRITE_PATH							"Resources\\Data\\PlaySpriteData.txt"
#define SOUND_PATH							"Resources\\Data\\PlaySoundData.txt"

#pragma endregion

#pragma region Các h?ng chu?i ???ng d?n c?a file HLSL

#define HLSL1_PATH							"Resources\\Data\\Map1HLSL.fx"
#define HLSL2_PATH							"Resources\\Data\\Map2HLSL.fx"
#define HLSL3_PATH							"Resources\\Data\\Map3HLSL.fx"
#define HLSL_EAGLE_PATH						"Resources\\Data\\ItemEagleHLSL.fx"

#pragma endregion


