#pragma once

#define MAP MapEditor::GetInstance()

class MapEditor
{
private:
	static MapEditor* instance;
	MapEditor();
	~MapEditor();

	ObjectTool* tool;
	WorldEditor* editor;

	World* uiWorld;
	Texture* modeTexture;

	bool isTool;

public:
	static MapEditor* GetInstance();
	static void Create();
	static void Delete();

	void Update();
	void Render();

	void SetFilePath(string filePath) { tool->SetPath(filePath); }
	void SetFilePath(wstring filePath) { editor->SetFilePath(filePath); }
};