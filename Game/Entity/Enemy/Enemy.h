#pragma once

#define SPAWNDELAY 3

class Player;

class Enemy : public Info
{
protected:
	vector<Animation*> actions;

	vector<int> itemIndex;	// ��� ������ �ε��� ��ȣ

	Shader* shader;
	D3DXCOLOR color;

	Vector2 spawnStartPos;	// ���� ���� LeftTop
	Vector2 spawnEndPos;	// ���� ���� RightBottom
	float spawnDelay;

	bool isAttack;			// ���ݿ���
	bool isHit;				// ���� ���߽� true - �ǰݹ����� ����� isAttack True ����
	bool isActive;			// ��������
	bool isDie;

	float damageDistance;	// �з��� �Ÿ�
	float damageDistanceValue;
	float damagePower;		// �з��� �Ŀ�
	float damageAngle;		// �з��� ����
	bool isDamage;			// �������� �޾�����

	float damageTime;

	Player* player;			 // �� ��ü���� player�� �ּҰ��� �޾Ƽ� ���
	Animation* curAnimation; // Enemy���� �ڽ��� Animation�� �����ϱ� ���� ������

	BuffManager* buffManager;

	//HpBar
	Texture* hpBarTexture;
	World* hpWorld;
	Shader* hpShader;

public:	
	float maxHp;	// �ִ� ü��
	float hp;		// ü��
	float attack;	// ���ݷ�
	float def;		// ����
	float speed;	// �̵��ӵ�

	Enemy();		  // ���̴�, bool�� �� ���� �κ� ����
	virtual ~Enemy();

	//Override �Լ�
	virtual void EnemyActions() = 0; // Enemy ���� ����
	virtual void Idle() = 0;
	virtual void LoadActions() = 0;	

	//���� �Լ� ����
	virtual void Update();
	virtual void Render();
	virtual void DetectPlayer();
	virtual void EnemyCollision();
	virtual void Die(bool isBoss = false);
	virtual void Damage(int damage, float angle, BuffEffect::Buff_Type type = BuffEffect::Buff_Type::NONE);	
	virtual void KnockBack();
	virtual void Spawn();

	virtual void SetPlayer(Player* player) { this->player = player; }
	virtual void SetIsActive(bool value) { isActive = value; }	

	virtual bool GetIsActive() const { return isActive; }
	virtual float GetHp() const { return hp; }
};