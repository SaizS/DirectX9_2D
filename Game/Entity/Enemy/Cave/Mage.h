#pragma once

#define FIREBALLCOUNT 5
#define MAGE_ATTACK_DELAY 3

class Mage : public Enemy
{
public:
	enum MageState
	{
		TRANSFORM,
		IDLE,
		LEFTMOVE,
		RIGHTMOVE,
		INTELEPORT,
		OUTTELEPORT,
		ATTACKREADY,
		ATTACK
	};

	enum MageAttackPattern
	{
		EYE_ROTATION,
		EYE_ROTATIONLASER,
		EYE_LASERLEFTMOVE,
		EYE_LASERRIGHTMOVE,
		MAGE_FIREBALL,
		MAGE_8DIR_FIREBALL,
		MAGE_BLACKBALL,
		NONE
	};
private:
	MageState state;
	MageAttackPattern attackPattern;

	vector<Mage_Eye*> eyes;

	Mage_Emote* emote;

	float attackDelay;

	vector<Mage_FireBall*> fireBalls;
	float fireBallAttackDelay;
	int fireBallAttackCount;

	float multiFireBallTime;

	Mage_BlackBall* blackBall;

	float mageMaxHp;

	World* attackBox;
	World* evadeBox;

	bool isTeleport;
	float teleportTime;

	bool isEmote;
public:
	Mage();
	~Mage();

	virtual void Update() override;
	virtual void Render() override;
	virtual void EnemyActions() override;
	virtual void Idle() override;

	void Attack();

	void SetActions(MageState state);

	void OnEye();

	virtual void LoadActions() override;	

	void SetPlayer(Player* player);

	void AttackPatternEnd();

	void TeleportEvent();
	void InTeleportEndEvent();
	void OutTeleportEndEvent();

	vector<Mage_FireBall*> GetFireBall() { return fireBalls; }

	void TransForm();

	void ReSet();

	void SetUI();
};