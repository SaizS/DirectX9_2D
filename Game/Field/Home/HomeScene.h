#pragma once

class HomeScene : public Scene
{
private:
	Home* home;
	Player* player;

public:
	HomeScene(Player* player);
	~HomeScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void SetPos(Vector2 pos) override;
	virtual void PlayerSpawn() override { player->Spawn(); };

};