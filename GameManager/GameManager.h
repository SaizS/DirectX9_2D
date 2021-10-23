#pragma once

class GameManager
{
private:
	Player* player;

public:
	GameManager();
	~GameManager();

	void ResourceLoad();
	void Update();
	void Render();

};