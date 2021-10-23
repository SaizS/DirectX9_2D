#pragma once

class Cave : public World
{
private:
	Texture* backGround;
	Mage* mage;
	Player* player;

	vector<World*> collisionWorld;
public:
	Cave();
	~Cave();

	void Update();
	void Render();

	void SetPlayer(Player* player) { this->player = player; mage->SetPlayer(player); }

	void CollisionEvent();
};