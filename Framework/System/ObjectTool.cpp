#include "framework.h"

ObjectTool::ObjectTool(string fileName) : curObject(NULL), page(ONE), isDraw(true), fileName(fileName), isActive(true), speed(10)
{
	board = TEXTURE->Add(L"Resource/Textures/UI/MapEditorBoard.png");

	drawMode = new Object(TEXTURE->Add(L"Resource/Textures/UI/DrawMode.png"));
	drawMode->pos = { 0, 175 };
	drawMode->SetParent(&world);

	editMode = new Object(TEXTURE->Add(L"Resource/Textures/UI/EditMode.png"));
	editMode->pos = { 0, 175 };
	editMode->SetParent(&world);

	LoadButton();
	LoadObjectCollision();

	D3DXMatrixIdentity(&view);

	pos = { 300, 400 };
}

ObjectTool::~ObjectTool()
{
	delete saveButton;
	delete loadButton;
	delete leftButton;
	delete rightButton;

	if (objects.size() > 0)
		for (Object* object : objects)
			delete object;

	if (pageOne.size() > 0)
		for (Button* one : pageOne)
			delete one;

	if (pageTwo.size() > 0)
		for (Button* two : pageTwo)
			delete two;

	if (pageThree.size() > 0)
		for (Button* three : pageThree)
			delete three;

	delete drawMode;
	delete editMode;
}

void ObjectTool::Update()
{
	if (KEYDOWN(VK_SHIFT))
		isActive ? isActive = false : isActive = true;

	Mode();

	if (curObject != NULL)
		curObject->Update();

	if (objects.size() != 0)
	{
		for (Object* object : objects)
			object->Update();
	}

	World::Update();

	if (!isActive)
		return;

	Move();

	switch (page)
	{
	case ObjectTool::ONE:
		for (Button* one : pageOne)
			one->Update();
		break;
	case ObjectTool::TWO:
		for (Button* two : pageTwo)
			two->Update();
		break;
	case ObjectTool::THREE:
		for (Button* three : pageThree)
			three->Update();
		break;
	default:
		break;
	}

	saveButton->Update();
	loadButton->Update();
	leftButton->Update();
	rightButton->Update();

	isDraw ? drawMode->Update() : editMode->Update();
}

void ObjectTool::Render()
{
	CAM->SetView();

	sort(objects.begin(), objects.end(), Compare);

	if (objects.size() != 0)
	{
		for (Object* object : objects)
		{
			object->Render();
			object->RenderBox();
		}
	}

	if (curObject != NULL)
	{
		curObject->Render();
		curObject->RenderBox();
	}

	if (!isActive)
		return;

	DEVICE->SetTransform(D3DTS_VIEW, &view);

	SetWorld();

	board->AlphaRender();

	switch (page)
	{
	case ObjectTool::ONE:
		for (Button* one : pageOne)
			one->Render();
		break;
	case ObjectTool::TWO:
		for (Button* two : pageTwo)
			two->Render();
		break;
	case ObjectTool::THREE:
		for (Button* three : pageThree)
			three->Render();
		break;
	default:
		break;
	}

	saveButton->Render();
	loadButton->Render();
	leftButton->Render();
	rightButton->Render();

	isDraw ? drawMode->Render() : editMode->Render();
}

void ObjectTool::Move()
{
	if (KEYPRESS(VK_UP))
		pos.y -= speed;
	if (KEYPRESS(VK_DOWN))
		pos.y += speed;
	if (KEYPRESS(VK_LEFT))
		pos.x -= speed;
	if (KEYPRESS(VK_RIGHT))
		pos.x += speed;

	INPUTMANAGER->SetToolPos(-pos);

	if (KEYPRESS('Z'))
	{
		scale.x -= DELTA * 2.0f;
		scale.y -= DELTA * 2.0f;
	}
	if (KEYPRESS('X'))
	{
		scale.x += DELTA * 2.0f;
		scale.y += DELTA * 2.0f;
	}
}

void ObjectTool::Mode()
{
	if (KEYDOWN(VK_TAB))
	{
		if (isDraw)
			isDraw = false;
		else
			isDraw = true;

		if (curObject != NULL)
		{
			curObject->SetColor(GREEN);
			curObject = NULL;
		}
	}

	if (isDraw)
		Draw();
	else
		Edit();
}

void ObjectTool::Draw()
{
	if (curObject == NULL)
		return;

	if (KEYDOWN(VK_LBUTTON))
	{
		Object* object = new Object(curObject->GetTexture());
		object->pos = MOUSEPOS;
		Vector4 data = objectCollisionBox[curObject->GetFilePath()];

		if (data.x < 0)
			data = { 100, 100, 0, 0 };

		object->SetOffset({ data.z, data.w });
		object->SetCollider({ data.x, data.y });
		object->SetFilePath(curObject->GetFilePath());
		objects.push_back(object);
	}

	if (KEYDOWN(VK_SPACE))
		curObject = NULL;

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

	curObject->pos = MOUSEPOS;

	if (KEYDOWN(VK_RBUTTON))
	{
		curObject = NULL;
	}
}

void ObjectTool::Edit()
{
	if (objects.size() == 0)
		return;

	if (KEYDOWN(VK_LBUTTON))
	{
		for (Object* object : objects)
		{
			if (object->Collision(MOUSEPOS))
			{
				if (curObject != NULL)
					curObject->SetColor(GREEN);
				curObject = object;
				curObject->SetColor(RED);
				break;
			}
		}
	}

	if (KEYPRESS(VK_LCONTROL) && curObject != NULL)
	{
		if (KEYPRESS(VK_LBUTTON))
		{
			curObject->pos = MOUSEPOS;
		}

		if (KEYPRESS('T'))
			curObject->offset.y -= DELTA * 300;

		if (KEYPRESS('G'))
			curObject->offset.y += DELTA * 300;

		if (KEYPRESS('F'))
			curObject->offset.x -= DELTA * 300;

		if (KEYPRESS('H'))
			curObject->offset.x += DELTA * 300;

		curObject->SetSize(*curObject->GetColider());
	}
	else if (curObject != NULL)
	{
		if (KEYPRESS('T'))
			curObject->offset.y -= DELTA * 30;

		if (KEYPRESS('G'))
			curObject->offset.y += DELTA * 30;

		if (KEYPRESS('F'))
			curObject->offset.x -= DELTA * 30;

		if (KEYPRESS('H'))
			curObject->offset.x += DELTA * 30;

		curObject->SetSize(*curObject->GetColider());
	}

	if (KEYPRESS(VK_RBUTTON) && curObject != NULL)
	{
		Vector2 size = (INPUTMANAGER->GetMousePos() - curObject->pos) * 2;
		size.x = abs(size.x);
		size.y = abs(size.y);
		curObject->SetSize(size);
	}

	if (KEYDOWN(VK_SPACE))
	{
		curObject = NULL;
	}

	if (KEYDOWN(VK_DELETE))
	{
		if (curObject != NULL)
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (curObject == objects[i])
				{
					objects.erase(objects.begin() + i);
					curObject = NULL;
					break;
				}
			}
		}
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

	if (KEYDOWN(VK_DELETE))
	{
		if (curObject != NULL)
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (curObject == objects[i])
				{
					objects.erase(objects.begin() + i);
					break;
				}
			}
		}
	}
}

void ObjectTool::SetObject(Texture* texture)
{
	if (curObject == NULL)
		curObject = new Object(texture);
	else if (curObject->GetTexture() == texture)
		return;
	else
		curObject->SetTexture(texture);
}

void ObjectTool::SetFilePath(wstring path)
{
	curObject->SetFilePath(path);
}

void ObjectTool::LoadButton()
{
	Vector2 startPos = { -120, -200 };
	int width = 3;

	//PageOne
	for (int i = 0; i < 12; i++)
	{
		wstring buttonPath = L"Object/Button/" + to_wstring(i) + L".png";
		wstring objectPath = L"Object/" + to_wstring(i) + L".png";
		Vector2 buttonPos;
		buttonPos.x = startPos.x + (i % width) * 120;
		buttonPos.y = startPos.y + (i / width) * 100;

		Button* button = new Button(TEXTURE->Add(buttonPath), TEXTURE->Add(objectPath), buttonPos);
		button->SetParent(&world);
		button->SetFilePath(objectPath);
		button->SetTextureEvent(bind(&ObjectTool::SetObject, this, placeholders::_1));
		button->SetWstringEvent(bind(&ObjectTool::SetFilePath, this, placeholders::_1));
		pageOne.push_back(button);
	}

	for (int i = 12; i < 24; i++)
	{
		wstring buttonPath = L"Object/Button/" + to_wstring(i) + L".png";
		wstring objectPath = L"Object/" + to_wstring(i) + L".png";
		Vector2 buttonPos;
		buttonPos.x = startPos.x + ((i - 12) % width) * 120;
		buttonPos.y = startPos.y + ((i - 12) / width) * 100;

		Button* button = new Button(TEXTURE->Add(buttonPath), TEXTURE->Add(objectPath), buttonPos);
		button->SetParent(&world);
		button->SetFilePath(objectPath);
		button->SetTextureEvent(bind(&ObjectTool::SetObject, this, placeholders::_1));
		button->SetWstringEvent(bind(&ObjectTool::SetFilePath, this, placeholders::_1));
		pageTwo.push_back(button);
	}

	for (int i = 24; i < 36; i++)
	{
		wstring buttonPath = L"Object/Button/" + to_wstring(i) + L".png";
		wstring objectPath = L"Object/" + to_wstring(i) + L".png";
		Vector2 buttonPos;
		buttonPos.x = startPos.x + ((i - 24) % width) * 120;
		buttonPos.y = startPos.y + ((i - 24) / width) * 100;

		Button* button = new Button(TEXTURE->Add(buttonPath), TEXTURE->Add(objectPath), buttonPos);
		button->SetParent(&world);
		button->SetFilePath(objectPath);
		button->SetTextureEvent(bind(&ObjectTool::SetObject, this, placeholders::_1));
		button->SetWstringEvent(bind(&ObjectTool::SetFilePath, this, placeholders::_1));
		pageThree.push_back(button);
	}

	saveButton = new Button(TEXTURE->Add(L"Resource/Textures/UI/saveButton.png"), { -40, 225 });
	saveButton->SetParent(&world);
	saveButton->SetVoidEvent(bind(&ObjectTool::Save, this));

	loadButton = new Button(TEXTURE->Add(L"Resource/Textures/UI/loadButton.png"), { 40, 225 });
	loadButton->SetParent(&world);
	loadButton->SetVoidEvent(bind(&ObjectTool::Load, this));

	leftButton = new Button(TEXTURE->Add(L"Resource/Textures/UI/LeftButton.png"), { -120, 225 });
	leftButton->SetParent(&world);
	leftButton->SetVoidEvent(bind(&ObjectTool::LeftButton, this));

	rightButton = new Button(TEXTURE->Add(L"Resource/Textures/UI/RightButton.png"), { 120, 225 });
	rightButton->SetParent(&world);
	rightButton->SetVoidEvent(bind(&ObjectTool::RightButton, this));
}

void ObjectTool::LoadObjectCollision()
{
	objectCollisionBox.insert({ L"Object/0.png", Vector4(33.6799, 33.6899, 0, 81.005) });
	objectCollisionBox.insert({ L"Object/1.png", Vector4(32.48, 29.7307, 0, 81.083) });
	objectCollisionBox.insert({ L"Object/2.png", Vector4(32.48, 33.6407, 0, 80.7041) });
	objectCollisionBox.insert({ L"Object/3.png", Vector4(62, 35.1241, 1.61158, 94.395) });
	objectCollisionBox.insert({ L"Object/4.png", Vector4(58, 51.1128, 0, 86.2444) });
	objectCollisionBox.insert({ L"Object/20.png", Vector4(94, 32.5413, -0.564052, 31.1105) });
	objectCollisionBox.insert({ L"Object/21.png", Vector4(58, 23.668, 0, 21.6318) });
	objectCollisionBox.insert({ L"Object/27.png", Vector4(26, 9.35278, -1.41865, 12.0811) });
}

void ObjectTool::Save()
{
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

void ObjectTool::Load()
{
	ifstream inFile(fileName);

	int size;
	inFile >> size;

	if (objects.size() >= size)
		return;

	for (int i = 0; i < size; i++)
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
		temp->SetCollider(collider);

		temp->Update();

		objects.push_back(temp);
	}

	inFile.close();
}

void ObjectTool::LeftButton()
{
	if (page == ONE)
		return;
	int num = (int)page - 1;
	page = (Page)num;
}

void ObjectTool::RightButton()
{
	if (page == THREE)
		return;
	int num = (int)page + 1;
	page = (Page)num;
}

bool ObjectTool::Compare(World* val1, World* val2)
{
	return val1->pos.y + val1->offset.y < val2->pos.y + val2->offset.y;
}