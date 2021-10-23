#include "framework.h"

WorldEditor::WorldEditor(wstring fileName) : selectWorld(NULL), pos(0, 0), size(0, 0), isCenter(false), isSize(false), fileName(fileName),
isSelect(false), isSave(false), isLoad(false), time(0), isPush(false), startPos(0, 0), endPos(0, 0), isWorldRender(true), isDrawMode(true)
{
	worldCount = totalWorlds.size();
}

WorldEditor::~WorldEditor()
{
	if (totalWorlds.size() > 0)
	{
		for (World* world : totalWorlds)
			delete world;
	}
}

void WorldEditor::Update()
{
	if (KEYDOWN('P'))
		isDrawMode ? isDrawMode = false : isDrawMode = true;

	if (isDrawMode)
		DrawMode();
	else
		EditMode();

	Save();
	Load();

	Revert();

	if (KEYDOWN('U'))
		isWorldRender ? isWorldRender = false : isWorldRender = true;

	if (totalWorlds.size() == 0)
		return;

	for (World* world : totalWorlds)
		world->Update();

	worldCount = totalWorlds.size();
}

void WorldEditor::Render()
{
	if (!isWorldRender || totalWorlds.size() == 0)
		return;

	for (World* world : totalWorlds)
	{
		world->SetWorld();
		world->RenderBox();
	}
}

void WorldEditor::Save()
{
	if (KEYDOWN('I'))
	{
		BinaryWriter writer(fileName);

		vector<Data> worldData;

		for (World* world : totalWorlds)
		{
			Data data;
			data.size = *world->GetColider();
			data.pos = world->pos;
			worldData.push_back(data);
		}

		DWORD fileSize = 0;

		writer.UInt(worldData.size());
		writer.Byte(worldData.data(), sizeof(Data) * worldData.size());
	}
}

void WorldEditor::Load()
{
	if (KEYDOWN('O'))
	{
		BinaryReader reader(fileName);

		UINT size = reader.UInt();

		vector<Data> worldData;
		worldData.resize(size);

		if (totalWorlds.size() >= size)
			return;

		void* ptr = (void*)worldData.data();

		reader.Byte(&ptr, sizeof(Data) * size);

		for (UINT i = 0; i < size; i++)
		{
			World* world = new World();
			world->SetCollider(worldData[i].size);
			world->pos = worldData[i].pos;

			totalWorlds.push_back(world);
		}
	}
}

void WorldEditor::DrawMode()
{
	if (KEYDOWN(VK_LBUTTON))
	{
		if (!isCenter)
		{
			isCenter = true;
			startPos = MOUSEPOS;
		}
	}

	if (KEYPRESS(VK_LBUTTON))
	{
		if (isCenter)
		{
			if (!isPush)
			{
				World* world = new World();
				totalWorlds.push_back(world);
				isPush = true;
			}
			endPos = MOUSEPOS;
			World* world = totalWorlds.back();

			size = endPos - startPos;
			size.x = abs(size.x);
			size.y = abs(size.y);
			pos = (startPos + endPos) * 0.5f;
			world->SetSize(size);
			world->pos = pos;
		}
	}

	if (KEYUP(VK_LBUTTON))
	{
		if (isCenter)
		{
			isCenter = false;
			isPush = false;
		}
	}
}

void WorldEditor::EditMode()
{
	bool isCheck = false;

	if (KEYDOWN(VK_LBUTTON))
	{
		for (World* world : totalWorlds)
		{
			if (world->Collision(INPUTMANAGER->GetMousePos()))
			{
				isSelect = true;
				world->SetColor(RED);
				selectWorld = world;
				isCheck = true;
				break;
			}
		}
	}

	if (selectWorld != nullptr)
	{
		if (KEYPRESS('W'))
		{
			selectWorld->pos.y -= 10.0f * DELTATIME;
		}
		if (KEYPRESS('S'))
		{
			selectWorld->pos.y += 10.0f * DELTATIME;
		}
		if (KEYPRESS('A'))
		{
			selectWorld->pos.x -= 10.0f * DELTATIME;
		}
		if (KEYPRESS('D'))
		{
			selectWorld->pos.x += 10.0f * DELTATIME;
		}
		//selectWorld->SetCollider(*selectWorld->GetColider());

		if (KEYPRESS(VK_LBUTTON) && !isCheck)
		{
			size = (INPUTMANAGER->GetMousePos() - selectWorld->pos) * 2;
			size.x = abs(size.x);
			size.y = abs(size.y);
			selectWorld->SetSize(size);
		}

		if (KEYDOWN(VK_RBUTTON))
		{
			isSelect = false;
			selectWorld->SetColor(GREEN);
			selectWorld = NULL;
		}
	}
}

void WorldEditor::Revert()
{
	if (KEYPRESS(VK_LCONTROL))
	{
		if (KEYDOWN('Z'))
		{
			if (totalWorlds.size() == 0)
				return;

			totalWorlds.pop_back();
		}
	}
}