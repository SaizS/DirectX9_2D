#pragma once
#define DATA DataManager::GetInstance()

struct ItemData {

	int key; //아이템 고유 번호
	int image; //아이템 이미지 번호
	int type; //아이템의 타입, 0-재료 1-포션 2-장비
	int effect; //효과
	int amount; //분량
	UINT price; //가격
	UINT stack; //보유한 갯수

	ItemData(int key = -1, int image = -1, int type = 0, int effect = 0, int amount = 0, int stack = 0, int price = 0) {
		this->key = key;
		this->image = image;
		this->type = type;
		this->effect = effect;
		this->amount = amount;
		this->price = price;
		this->stack = stack;
	}
};

class DataManager {
private:
	//ItemData
	map<int, ItemData> itemList;
	vector<Texture*> itemTexture;
	vector<Texture*> itemInfoTexture;

	//MapData
	map<string, vector<Object*>> mapObjects;
	map<string, vector<World*>> mapCollsionWorlds;

	//Buff
	vector<Texture*> buffIconTexture;

	static DataManager* instance;
	DataManager();
	~DataManager();

public:
	static DataManager* GetInstance();
	static void Create();
	static void Delete();

	//Item
	void LoadItemData();
	ItemData GetItemData(int key);
	Texture* GetItemImage(int key);
	Texture* GetItemInfoImage(int key);
	Texture* GetBuffIconImage(int key);

	//Map
	void LoadMapData();
	vector<Object*> GetObjectData(string key);
	vector<World*> GetCollisionWorldData(string key);
};