#pragma once

#include "BaseObject.h"
#include <vector>

class CBinaryNode
{
public:
	std::string id;
	float positionX; //toa do cua dinh top-left
	float positionY;
	float width;
	float height;

	CBinaryNode *nodeL;
	CBinaryNode *nodeR;

	std::vector<CBaseObject*> listObject;

	//init 1
	CBinaryNode();

	//init 2
	CBinaryNode(std::string id, float positionX, float positionY, float width, float height);

	//kiem tra co giao nhau voi view port hay ko
	bool IsIntersecting(float vp_X, float vp_Y, float vp_Width, float vp_Height);

	//kiem tra node co chua diem nay khong?
	bool IsContain(float positionX, float positionY);
};
