#include "BinaryTree.h"
#include <string>
#include "Ground.h"
#include "Cloud.h"
#include "Pipe.h"
#include "Grass.h"
#include "Brick.h"
#include "MushroomBlock.h"
#include "CoinBrick.h"
#include "CoinBlock.h"
#include "Coin.h"
#include "Flower.h"
#include "Stone.h"
#include "PipeUp1.h"
#include "MushroomEnemy.h"
#include "Turtle.h"
#include "WingTurtle.h"
#include "FireTurtle.h"


//load data from binary_tree_file_text to a list of binary node
std::vector<CBinaryNode*> loadBinaryTree(std::vector<CGameObject*> listObject, std::string binaryTreePath);

//arrange node into a binary tree, the input is list_binary_node
void buildTree(CBinaryNode* node, std::vector<CBinaryNode*> listBinaryNode);

//load data from list_object_text_file
std::vector<CGameObject*> loadListObject(std::string listObjectPath);

CBinaryTree::CBinaryTree()
{
	rootNode = nullptr;
	listCurrentObject = new std::vector<CGameObject*>();
}

bool CBinaryTree::init(std::string listObjectPath, std::string binaryTreePath)
{
	std::vector<CGameObject*> listObject = loadListObject(listObjectPath);

	std::vector<CBinaryNode*> listBinaryNode = loadBinaryTree(listObject, binaryTreePath);

	for (int i = 0; i < listBinaryNode.size(); i++)
	{
		if (listBinaryNode.at(i)->id == "00") rootNode = listBinaryNode.at(i);
	}

	buildTree(rootNode, listBinaryNode);

	return 1;
}

std::vector<CBinaryNode*> loadBinaryTree(std::vector<CGameObject*> listObject, std::string binaryTreePath)
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

void buildTree(CBinaryNode* node, std::vector<CBinaryNode*> listBinaryNode)
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

std::vector<CGameObject*> loadListObject(std::string listObjectPath)
{
	std::vector<CGameObject*> listObject;
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
		CGameObject* gameObject;
		switch (typeId)
		{
		case 4: gameObject = new CGround();
			break;
		case 112: gameObject = new CCloud();
			break;
		case 7: gameObject = new CPipe();
			break;
		case 59: gameObject = new CGrass();
			break;
		case 62: gameObject = new CBrick();
			break;
		case 218: gameObject = new CMushroomBlock();
			break;
		case 221: gameObject = new CCoinBrick();
			break;
		case 222: gameObject = new CCoinBlock();
			break;
		case 223: gameObject = new CCoin();
			break;
		case 115: gameObject = new CFlowerPipe();//Ch?a có
			break;
		case 147: gameObject = new CpipeDown1();//Ch?a  có
			break;
		case 42: gameObject = new CStone();
			break;
		case 61: gameObject = new CFlower();
			break;
		case 169: gameObject = new CPipeUp1();
			break;
		}
		//= new CGameObject(id, typeId, x, y, width, height);
		listObject.push_back(gameObject);
	}

	return listObject;
}