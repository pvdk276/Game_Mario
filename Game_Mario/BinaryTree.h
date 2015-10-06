#pragma once

#include <vector>
#include "BinaryNode.h"
#include "FileUtils.h"
#include "Singleton.h"

class CBinaryTree : public CSingleton<CBinaryTree>
{
public:
	CBinaryNode* rootNode;
	std::vector<CGameObject*>* listCurrentObject;

	CBinaryTree();

	bool init(std::string listObjectPath, std::string binaryTreePath);

	void loadQuadTree(std::vector<CGameObject*> listObject, std::string binaryTreePath);

	void buildTree(CBinaryNode* node, std::vector<CBinaryNode*> listQuadNode);

	//get list current object in view port
	void loadListCurrentObject(CBinaryNode* node, int posX, int posY, int width, int height);

	std::vector<CGameObject*> loadListObject(std::string listObjectPath);
};