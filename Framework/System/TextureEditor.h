#pragma once

struct TextureData
{
	string filePath;
	float x;
	float y;
	float sizeX;
	float sizeY;
	float offX;
	float offY;
};

class Button;
class Object;
class Texture;

class TextureEditor
{
private:
	vector<Button*> buttons;
	vector<Object*> objects;
	Object* curObject;
	World* curWorld;

	wstring dataName;
	string fileName;
public:
	TextureEditor(wstring dataName);
	TextureEditor(string fileName);
	~TextureEditor();

	void Update();
	void Render();

	void Click(Texture* texture);
	void SetFilePath(wstring str);

	void Draw();
	void PixWorld();
	void Delete();

	void LoadButton();

	void Save();
	void Load();

	static bool Compair(World* val1, World* val2);

};