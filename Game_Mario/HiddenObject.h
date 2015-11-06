#pragma once

#include "GameObject.h"

class CHiddenObject : public CGameObject
{
public:
	CHiddenObject();
	~CHiddenObject();
	CBox GetBox();
};