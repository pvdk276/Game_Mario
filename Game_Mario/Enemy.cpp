#include "Enemy.h"

CEnemy::CEnemy(ObjectName type, D3DXVECTOR2 position, float width, float height, CSprite * sprite, float timeAmination, D3DXVECTOR2 maxVelocity, D3DXVECTOR2 maxAccel) : CLivingObject(type, position, width, height, sprite, timeAnimation, maxVelocity, maxAccel)
{

}

CEnemy::~CEnemy()
{
}

void CEnemy::UpdateAnimation(float delta_time)
{
	sprite->UpdateSprite(delta_time, 0, 1, direction);
}
