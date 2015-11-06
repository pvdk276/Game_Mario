#include "HiddenObject.h"

CHiddenObject::CHiddenObject()
{

}

CHiddenObject::~CHiddenObject()
{

}

CBox CHiddenObject::GetBox()
{
	CBox box(position.x, position.y, width, height, 0.0f, 0.0f);
	return box;
}