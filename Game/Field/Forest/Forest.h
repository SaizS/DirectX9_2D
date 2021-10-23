#pragma once

class Forest : public World
{
private:
	vector<Texture*> backGround;
	Animation* waterAni;

	Player* player;

	vector<Info*> textureList;
	vector<Object*> buildings;

	vector<World*> collisionWorlds;

	vector<Enemy*> slimes;
	vector<Enemy*> chicken;
	vector<Enemy*> mushRoom;

	vector<Paticle*> paticles;

public:
	Forest();
	~Forest();

	void Update();
	void Render();

	void ChangeMap();

	void SetPlayer(Player* player) { this->player = player; textureList.push_back(player); }
	void InitPortion(vector<Potion*> data);

	void Load();
	void LoadAnimation();

	void ObjectCollision();
	void CollectPaticle();
	void MouseCollision();

	static bool Compare(World* val1, World* val2);
};