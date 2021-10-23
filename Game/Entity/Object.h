#pragma once

class Player;
class Enemy;

class Object : public Info
{
private:
	Texture* texture;
	wstring filePath;

public:
	Object(Texture* texture);
	~Object();

	virtual void Update() override;
	virtual void Render() override;

	void SetFilePath(wstring value) { filePath = value; }
	void SetTexture(Texture* texture) { this->texture = texture; }

	wstring GetFilePath() { return filePath; }
	Texture* GetTexture() { return texture; }

	void PlayerCollision(World* player) { CollisionMove(player); }
	void EnemyCollision(World* enemy) { CollisionMove(enemy); }
};