#pragma once
class ItemInfo : public World {
private:
	Texture* texture;
	int imageNumber;
	int itemType;
public:
	ItemInfo(int value = -1);
	void ChangeImage(int value) { imageNumber = value; }
	void ChangeType(int value) { itemType = value; }
	int GetType() { return itemType; }
	void Render();
	LPDIRECT3DTEXTURE9 GetTexture() { return texture->GetTexture(); }
};