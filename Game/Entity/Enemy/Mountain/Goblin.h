#pragma once

class Goblin : public Enemy
{
public:
	enum State
	{
		LEFTIDLE,
		RIGHTIDLE,
		LEFTWORK,
		RIGHTWORK,
		LEFTATTACK,
		RIGHTATTACK
	};
private:
	State state;

	World* attackHitBox;
public:
	Goblin();
	~Goblin();

	virtual void EnemyActions() override;
	virtual void Idle() override;
	virtual void LoadActions() override;

	void SetActions(State state);
};