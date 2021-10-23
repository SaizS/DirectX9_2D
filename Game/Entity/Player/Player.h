#pragma once

#define POTION_COUNT 30
#define COLLECT_TIME 3

class Paticle;

class Player : public Info
{
public:
	enum State
	{
		UPIDLE,
		DOWNIDLE,
		LEFTIDLE,
		RIGHTIDLE,
		UPRUN,
		DOWNRUN,
		LEFTRUN,
		RIGHTRUN,
		UPATTACK,
		DOWNATTACK,
		LEFTATTACK,
		RIGHTATTACK,
		UPDIE,
		DOWNDIE,
		LEFTDIE,
		RIGHTDIE,
		COLLECT,
		COLLECTING
	};
private:
	State state;

	vector<Animation*> actions;
	Shader* shader;
	D3DXCOLOR color;

	Vector4 standardAngle; // �ޱ� ������

	bool isDie;

	World* hitBox;

	vector<Object*> objects;

	bool isAttack;

	bool isDamage;
	float damageDistance; // �˹� �Ÿ�
	float damageAngle; // �˹� ����
	
	float collectTime; // ���� �ð�

	vector<Potion*> portions;

	Paticle* curPaticle;

	BuffManager* bm;
	//vector<BuffEffect*> buffFXs; //������

	bool isCollect;
public:
	float maxHp;
	float hp;
	float atk;
	float def;
	float speed;

	Player();
	~Player();

	void Update() override;
	void Render() override;

	void Move();
	void Attack();
	void Die();

	void Damage(int damage, float angle);
	void KnockBack();

	void SetActions(State dir);

	void LoadActions();

	void UpIdle() { SetActions(UPIDLE); }
	void DownIdle() { SetActions(DOWNIDLE); }
	void LeftIdle() { SetActions(LEFTIDLE); }
	void RightIdle() { SetActions(RIGHTIDLE); }

	void SetObject(vector<Object*> object) { objects = object; }

	World* GetHitBox() { return hitBox; }
	bool GetIsDie() { return isDie; }

	vector<Potion*> GetPortions() { return portions; }

	void SetPortion();
	void SetPaticle(Paticle* paticle) { curPaticle = paticle; }
	void SetBuff(int key) { bm->SetBuff(key); }

	void CollectPaticle();

	void SetIsAttack(bool value) { isAttack = value; }
	void SetFade();

	void Spawn();

	State GetState() { return state; }
};