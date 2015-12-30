#pragma once

#include <vector>
#include "BinaryNode.h"
#include "FileUtils.h"
#include "Singleton.h"

class CBinaryTree : public CSingleton<CBinaryTree>
{
public:
	CBinaryNode* rootNode;
	std::vector<CBaseObject*>* listCurrentObject;

	//default init function
	CBinaryTree();

	//build a binary tree
	bool Init(std::string listObjectPath, std::string binaryTreePath);

	//get list current object in view port
	void loadListCurrentObject(CBinaryNode* node, int posX, int posY, int width, int height);

	//load data from binary_tree_file_text to a list of binary node
	std::vector<CBinaryNode*> loadBinaryTree(std::vector<CBaseObject*> listObject, std::string binaryTreePath);

	//arrange node into a binary tree, the input is list_binary_node
	void buildTree(CBinaryNode* node, std::vector<CBinaryNode*> listBinaryNode);

	//load data from list_object_text_file
	std::vector<CBaseObject*> loadListObject(std::string listObjectPath);

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