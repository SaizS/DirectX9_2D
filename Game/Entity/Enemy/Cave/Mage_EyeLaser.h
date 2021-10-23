#pragma once

class Mage_EyeLaser : public Info
{
private:
	vector<Animation*> actions;

	int state;
	float shootTime;
	bool isShoot;

	bool isActive;

	bool isRotaion;

	function<void()> LaserEndEvent;

	Player* player;

public:
	Mage_EyeLaser(World* world);
	~Mage_EyeLaser();

	virtual void Update() override;
	virtual void Render() override;

	void SetLaser(bool isRotation = false);
	void SetPlayer(Player* player) { this->player = player; }

	void ReadyShoot();
	void Shoot();

	void Load();

	void EndEvent(function<void()> EndEvent) { LaserEndEvent = EndEvent; }

	bool GetIsShoot() { return isShoot; }

	void LaserEnd() { isActive = false; isShoot = false; }
};