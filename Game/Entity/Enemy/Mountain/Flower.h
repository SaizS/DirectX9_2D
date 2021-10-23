#pragma once

#define FLOWER_BULLET_COUNT 5
#define FLOWER_ATTACK_DELAY 4

class Flower : public Enemy
{
public:
	enum State
	{
		IDLE,
		FIRE
	};

private:
	State state;

	float attackDelay;

	vector<Flower_Bullet*> bullets;

	bool isFire;

public:
	Flower();
	~Flower();

	virtual void Update() override;
	virtual void Render() override;

	virtual void EnemyActions() override;
	virtual void LoadActions() override;
	virtual void Idle() override;

	void SetActions(State state);

	void BulletCollision();
};