#pragma once

class Home : public World
{
private:
	Texture* backGround;

	vector<Info*> textureList;
	vector<World*> collisionWorld;

	vector<Object*> buildings;

	Player* player;

public:
	Home();
	~Home();

	void Update();
	void Render();

	void SetPlayer(Player* player);

	void Load();

	void CollisionObject();

	void InTown();

	static bool Compare(World* val1, World* val2);
};