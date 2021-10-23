#pragma once

#define RUSH_DELAY 2
#define RUSH_DISTANCE 2

class Pig : public Enemy
{
public:
	enum State
	{
		IDLE,
		LEFTMOVE,
		RIGHTMOVE
	};
private:
	State state;

	bool isRush;
	float rushDelayTime;
	float rushAngle;
	float rushDistance;

	Vector2 rushDestination;

public:
	Pig();
	~Pig();

	virtual void EnemyActions() override;
	virtual void LoadActions() override;
	virtual void Idle() override;

	void SetActions(State state);

	// Enemy을(를) 통해 상속됨
	
};