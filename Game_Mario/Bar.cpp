#include "Bar.h"
#include "BinaryTree.h"

CBar::CBar(int id, ObjectName type, D3DXVECTOR2 position, CSprite* sprite) : CDynamicObject(id, position, sprite)
{
	this->type = type;
	this->width = 200;
	this->height = 32;
	direction = 1;

	if (type == BAR_DOWN) velocity.y = -100.0f;
	else if (type == BAR_UP) velocity.y = 100.0f;
	else if (type == BAR_RIGHT) velocity.x = 100.0f;
	else velocity = D3DXVECTOR2(0.0f, 0.0f);

	if(type == BAR_RIGHT) prePosition = position;
}


CBar::~CBar()
{
}

void CBar::Update(float delta_time)
{
	//check collision
	/*if (type == BAR_RIGHT)
	{
		for (int i = 0; i < CBinaryTree::getInstance()->listCurrentObject->size(); i++)
		{
			if (CBinaryTree::getInstance()->listCurrentObject->at(i)->type == BAR)
			{
				float normalx, normaly;
				float distancex, distancey;
				float value = CCollision::getInstance()->CheckCollision(
					CBinaryTree::getInstance()->listCurrentObject->at(i)->GetBox(),
					this->GetBox(),
					normalx,
					normaly,
					distancex,
					distancey,
					delta_time);

				if(value < 1) direction = -1 * direction;
			}
		}
	}	*/

	//update position
	/*if (type == BAR_DOWN) velocity.y = -100.0f;
	else if (type == BAR_UP) velocity.y = 100.0f;
	else if (type == BAR_RIGHT) velocity.x = 100.0f;*/

	position.x += velocity.x * delta_time * direction;
	position.y += velocity.y * delta_time;

	if (position.y < -16.0f) position.y = 766.0f;
	if (position.y > 766) position.y = -16.0f;
	if (position.x < prePosition.x)
	{
		position.x = prePosition.x;
		direction = -1 * direction;
	}
	//update animation
}

void CBar::Render()
{
	sprite->Render(position.x, position.y, CCamera::getInstance()->position.x, CCamera::getInstance()->position.y, 0);
}
