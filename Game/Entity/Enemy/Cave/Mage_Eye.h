#pragma once

class Mage_Eye : public Enemy // 레이저 y값 22 상속 쏠때 188
{
public:
	enum Mage_EyeState
	{
		IDLE,
		INTELEPORT,
		OUTTELEPORT
	};

private:
	Mage_EyeState state;

	Vector2* magePos;

	Vector2 basicPos;
	float basicDistance;
	float basicAngle;

	bool isRight;

	float rotDistance;
	float rotAngle;
	
	bool isActive;
	bool isTeleport;
	float teleportDelay;

	//Attack 1 ( 주위 돌기)
	bool isRotationAttack;
	bool isPattern1;
	float rotationAttackTime;

	bool isRotationLaser;

	Mage_EyeLaser* laser;

	function<void()> AttackEndEvent;

public:
	Mage_Eye(Vector2 pos, World* world, function<void()> AttackEndEvent);
	~Mage_Eye();

	virtual void Update() override;
	virtual void Render() override;
	virtual void EnemyActions() override;
	virtual void Idle() override;
	virtual void LoadActions() override;

	void SetPlayer(Player* player) { this->player = player; laser->SetPlayer(player); }

	void SetTeleport();

	void Teleport();
	void SetRotationAttack();
	void RotationAttack();		// 눈이 돌아가는 함수
	void LaserShoot();			// 일반 레이저를 발사 하는 함수
	void RotationLaser();		// 레이저를 발사하며 회전하는 함수
	void RotaionLaserShoot();	// 회전레이저 발사 준비 함수;
	void LaserCollision();
	
	void SetActions(Mage_EyeState state);
	void SetIsActive(bool value) { isActive = value; }
	

	void InTeleport();
	

	

	Mage_EyeLaser* GetLaser() { return laser; }
	bool GetIsRight() { return isRight; }
	
};