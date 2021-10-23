#pragma once

class Mountain : public World
{
private:
	Texture* backGround;
	Object* trees;

	vector<Info*> textureList;
	vector<Object*> buildings;

	vector<World*> collisionWorld;

	Player* player;

	vector<Paticle*> paticles;
public:
	Mountain();
	~Mountain();

	void Update();
	void Render();

	void ObjectCollision();

	void ChangeMap();

	void SetPlayer(Player* player);
	void SetPortion(vector<Potion*> data);
	void CollectPaticle();
	void MouseCollision();

	void Load();
	
	static bool Compare(World* val1, World* val2);
};