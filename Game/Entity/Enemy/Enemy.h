#pragma once

#define SPAWNDELAY 3

class Player;

class Enemy : public Info
{
protected:
	vector<Animation*> actions;

	vector<int> itemIndex;	// 드랍 아이템 인덱스 번호

	Shader* shader;
	D3DXCOLOR color;

	Vector2 spawnStartPos;	// 스폰 범위 LeftTop
	Vector2 spawnEndPos;	// 스폰 범위 RightBottom
	float spawnDelay;

	bool isAttack;			// 공격여부
	bool isHit;				// 공격 적중시 true - 피격범위를 벗어나도 isAttack True 유지
	bool isActive;			// 스폰여부
	bool isDie;

	float damageDistance;	// 밀려날 거리
	float damageDistanceValue;
	float damagePower;		// 밀려날 파워
	float damageAngle;		// 밀려날 각도
	bool isDamage;			// 데미지를 받았을때

	float damageTime;

	Player* player;			 // 각 개체에서 player의 주소값을 받아서 사용
	Animation* curAnimation; // Enemy에서 자식의 Animation을 제어하기 위한 포인터

	BuffManager* buffManager;

	//HpBar
	Texture* hpBarTexture;
	World* hpWorld;
	Shader* hpShader;

public:	
	float maxHp;	// 최대 체력
	float hp;		// 체력
	float attack;	// 공격력
	float def;		// 방어력
	float speed;	// 이동속도

	Enemy();		  // 쉐이더, bool값 등 공통 부분 정의
	virtual ~Enemy();

	//Override 함수
	virtual void EnemyActions() = 0; // Enemy 패턴 정의
	virtual void Idle() = 0;
	virtual void LoadActions() = 0;	

	//공통 함수 정의
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