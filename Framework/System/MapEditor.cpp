#include "framework.h"

MapEditor* MapEditor::instance = NULL;

MapEditor::MapEditor()
{
	tool = new ObjectTool("data.txt");
	editor = new WorldEditor(L"data.data");
	isTool = true;

	modeTexture = TEXTURE->Add(L"Resource/Textures/UI/ObjectMode.png");
}

MapEditor::~MapEditor()
{
	delete tool;
	delete editor;
}

MapEditor* MapEditor::GetInstance()
{
	return instance;
}

void MapEditor::Create()
{
	instance = new MapEditor();
}

void MapEditor::Delete()
{
	delete instance;
}

void MapEditor::Update()
{
	if (KEYDOWN('L'))
		isTool ? isTool = false : isTool = true;

	isTool ? tool->Update() : editor->Update();

	//uiWorld->Update();
}

void MapEditor::Render()
{
	isTool ? tool->Render() : editor->Render();

	/*uiWorld->SetWorld();

	modeTexture->Render();*/
}