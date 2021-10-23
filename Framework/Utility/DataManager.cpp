#include "framework.h"

DataManager* DataManager::instance = NULL;

DataManager::DataManager()
{
	int width = 10;
	int height = 10;
	//아이템
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)	{
			itemTexture.push_back(TEXTURE->Add(L"Resource/Textures/Item/material.png", j, i, width, height));
		}
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			itemTexture.push_back(TEXTURE->Add(L"Resource/Textures/Item/potion.png", j, i, width, height));
		}
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			itemTexture.push_back(TEXTURE->Add(L"Resource/Textures/Item/material.png", j, i, width, height)); //key
		}
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			itemTexture.push_back(TEXTURE->Add(L"Resource/Textures/Item/flask.png", j, i, width, height)); //투사체용 텍스쳐
		}
	}

	//아이템 정보
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			itemInfoTexture.push_back(TEXTURE->Add(L"Resource/Textures/Item/materialInfo.png", j, i, width, height));
		}
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			itemInfoTexture.push_back(TEXTURE->Add(L"Resource/Textures/Item/potionInfo.png", j, i, width, height));
		}
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			itemInfoTexture.push_back(TEXTURE->Add(L"Resource/Textures/Item/materialInfo.png", j, i, width, height)); //key
		}
	}

	//버프 아이콘
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			buffIconTexture.push_back(TEXTURE->Add(L"Resource/Textures/UI/buffIcon.png", j, i, width, height));
		}
	}

	LoadItemData();
	LoadMapData();
}

DataManager::~DataManager()
{
}

DataManager* DataManager::GetInstance()
{
	return instance;
}

void DataManager::Create()
{
	instance = new DataManager();
}

void DataManager::Delete()
{
	delete instance;
}

void DataManager::LoadItemData()
{
	ifstream stream("Data/Save/item.txt", ios::in);
	int colCount = 8;
	int count = 0;
	string str; 
	while (true) {
		if (count < colCount) {
			stream >> str;
			count++;
			continue;
		}

		ItemData data;
		str.clear();
		stream >> str;
		data.key = -1;
		stream >> data.key;
		if (data.key == -1)
			return;
		stream >> data.image >> data.type >> data.effect >> data.amount >> data.stack >> data.price;
		itemList.insert({ data.key, data });
	}
}

ItemData DataManager::GetItemData(int key)
{
	if (key < 0 || key > 400)
		return ItemData();
	return itemList[key];
}

Texture* DataManager::GetItemImage(int key)
{
	if (key < 0 || key > 400)
		return NULL;
	return itemTexture[key];
}

Texture* DataManager::GetItemInfoImage(int key)
{
	if (key < 0 || key > 300)
		return NULL;
	return itemInfoTexture[key];
}

Texture* DataManager::GetBuffIconImage(int effectNum)
{
	if (effectNum < 0 || effectNum > 100)
		return NULL;
	return buffIconTexture[effectNum];
}

void DataManager::LoadMapData()
{
	//HomeObject
	ifstream inFile("Data/Map/HomeObject.txt");

	int homeObjectSize;
	inFile >> homeObjectSize;

	vector<Object*> homeObjects;

	for (int i = 0; i < homeObjectSize; i++)
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

		homeObjects.push_back(temp);
	}

	inFile.close();

	//HomeCollisionWorld
	BinaryReader homeReader(L"Data/Map/HomeCollision.map");

	UINT homeCollisionSize = homeReader.UInt();

	vector<Data> homeCollisionData;
	homeCollisionData.resize(homeCollisionSize);

	void* homePtr = (void*)homeCollisionData.data();

	homeReader.Byte(&homePtr, sizeof(Data) * homeCollisionSize);

	vector<World*> homeCollisionWorlds;

	for (UINT i = 0; i < homeCollisionSize; i++)
	{
		World* world = new World();
		world->pos = homeCollisionData[i].pos;
		world->SetCollider(homeCollisionData[i].size);
		homeCollisionWorlds.push_back(world);
	}

	//TownObject
	inFile = ifstream("Data/Map/TownObject.txt");

	int townObjectSize;
	inFile >> townObjectSize;

	vector<Object*> townObjects;

	for (int i = 0; i < townObjectSize; i++)
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

		townObjects.push_back(temp);
	}

	inFile.close();

	//TownCollisionWorld
	BinaryReader townReader(L"Data/Map/TownCollision.map");

	UINT townCollisionSize = townReader.UInt();

	vector<Data> townCollisionData;
	townCollisionData.resize(townCollisionSize);

	void* townPtr = (void*)townCollisionData.data();

	townReader.Byte(&townPtr, sizeof(Data) * townCollisionSize);

	vector<World*> townCollisionWorlds;

	for (UINT i = 0; i < townCollisionSize; i++)
	{
		World* world = new World();
		world->pos = townCollisionData[i].pos;
		world->SetCollider(townCollisionData[i].size);
		townCollisionWorlds.push_back(world);
	}

	//ForestObject
	inFile = ifstream("Data/Map/ForestObject.txt");

	int forestObjectSize;
	inFile >> forestObjectSize;

	vector<Object*> forestObjects;

	for (int i = 0; i < forestObjectSize; i++)
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

		forestObjects.push_back(temp);
	}

	inFile.close();

	//ForestCollisionWorld
	BinaryReader forestReader(L"Data/Map/ForestCollision.map");

	UINT forestCollisionSize = forestReader.UInt();

	vector<Data> forestCollisionData;
	forestCollisionData.resize(forestCollisionSize);

	void* forestPtr = (void*)forestCollisionData.data();

	forestReader.Byte(&forestPtr, sizeof(Data) * forestCollisionSize);

	vector<World*> forestCollisionWorlds;

	for (UINT i = 0; i < forestCollisionSize; i++)
	{
		World* world = new World();
		world->pos = forestCollisionData[i].pos;
		world->SetCollider(forestCollisionData[i].size);
		forestCollisionWorlds.push_back(world);
	}

	//MountainObject
	inFile = ifstream("Data/Map/MountainObject.txt");

	int mountainObjectSize;
	inFile >> mountainObjectSize;

	vector<Object*> mountainObjects;

	for (int i = 0; i < mountainObjectSize; i++)
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

		mountainObjects.push_back(temp);
	}

	inFile.close();

	//MountainCollisionWorld
	BinaryReader mountainReader(L"Data/Map/MountainCollision.map");

	UINT mountainCollisionSize = mountainReader.UInt();

	vector<Data> mountainCollisionData;
	mountainCollisionData.resize(mountainCollisionSize);

	void* mountainPtr = (void*)mountainCollisionData.data();

	mountainReader.Byte(&mountainPtr, sizeof(Data) * mountainCollisionSize);

	vector<World*> mountainCollisionWorlds;

	for (UINT i = 0; i < mountainCollisionSize; i++)
	{
		World* world = new World();
		world->pos = mountainCollisionData[i].pos;
		world->SetCollider(mountainCollisionData[i].size);
		mountainCollisionWorlds.push_back(world);
	}

	//CaveCollisionWorld
	BinaryReader caveReader(L"Data/Map/CaveCollision.map");

	UINT caveCollisionSize = caveReader.UInt();

	vector<Data> caveCollisionData;
	caveCollisionData.resize(caveCollisionSize);

	void* cavePtr = (void*)caveCollisionData.data();

	caveReader.Byte(&cavePtr, sizeof(Data)* caveCollisionSize);

	vector<World*> caveCollisionWorlds;

	for (UINT i = 0; i < caveCollisionSize; i++)
	{
		World* world = new World();
		world->pos = caveCollisionData[i].pos;
		world->SetCollider(caveCollisionData[i].size);
		caveCollisionWorlds.push_back(world);
	}

	//InsertMapObjectData
	mapObjects.insert({ "HomeObjects", homeObjects });
	mapObjects.insert({ "TownObjects", townObjects });
	mapObjects.insert({ "ForestObjects", forestObjects });
	mapObjects.insert({ "MountainObjects", mountainObjects});

	//InsertMapCollisionWorld
	mapCollsionWorlds.insert({ "HomeCollisionWorlds", homeCollisionWorlds });
	mapCollsionWorlds.insert({ "TownCollisionWorlds", townCollisionWorlds });
	mapCollsionWorlds.insert({ "ForestCollisionWorlds", forestCollisionWorlds });
	mapCollsionWorlds.insert({ "MountainCollisionWorlds", mountainCollisionWorlds });
	mapCollsionWorlds.insert({ "CaveCollisionWorlds", caveCollisionWorlds });
}

vector<Object*> DataManager::GetObjectData(string key)
{
	if(mapObjects.count(key) == 0)
		return vector<Object*>();

	return mapObjects[key];
}

vector<World*> DataManager::GetCollisionWorldData(string key)
{
	if(mapCollsionWorlds.count(key) == 0)
		return vector<World*>();

	return mapCollsionWorlds[key];
}
