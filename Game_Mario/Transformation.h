#pragma once
#include "Singleton.h"
#include <d3dx9.h>

class CTransformation : public CSingleton<CTransformation>
{
public:
	D3DXVECTOR3 Trans(int posX, int posY, int vpx, int vpy)
	{
		D3DXVECTOR3 position((float)posX, (float)posY, 0);
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._22 = -1.0f;
		mt._41 = -vpx;
		mt._42 = vpy;
		D3DXVECTOR4 vp_pos;
		D3DXVec3Transform(&vp_pos, &position, &mt);

		D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
		return p;
	}
};