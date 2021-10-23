#pragma once

class ForestScene : public Scene
{
private:
	Forest* forest;
	Player* player;

public:
	ForestScene(Player* player);
	~ForestScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void PlayerSpawn() override { player->Spawn(); };

	virtual void SetPos(Vector2 pos) override { player->pos = pos; }

};