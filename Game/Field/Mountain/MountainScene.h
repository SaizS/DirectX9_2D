#pragma once

class MountainScene : public Scene
{
private:
	Mountain* mountain;
	Player* player;
public:
	MountainScene(Player* player);
	~MountainScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void SetPos(Vector2 pos) override;
	virtual void PlayerSpawn() override { player->Spawn(); }
};