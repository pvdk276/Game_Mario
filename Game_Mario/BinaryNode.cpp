#include "BinaryNode.h"

CBinaryNode::CBinaryNode()
{
	id = "";
	positionX = 0;
	positionY = 0;
	width = 0;
	height = 0;

	nodeL = nullptr;
	nodeR = nullptr;
}

CBinaryNode::CBinaryNode(std::string id, float positionX, float positionY, float width, float height)
{
	this->id = id;
	this->positionX = positionX;
	this->positionY = positionY;
	this->width = width;
	this->height = height;

	nodeL = nullptr;
	nodeR = nullptr;
}

bool CBinaryNode::IsIntersecting(float vp_X, float vp_Y, float vp_Width, float vp_Height)
{
	if (vp_X - vp_Width / 2 >= positionX && vp_X - vp_Width / 2 <= positionX + width) return true;

	if (vp_X + vp_Width / 2 >= positionX && vp_X + vp_Width / 2 <= positionX + width) return true;

	return false;
}

bool CBinaryNode::IsContain(float positionX, float positionY)
{
	if (positionX >= this->positionX && positionX <= (this->positionX + width))
	{
		if (positionY <= this->positionY && positionY >= (this->positionY - height))
		{
			return true;
		}
	}
	return false;
}