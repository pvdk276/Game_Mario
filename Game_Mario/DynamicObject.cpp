#include "DynamicObject.h"

CDynamicObject::CDynamicObject()
{

}

CDynamicObject::~CDynamicObject()
{

}

CBox CDynamicObject::GetBox()
{
	CBox box(position.x, position.y, width, height, velocity.x, velocity.y);
	return box;
}