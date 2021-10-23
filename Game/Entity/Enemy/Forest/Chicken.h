#pragma once

class Chicken : public Enemy
{
public:
	enum State
	{
		LEFTIDLE,
		RIGHTIDLE,
		LEFTMOVE,
		RIGHTMOVE,
		UPMOVE
	};

private:
	State state;

	float waveValue;
	bool isWave;
	float waveDistance;

public: 
	Chicken();
	~Chicken();
	
	virtual void EnemyActions() override;
	virtual void LoadActions() override;
	virtual void Idle() override;

	void SetActions(State state);
};