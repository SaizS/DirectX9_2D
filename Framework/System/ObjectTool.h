#pragma once

class Object;

class ObjectTool : public World
{
private:
	enum Page
	{
		ONE,
		TWO,
		THREE
	}page;

	Texture* board;
	Object* drawMode;
	Object* editMode;

	vector<Button*> pageOne;
	vector<Button*> pageTwo;
	vector<Button*> pageThree;

	Button* saveButton;
	Button* loadButton;

	Button* leftButton;
	Button* rightButton;

	vector<Object*> objects;

	Object* curObject;

	D3DXMATRIX view;

	bool isDraw;

	string fileName;

	map<wstring, Vector4> objectCollisionBox;

	bool isActive;

	float speed;
public:
	ObjectTool(string fileName);
	~ObjectTool();

	void Update();
	void Render();

	void Move();

	void Mode();
	void Draw();
	void Edit();

	void SetObject(Texture* texture);
	void SetFilePath(wstring path);

	void LoadButton();
	void LoadObjectCollision();

	void Save();
	void Load();

	void LeftButton();
	void RightButton();

	void SetPath(string filePath) { fileName = filePath; }

	static bool Compare(World* val1, World* val2);
};