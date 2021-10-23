#include "framework.h"

TextureManager* TextureManager::instance = NULL;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	for (auto index : textureList)
		index.second->Release();

	for (auto index : texturesBG)
		delete index;
}

TextureManager* TextureManager::GetInstance()
{
	return instance;
}

void TextureManager::Create()
{
	instance = new TextureManager();
}

void TextureManager::Delete()
{
	delete instance;
}

Texture* TextureManager::Add(wstring fileName, Vector2 start, Vector2 end, D3DCOLOR transColor)
{
	LPDIRECT3DTEXTURE9 dxTexture;
	if (textureList.count(fileName) > 0) {
		dxTexture = textureList[fileName];
	}
	else {
		D3DXCreateTextureFromFileEx(
			DEVICE,
			fileName.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			NULL,
			D3DFMT_A8B8G8R8,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			transColor,
			NULL,
			NULL,
			&dxTexture
		);
		textureList.insert({ fileName, dxTexture });
	}

	Texture* texture = new Texture(dxTexture, start, end);
	texturesBG.push_back(texture);
	return texture;
}

Texture* TextureManager::Add(wstring fileName, int frameX, int frameY, int maxFrameX, int maxFrameY, D3DCOLOR transColor)
{
	LPDIRECT3DTEXTURE9 dxTexture;
	if (textureList.count(fileName) > 0) {
		dxTexture = textureList[fileName];
	}
	else {
		D3DXCreateTextureFromFileEx(
			DEVICE,
			fileName.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			NULL,
			D3DFMT_A8B8G8R8,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			transColor,
			NULL,
			NULL,
			&dxTexture
		);
		textureList.insert({ fileName, dxTexture });
	}

	Texture* texture = new Texture(dxTexture, frameX, frameY, maxFrameX, maxFrameY);
	texturesBG.push_back(texture);
	return texture;
}
