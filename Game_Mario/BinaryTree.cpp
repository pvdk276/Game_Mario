#include "BinaryTree.h"
#include <string>

CBinaryTree::CBinaryTree()
{
	rootNode = nullptr;
	listCurrentObject = new std::vector<CGameObject*>();

	//std::vector<CGameObject*> listObject = loadListObject(listObjectPath);
	//loadQuadTree(listObject, binaryTreePath);
}

bool CBinaryTree::init(std::string listObjectPath, std::string binaryTreePath)
{
	std::vector<CGameObject*> listObject = loadListObject(listObjectPath);
	loadQuadTree(listObject, binaryTreePath);

	return 1;
}

void CBinaryTree::loadQuadTree(std::vector<CGameObject*> listObject, std::string binaryTreePath)
{
	std::vector<std::string> nodes = CFileUtils::getInstance()->loadFromFile(binaryTreePath);
	std::vector<CBinaryNode*> listQuadNode;

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

		listQuadNode.push_back(node);
	}

	//find root node
	for (int i = 0; i < listQuadNode.size(); i++)
	{
		if (listQuadNode.at(i)->id == "00") rootNode = listQuadNode.at(i);
	}

	buildTree(rootNode, listQuadNode);
}

void CBinaryTree::buildTree(CBinaryNode* node, std::vector<CBinaryNode*> listQuadNode)
{
	std::string idL = node->id + "00";
	std::string idR = node->id + "01";

	for (int i = 0; i < listQuadNode.size(); i++)
	{
		std::string id = listQuadNode.at(i)->id;
		if (id == idL) node->nodeL = listQuadNode.at(i);
		else if (id == idR) node->nodeR = listQuadNode.at(i);
	}

	if (node->nodeL != nullptr) buildTree(node->nodeL, listQuadNode);
	if (node->nodeR != nullptr) buildTree(node->nodeR, listQuadNode);
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

std::vector<CGameObject*> CBinaryTree::loadListObject(std::string listObjectPath)
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
		CGameObject* gameObject = new CGameObject(id, typeId, x, y, width, height);
		listObject.push_back(gameObject);
	}

	return listObject;
}