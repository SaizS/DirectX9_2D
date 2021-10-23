#pragma once

class Mage_BlackBall : public Enemy
{
private:
	function<void()> EndEvent;

	float durationTime;

public:
	Mage_BlackBall();
	~Mage_BlackBall();

	virtual void Update() override;
	virtual void Render() override;
	virtual void EnemyActions() override;
	virtual void Idle() override;
	virtual void LoadActions() override;

	void Shoot(Vector2 pos);

	void SetEvent(function<void()> Event) { EndEvent = Event; }
};