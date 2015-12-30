#include "BinaryTree.h"
#include <string>
#include "GameGraphic.h"
#include "Land.h"
#include "Cloud.h"
#include "Pipe.h"
#include "Grass.h"
#include "Brick.h"
#include "Block.h"
#include "CoinBrick.h"
#include "Bonus.h"
#include "CarnivorousFlower.h"
#include "Stone.h"
#include "Enemy.h"
#include "Turtle.h"
#include "FireTurtle.h"
#include "Spring.h"
#include "Bar.h"
#include "Tower.h"


////load data from binary_tree_file_text to a list of binary node
//std::vector<CBinaryNode*> loadBinaryTree(std::vector<CBaseObject*> listObject, std::string binaryTreePath);
//
////arrange node into a binary tree, the input is list_binary_node
//void buildTree(CBinaryNode* node, std::vector<CBinaryNode*> listBinaryNode);
//
////load data from list_object_text_file
//std::vector<CBaseObject*> loadListObject(std::string listObjectPath);

CBinaryTree::CBinaryTree()
{
	rootNode = nullptr;
	listCurrentObject = new std::vector<CBaseObject*>();

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

bool CBinaryTree::Init(std::string listObjectPath, std::string binaryTreePath)
{
	std::vector<CBaseObject*> listObject = loadListObject(listObjectPath);

	std::vector<CBinaryNode*> listBinaryNode = loadBinaryTree(listObject, binaryTreePath);

	for (int i = 0; i < listBinaryNode.size(); i++)
	{
		if (listBinaryNode.at(i)->id == "00") rootNode = listBinaryNode.at(i);
	}

	buildTree(rootNode, listBinaryNode);

	return 1;
}

std::vector<CBinaryNode*> CBinaryTree::loadBinaryTree(std::vector<CBaseObject*> listObject, std::string binaryTreePath)
{
	std::vector<std::string> nodes = CFileUtils::getInstance()->loadFromFile(binaryTreePath);
	std::vector<CBinaryNode*> listBinaryNode;

	for (int i = 0; i < nodes.size(); i++)
	{
		std::vector<std::string> items = CFileUtils::getInstance()->split(nodes.at(i), '\t');
		std::string id = items.at(0);
		float x = atof(items.at(1).c_str());
		float y = atof(items.at(2).c_str());
		float width = atof(items.at(3).c_str());
		float height = atof(items.at(4).c_str());
		CBinaryNode* node = new CBinaryNode(id, x, y, width, height);

		if (items.size() > 5)
		{
			for (int k = 5; k < items.size(); k++)
			{
				for (int j = 0; j < listObject.size(); j++)
				{
					std::string id = std::to_string(listObject.at(j)->id);

					if (items.at(k) == id)
					{
						node->listObject.push_back(listObject.at(j));
						break;
					}
				}
			}
		}

		listBinaryNode.push_back(node);
	}

	return listBinaryNode;
}

void CBinaryTree::buildTree(CBinaryNode* node, std::vector<CBinaryNode*> listBinaryNode)
{
	std::string idL = node->id + "00";
	std::string idR = node->id + "01";

	for (int i = 0; i < listBinaryNode.size(); i++)
	{
		std::string id = listBinaryNode.at(i)->id;
		if (id == idL) node->nodeL = listBinaryNode.at(i);
		else if (id == idR) node->nodeR = listBinaryNode.at(i);
	}

	if (node->nodeL != nullptr) buildTree(node->nodeL, listBinaryNode);
	if (node->nodeR != nullptr) buildTree(node->nodeR, listBinaryNode);
}

void CBinaryTree::loadListCurrentObject(CBinaryNode* node, int posX, int posY, int width, int height)
{
	if (node->IsIntersecting(posX, posY, width, height))
	{
		//check if leaf node
		if (node->nodeL == nullptr && node->nodeR == nullptr)
		{
			for (int i = 0; i < node->listObject.size(); i++)
			{
				//check if not added yet
				if (std::find(listCurrentObject->begin(), listCurrentObject->end(), node->listObject.at(i)) == listCurrentObject->end())
				{
					listCurrentObject->push_back(node->listObject.at(i));
				}
			}
		}
		else
		{
			if (node->nodeL != nullptr) loadListCurrentObject(node->nodeL, posX, posY, width, height);

			if (node->nodeR != nullptr) loadListCurrentObject(node->nodeR, posX, posY, width, height);
		}
	}
}

std::vector<CBaseObject*> CBinaryTree::loadListObject(std::string listObjectPath)
{
	std::vector<CBaseObject*> listObject;
	//= new std::vector<GameObject*>();
	std::vector<std::string> objects = CFileUtils::getInstance()->loadFromFile(listObjectPath);
	for (int i = 0; i < objects.size(); i++)
	{
		std::vector<std::string> items = CFileUtils::getInstance()->split(objects.at(i), '\t');
		int id = stoi(items.at(0));
		int typeId = stoi(items.at(1));
		float x = atof(items.at(2).c_str());
		float y = atof(items.at(3).c_str());
		float width = atof(items.at(4).c_str());
		float height = atof(items.at(5).c_str());
		CBaseObject* gameObject;
		D3DXVECTOR2 position = D3DXVECTOR2(x, y);
		switch (typeId)
		{
		case 1: //left-land
			gameObject = new CLand(id, LEFT_LAND, position, land);
			break;

		case 2: //center-land
			gameObject = new CLand(id, CENTER_LAND, position, land);
			break;

		case 3: //right-land
			gameObject = new CLand(id, RIGHT_LAND, position, land);
			break;

		case 4: //spring
			gameObject = new CSpring(id, position, spring);
			break;

		case 5: //pipe
			gameObject = new CPipe(id, PIPE, position, pipe, nullptr);
			break;

		case 6: //tank
			break;

		case 7: //stone
			gameObject = new CStone(id, position, stone);
			break;

		case 8: //grass
			gameObject = new CGrass(id, position, grass);
			break;

		case 9: //carnivorous-flower
			gameObject = new CCarnivorousFlower(id, position, carnivorousFlower);
			break;

		case 10: //brick
			gameObject = new CBrick(id, position, brick);
			break;

		case 11: //left-pipe
			break;

		case 12: //left-pipe-1
			break;

		case 13: //left-pipe-2
			break;

		case 14: //cloud
			gameObject = new CCloud(id, position, cloud);
			break;

		case 15: //carnivorous-flower-pipe
			gameObject = new CPipe(id, CARNIVOROUS_FLOWER_PIPE, position, pipe, carnivorousFlower);
			break;

		case 16: //pipe-down
			gameObject = new CPipe(id, PIPE_DOWN, position, pipe, NULL);
			break;

		case 17: //pipe-down-1
			gameObject = new CPipe(id, PIPE_DOWN_1, position, pipe, NULL);
			break;

		case 18: //pipe-down-2
			gameObject = new CPipe(id, PIPE_DOWN_2, position, pipe, NULL);
			break;

		case 19: //pipe-up-1
			gameObject = new CPipe(id, PIPE_UP_1, position, pipe, NULL);
			break;

		case 20: //pipe-up-2
			gameObject = new CPipe(id, PIPE_UP_2, position, pipe, NULL);
			break;

		case 21: //tower
			gameObject = new CTower(id, position, tower);
			break;

		case 22: //bar-down
			gameObject = new CBar(id, BAR_DOWN, position, bar);
			break;

		case 23: //bar-up
			gameObject = new CBar(id, BAR_UP, position, bar);
			break;

		case 24: //bar-right
			gameObject = new CBar(id, BAR_RIGHT, position, bar);
			break;

		case 25: //bar
			gameObject = new CBar(id, BAR, position, bar);
			break;

		case 26: //coin
			gameObject = new CBonus(id, COIN, position, coin);
			break;

		case 27: //coin-block
			gameObject = new CBlock(id, COIN_BLOCK, position, secretBlock, coin);
			break;

		case 28: //coin-brick
			gameObject = new CCoinBrick(id, COIN_BRICK, position, brick, coin);
			break;

		case 29: //flower-block
			gameObject = new CBlock(id, FLOWER_BLOCK, position, secretBlock, flower);
			break;

		case 30: //green-mushroom-block
			gameObject = new CBlock(id, GREEN_MUSHROOM_BLOCK, position, secretBlock, mushroom);
			break;

		case 31: //red-mushroom-block
			gameObject = new CBlock(id, RED_MUSHROOM_BLOCK, position, secretBlock, mushroom);
			break;

		case 32: //star-block
			gameObject = new CBlock(id, STAR_BLOCK, position, secretBlock, star);
			break;

		case 33: //enemy
			gameObject = new CEnemy(id, position, enemy);
			break;

		case 34: //wing-turtle
			gameObject = new CTurtle(id, WING_TURTLE, position, turtle);
			break;

		case 35: //turtle
			gameObject = new CTurtle(id, TURTLE, position, turtle);
			break;

		case 36: //fire-turtle
			gameObject = new CFireTurtle(id, position, turtle2);
			break;
		}

		listObject.push_back(gameObject);
	}

	return listObject;
}