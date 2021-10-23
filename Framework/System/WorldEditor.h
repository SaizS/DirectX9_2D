#pragma once

struct Data
{
	Vector2 size;
	Vector2	pos;
};

class WorldEditor
{
	vector<World*> totalWorlds;

	World* selectWorld;

	Vector2 pos;
	Vector2 size;

	Vector2 startPos;
	Vector2 endPos;

	bool isDrawMode;

	bool isCenter;
	bool isSize;

	bool isSelect;

	bool isSave;
	bool isLoad;

	bool isWorldRender;

	float time;
	bool isPush;

	int worldCount;

	wstring fileName;

public:
	WorldEditor(wstring fileName);
	~WorldEditor();

	void Update();
	void Render();

	void Save();
	void Load();

	void DrawMode();
	void EditMode();
	void Revert();

	vector<World*> GetMap() { return totalWorlds; }

	void SetFilePath(wstring filePath) { fileName = filePath; }
};