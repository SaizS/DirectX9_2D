#pragma once

class Town : public World
{
private:
	Texture* backGround;
	Texture* water;
	Animation* waterObjets;

	Player* player;

	vector<Object*> buildings; // 건물	
	vector<Npc*> npcs;			//NPC

	vector<Info*> textureList; // 렌더용 텍스처 주소	

	Vector2 textureSize;

	vector<World*> collsionWorld;

public:
	Town();
	~Town();

	void Update();
	void Render();

	void SetPlayer(Player* player);
	void InitPortion(vector<Potion*> data);

	void Load();
	void LoadAnimation();

	void ObjectCollision();
	void WindowCollision();
	void PortionCollision();
	void MouseCollision();

	void NpcEvent();

	void ChangeMap();

	static bool Compare(World* val1, World* val2);
};