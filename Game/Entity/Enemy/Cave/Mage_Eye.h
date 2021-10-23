#pragma once

class Mage_Eye : public Enemy // ������ y�� 22 ��� �� 188
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

	//Attack 1 ( ���� ����)
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
	void RotationAttack();		// ���� ���ư��� �Լ�
	void LaserShoot();			// �Ϲ� �������� �߻� �ϴ� �Լ�
	void RotationLaser();		// �������� �߻��ϸ� ȸ���ϴ� �Լ�
	void RotaionLaserShoot();	// ȸ�������� �߻� �غ� �Լ�;
	void LaserCollision();
	
	void SetActions(Mage_EyeState state);
	void SetIsActive(bool value) { isActive = value; }
	

	void InTeleport();
	

	

	Mage_EyeLaser* GetLaser() { return laser; }
	bool GetIsRight() { return isRight; }
	
};