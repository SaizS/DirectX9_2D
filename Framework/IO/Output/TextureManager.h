#pragma once

#define TEXTURE TextureManager::GetInstance()

class TextureManager
{
private:
	static TextureManager* instance;
 	TextureManager();
	~TextureManager();

	map<wstring, LPDIRECT3DTEXTURE9> textureList;
	vector<Texture*> texturesBG;
public:
	static TextureManager* GetInstance();
	static void Create();
	static void Delete();

	Texture* Add(wstring fileName, Vector2 start = Vector2(0, 0), Vector2 end = Vector2(0, 0), D3DCOLOR transColor = MAGENTA);
	Texture* Add(wstring fileName, int frameX, int frameY, int maxFrameX, int maxFrameY, D3DCOLOR transColor = MAGENTA);
};

