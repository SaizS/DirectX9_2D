#pragma once

class CaveScene : public Scene
{
private:
	Player* player;
	Cave* cave;

public:
	CaveScene(Player* player);
	~CaveScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void SetPos(Vector2 pos) override;
	virtual void PlayerSpawn() override {
		player->Spawn();
	}
};