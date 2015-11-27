#include "Texture.h"

CTexture::CTexture(char* fileName)
{
	m_szFileName = fileName;
	this->load();
}

CTexture::~CTexture()
{
	if (m_lpTexture != NULL)
		m_lpTexture->Release();
	if (m_szFileName)
		delete m_szFileName;
}

void CTexture::load()
{
	D3DXIMAGE_INFO info;
	HRESULT result;
	//Load hình t? ???ng d?n c?a file
	result = D3DXGetImageInfoFromFile(m_szFileName, &info);

	if (result != D3D_OK)
	{
		char str[255];
		sprintf_s(str, "[texture.cpp] Failed to get information from image file [%s]", m_szFileName);
		OutputDebugString(str);
		return;
	}

	RECT s = { 0, 0, info.Width, info.Height };
	this->m_rectSize = s;

	LPDIRECT3DDEVICE9 dev = CGameGraphic::getInstance()->GetDevice();
	if (!dev)
	{
		OutputDebugString("[texture.cpp] Can not get device to Load Image From File.");
		return;
	}
	//Hàm t?o texture t? file
	result = D3DXCreateTextureFromFileEx(
		dev,
		m_szFileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), //Màu ?? t?y
		&info,
		NULL,
		&m_lpTexture
		);

	if (result != D3D_OK)
	{
		char str[255];
		sprintf_s(str, "[texture.cpp] Failed to create texture from file [%s]", m_szFileName);
		OutputDebugString(str);
		return;
	}
}

void CTexture::Draw(D3DXVECTOR2 pos)
{
	D3DXVECTOR3 position(pos.x, pos.y, 0);
	LPD3DXSPRITE spriteHandler = CGameGraphic::getInstance()->spriteHandler;
	if (!spriteHandler)
	{
		OutputDebugString("[texture.cpp] Can not get sprite handler to draw.");
		return;
	}

	spriteHandler->Draw(m_lpTexture, &m_rectSize, NULL, &position, 0xFFFFFFFF);
}

