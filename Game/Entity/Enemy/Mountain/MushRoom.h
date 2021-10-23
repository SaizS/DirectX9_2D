#pragma once

#define MUSHROOMMOVEDELAY 1.2
#define MUSHROOMATTACKDELAY 1

class MushRoom : public Enemy
{
private:
	enum State
	{
		RIGHTIDLE,
		LEFTIDLE,
		RIGHTJUMP,
		LEFTJUMP,
		RIGHTATTACK,
		LEFTATTACK
	}state;

	float moveDelay;
	float jumpAngle;
	float attackDelay;

	World* attackHitBox;
public:
	MushRoom();
	~MushRoom();

	virtual void EnemyActions() override;
	virtual void LoadActions() override;
	virtual void Idle() override;

	void SetActions(State state);
};