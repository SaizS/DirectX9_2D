#pragma once

class Character;

class TownScene : public Scene
{
private:
	Town* town;
	Player* player;

public:
	TownScene(Player* player);
	~TownScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void SetPos(Vector2 pos) override { player->pos = pos; }
	virtual void PlayerSpawn() override { player->Spawn(); };

};