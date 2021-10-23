#pragma once

#define SLIME_JUMP_DELAY 2.0f

class Slime : public Enemy
{
private:
	enum State
	{
		IDLE,
		JUMP
	}state;

	vector<Animation*> blueSlime;
	vector<Animation*> purpleSlime;

	float jumpDelay;
	float jumpAngle;

public:
	Slime();
	~Slime();

	virtual void EnemyActions() override;
	virtual void LoadActions() override;
	virtual void Idle() override;

	
	void SetActions(State state);

	
};