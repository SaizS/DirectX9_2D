#pragma once

class Flower_Bullet : public Info
{
private:
	Animation* bullet;

	bool isActive;
	float angle;
	float speed;
	float attack;

public:
	Flower_Bullet();
	~Flower_Bullet();

	virtual void Update() override;
	virtual void Render() override;

	void Fire(Vector2 pos, float angle);

	float GetAttack() { return attack;}
	bool GetIsActive() { return isActive; }

	void SetIsActive(bool value) { isActive = value; }

	void Load();
};