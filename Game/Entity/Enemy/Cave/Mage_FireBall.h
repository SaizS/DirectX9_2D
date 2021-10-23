#pragma once

class Mage_FireBall : public Enemy
{
public:
	enum Mage_FireBallState
	{
		SHOOT,
		CRASH
	};
private:
	Mage_FireBallState state;

public:
	Mage_FireBall();
	~Mage_FireBall();

	virtual void Update() override;
	virtual void Render() override;
	virtual void EnemyActions() override;
	virtual void Idle() override;
	virtual void LoadActions() override;

	void SetActions(Mage_FireBallState state);

	void Shoot(Vector2 pos, float angle);
	void FireBallCrash();

	void IsAciveFalse() { isActive = false; }

	Mage_FireBallState GetState() { return state; }
	bool GetIsActive() { return isActive; }
};