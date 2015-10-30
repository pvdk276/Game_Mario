#include "Sprite.h"
#include "Transformation.h"

CSprite::CSprite(LPD3DXSPRITE spriteHandler, LPCSTR filePath, int width, int height, int count, int spritePerRow, int transparentColor)
{
	this->spriteHandler = spriteHandler;
	this->width = width;
	this->height = height;
	this->count = count;
	this->spritePerRow = spritePerRow;
	this->curIndex = 0;

	timeAnimation = 0;
	timeCurrent = 0;

	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filePath, &info);
	if (FAILED(result))
	{
		MessageBox(NULL, "Cannot get image info from file", "Error", MB_OK);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	spriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&image);

	if (FAILED(result))
	{
		MessageBox(NULL, "Cannot create texture form file", "Error", MB_OK);
		return;
	}
}

CSprite::~CSprite()
{

}

void CSprite::Next()
{
	curIndex = (curIndex + 1) % count;
}

void CSprite::Reset()
{
	curIndex = 0;
}

void CSprite::PositionSprite()
{
	rect.top = (curIndex / spritePerRow) * height;
	rect.left = (curIndex % spritePerRow) * width;
	rect.bottom = rect.top + height;
	rect.right = rect.left + width;
}

void CSprite::Render(float x, float y, float vpx, float vpy, float direction)
{
	/*RECT rect;
	rect.top = (curIndex / spritePerRow) * height;
	rect.left = (curIndex % spritePerRow) * width;
	rect.bottom = rect.top + height;
	rect.right = rect.left + width;*/

	D3DXVECTOR3 position((float)x, (float)y, 0);
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -vpx;
	mt._42 = vpy;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 center((float)width / 2, (float)height / 2, 0);

	D3DXMATRIX currentMatrix;
	spriteHandler->GetTransform(&currentMatrix);
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	if (direction < 0)
	{
		D3DXVECTOR3 p(-vp_pos.x, vp_pos.y, 0);

		D3DXMATRIX newMatrix;
		D3DXMatrixIdentity(&newMatrix);
		newMatrix._11 = -1;
		newMatrix._22 = 1;

		spriteHandler->SetTransform(&newMatrix);

		spriteHandler->Draw(
			image,
			&rect,
			&center,
			&p,
			D3DCOLOR_XRGB(255, 255, 255)
			);

		spriteHandler->SetTransform(&currentMatrix);
	}
	else
	{
		D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);

		spriteHandler->Draw(
			image,
			&rect,
			&center,
			&p,
			D3DCOLOR_XRGB(255, 255, 255)
			);
	}
	spriteHandler->End();

	//Next();
	UpdateSprite();
}

void CSprite::UpdateSprite() {
	PositionSprite();
}

void CSprite::UpdateSprite(float _time, int _spriteBegin, int _SpriteEnd, int _flag) 
{
	if (timeAnimation != 0) 
	{
		if (timeCurrent >= timeAnimation)
		{
			if (_flag == -1)

				//nó bay m?t luôn ?ó
			{
				curIndex--;
				if (curIndex < _spriteBegin) {
					curIndex = _SpriteEnd;
				}
				if (curIndex > _SpriteEnd) {
					curIndex = _SpriteEnd;
				}
			}
			if (_flag == 1)
			{
				curIndex++;
				if (curIndex < _spriteBegin) {
					curIndex = _spriteBegin;
				}
				if (curIndex > _SpriteEnd) {
					curIndex = _spriteBegin;
				}
			}
			PositionSprite();
			timeCurrent = 0;
		}
		else
		{
			timeCurrent += _time;
		}
	}
}

void CSprite::RenderMap(float posX, float posY, float vpx, float vpy, int value)
{
	RECT rect;
	rect.top = ((value - 1) / spritePerRow) * height;
	rect.left = ((value - 1) % spritePerRow) * width;
	rect.bottom = rect.top + height;
	rect.right = rect.left + width;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 p = CTransformation::getInstance()->Trans(posX, posY, vpx, vpy);

	spriteHandler->Draw(
		image,
		&rect,
		NULL, //&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
		);
	spriteHandler->End();
}