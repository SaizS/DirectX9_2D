#include "framework.h"

TextureEditor::TextureEditor(wstring dataName) : dataName(dataName), fileName(NULL)
{
	LoadButton();
}

TextureEditor::TextureEditor(string fileName) : fileName(fileName)
{
	dataName = L"";
	LoadButton();
}

TextureEditor::~TextureEditor()
{
}

void TextureEditor::Update()
{
	Draw();
	PixWorld();
	Delete();
	Save();

	if (KEYDOWN(VK_F8))
		Load();

	if (curObject != NULL)
	{
		curObject->pos = MOUSEPOS;
		curObject->Update();
	}
	for (Button* button : buttons)
		button->Update();

	if (objects.size() == 0)
		return;

	if (objects.size() == 27)
		printf("%f %f \n", objects[4]->pos.x, objects[4]->pos.y);

	for (Object* object : objects)
		object->Update();
}

void TextureEditor::Render()
{
	for (Button* button : buttons)
		button->Render();
	if(curObject!=NULL)
	curObject->Render();

	if (objects.size() == 0)
		return;

	for (Object* object : objects)
	{
		//sort(objects.begin(), objects.end(), Compair);
		object->Render();
	}
}

void TextureEditor::Click(Texture* texture)
{
	curObject = new Object(texture);
	curObject->SetCollider(texture->GetSize());
}

void TextureEditor::SetFilePath(wstring str)
{
	curObject->SetFilePath(str);
}

void TextureEditor::Draw()
{
	if (curObject == NULL)
		return;

	if (KEYDOWN(VK_LBUTTON))
	{
		Object* object = new Object(curObject->GetTexture());
		object->pos = curObject->pos;
		object->SetFilePath(curObject->GetFilePath());
		object->SetCollider(*curObject->GetColider());
		objects.push_back(object);
	}
}

void TextureEditor::PixWorld()
{
	if (objects.size() == 0)
		return;

	if (KEYDOWN(VK_LBUTTON))
	{
		for (Object* object : objects)
		{
			if (object->Collision(MOUSEPOS))
			{
				curWorld = object;
				break;
			}
		}
	}

	if (KEYPRESS(VK_SHIFT) && curWorld != NULL)
	{
		if (KEYPRESS(VK_LBUTTON))
		{
			curWorld->pos = MOUSEPOS;
		}

		if (KEYPRESS(VK_UP))
			curWorld->offset.y -= DELTA * 300;

		if (KEYPRESS(VK_DOWN))
			curWorld->offset.y += DELTA * 300;

		if (KEYPRESS(VK_LEFT))
			curWorld->offset.x -= DELTA * 300;

		if (KEYPRESS(VK_RIGHT))
			curWorld->offset.x += DELTA * 300;

		curWorld->SetCollider(*curWorld->GetColider());
	}
	else if(curWorld != NULL)
	{
		if (KEYPRESS(VK_UP))
			curWorld->offset.y -= DELTA * 30;

		if (KEYPRESS(VK_DOWN))
			curWorld->offset.y += DELTA * 30;

		if (KEYPRESS(VK_LEFT))
			curWorld->offset.x -= DELTA * 30;

		if (KEYPRESS(VK_RIGHT))
			curWorld->offset.x += DELTA * 30;

		curWorld->SetCollider(*curWorld->GetColider());
	}

	if (KEYPRESS(VK_RBUTTON) && curWorld != NULL)
	{
		Vector2 size = (INPUTMANAGER->GetMousePos() - curWorld->pos) * 2;
		curWorld->SetCollider(size);
	}

	if (KEYDOWN(VK_SPACE))
	{
		curWorld = NULL;
		curObject = NULL;
	}

	if (KEYPRESS(VK_LCONTROL))
	{
		if (KEYDOWN('Z'))
		{
			if (objects.size() > 0)
			{
				objects.pop_back();
			}
		}
	}
}

void TextureEditor::Delete()
{
	if (KEYDOWN(VK_DELETE) && curWorld != NULL)
	{
		int count = 0;
		for (Object* object : objects)
		{
			if (object == curWorld)
			{
				objects.erase(objects.begin() + count);
				break;
			}
			count++;
		}
	}
}

void TextureEditor::LoadButton()
{
	Vector2 startPos = { 1800, 0 };
	int width = 5;
	for (int i = 0; i < 20; i++)
	{
		wstring str = L"Object/" + to_wstring(i) + L".png";
		Vector2 pos;
		pos.x = startPos.x + (i % width) * 400;
		pos.y = startPos.y + (i / width) * 400;
		Button* button = new Button(TEXTURE->Add(str), pos);
		button->SetFilePath(str);
		buttons.push_back(button);
		buttons[i]->SetTextureEvent(bind(&TextureEditor::Click, this, placeholders::_1));
		buttons[i]->SetWstringEvent(bind(&TextureEditor::SetFilePath, this, placeholders::_1));
	}
}

void TextureEditor::Save() // 바이너리 저장시 오브젝트 갯수가 일정수를 초과하면 Load시 터져버림 - 대안으로 fstream 사용
{
	if (KEYDOWN(VK_F7))
	{
		/*
		BinaryWriter* w = new BinaryWriter(dataName);

		vector<TextureData> data;

		for (Object* object : objects)
		{
			TextureData temp;
			string str;
			str.assign(object->GetFilePath().begin(), object->GetFilePath().end());
			temp.filePath = str;
			temp.x = object->pos.x;
			temp.y = object->pos.y;
			data.push_back(temp);
		}

		w.UInt(data.size());

		w->UInt(objects.size());

		for (int i = 0; i < objects.size(); i++)
		{
			string str;
			wstring ws = objects[i]->GetFilePath();
			str.assign(ws.begin(), ws.end());
			w->String(str);
			w->Float(objects[i]->pos.x);
			w->Float(objects[i]->pos.y);
			w->Float(objects[i]->collider.x);
			w->Float(objects[i]->collider.y);
			w->Float(objects[i]->offset.x);
			w->Float(objects[i]->offset.y);
		}
		//w.Byte(data.data(), sizeof(TextureData) * data.size());
		delete w;
		*/

		ofstream outFile(fileName);

		outFile << objects.size() << endl;

		for (int i = 0; i < objects.size(); i++)
		{
			string str;
			wstring ws = objects[i]->GetFilePath();
			str.assign(ws.begin(), ws.end());
			outFile << str << endl;
			outFile << objects[i]->pos.x << endl;
			outFile << objects[i]->pos.y << endl;
			outFile << objects[i]->collider.x << endl;
			outFile << objects[i]->collider.y << endl;
			outFile << objects[i]->offset.x << endl;
			outFile << objects[i]->offset.y << endl;
		}
		outFile.close();
	}
}

void TextureEditor::Load() // 마찬가지로 fstream 사용
{
	/*
	BinaryReader* r = new BinaryReader(L"Data/Test.map");

	UINT size = r->UInt();

	for (int i = 0; i < size; i++)
	{
		string str = r->String();
		wstring wstr;
		wstr.assign(str.begin(), str.end());
		Texture* texture = TEXTURE->Add(wstr);
		Object* temp = new Object(texture);
		temp->pos.x = r->Float();
		temp->pos.y = r->Float();
		temp->collider.x = r->Float();
		temp->collider.y = r->Float();
		temp->offset.x = r->Float();
		temp->offset.y = r->Float();
		temp->Update();

		temp->SetCollider(*temp->GetColider());

		objects.push_back(temp);
	}

	delete r;
	*/

	ifstream inFile(fileName);

	int size;
	inFile >> size;

	for(int i = 0; i < size; i++)
	{
		string str;
		Vector2 pos;
		Vector2 collider;
		Vector2 offset;
		inFile >> str >> pos.x >> pos.y >> collider.x >> collider.y >> offset.x >>
			offset.y;
		wstring wstr;
		wstr.assign(str.begin(), str.end());
		Texture* texture = TEXTURE->Add(wstr);
		Object* temp = new Object(texture);
		temp->pos = pos;
		temp->collider = collider;
		temp->offset = offset;
		temp->SetFilePath(wstr);
		temp->Update();

		temp->SetCollider(collider);

		objects.push_back(temp);
	}

	inFile.close();
}

bool TextureEditor::Compair(World* val1, World* val2)
{
	return val1->pos.y > val2->pos.y;
}
