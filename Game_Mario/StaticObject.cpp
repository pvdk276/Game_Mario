#include "StaticObject.h"

CStaticObject::CStaticObject()
{
}

CStaticObject::~CStaticObject()
{

}

CBox CStaticObject::GetBox()
{
	CBox box(position.x, position.y, width, height, 0.0f, 0.0f);
	return box;
}

