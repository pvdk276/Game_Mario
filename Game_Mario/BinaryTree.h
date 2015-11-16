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
	bool init(std::string listObjectPath, std::string binaryTreePath);

	//get list current object in view port
	void loadListCurrentObject(CBinaryNode* node, int posX, int posY, int width, int height);
};