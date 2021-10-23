#pragma once
class ItemImage : public World {
private:
	Texture* texture;
	int imageNumber;
public:
	ItemImage(int value = -1);
	int GetImageNumber() { return imageNumber; }
	void ChangeImage(int value) { imageNumber = value; }
	void Update();
	void Render();
	void UnSetWorldRender();
	LPDIRECT3DTEXTURE9 GetTexture() { return texture->GetTexture(); }
};