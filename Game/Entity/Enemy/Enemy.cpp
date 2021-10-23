#include "framework.h"
#include "Enemy.h"

Enemy::Enemy()
{
	shader = Shader::Add(L"Shader/Object.hlsl");
	color = D3DXCOLOR(1, 1, 1, 1);
	speed = 150.0f;

	damageTime = 0.0f;

	spawnDelay = 0.0f;

	isAttack = false;
	isHit = false;
	isActive = true;
	isDie = false;

	hpBarTexture = TEXTURE->Add(L"Resource/Textures/UI/hp.png");
	hpShader = Shader::Add(L"Shader/EnemyHpBar.hlsl");

	hpWorld = new World();
	hpWorld->pos = { 0, -30 };
	hpWorld->SetParent(&world);

	buffManager = new BuffManager(this);
	buffManager->SetParent(&world);
	buffManager->SetOffset(0, -50);
}

Enemy::~Enemy()
{
	for (Animation* ani : actions)
		delete ani;
	delete hpWorld;
	delete buffManager;
}

void Enemy::Update()
{
	if (!isActive)
		return;

	if (hp > maxHp)
		hp = maxHp;

	if (vertices[0].color != BLUE)
		SetColor(BLUE);

	if (!isDie && !buffManager->BuffCheck(20))
	{
		EnemyActions();		// Enemy 행동 패턴 Override 사용
		curAnimation->Update();
	}

	EnemyCollision();	// Enemy 충돌처리
	DetectPlayer();		// Enemy Player 감지
	KnockBack();		// 데미지를 받았을 때 넉백

	Die();				// Enemy가 Hp가 0이하가 되었을때

	hpWorld->Update();
	World::Update();

	buffManager->Update();
}

void Enemy::Render()
{
	if (!isActive)
		return;

	SetWorld();

	shader->SetTexture("map", curAnimation->GetTexture());
	shader->SetVector("color", &color, 4);
	shader->Begin();
	curAnimation->Render();
	shader->End();

	buffManager->Render();

	hpWorld->SetWorld();
	hpShader->SetFloat("value", hp / maxHp);
	hpShader->SetTexture("map", hpBarTexture->GetTexture());
	hpShader->Begin();
	hpBarTexture->Render();
	hpShader->End();
}

void Enemy::DetectPlayer()
{
	if (player == NULL)
		return;

	if (!isAttack)
	{
		if(CollisionCircle(player))
			isAttack = true;
		Idle();
	}

	if (isAttack && !isHit)
	{
		if (!CollisionCircle(player))
		{
			isAttack = false;
		}
	}

	if (isHit)
	{
		Vector2 vec = player->pos - pos;
		vec = OP::GetNomalize(vec);
		float distance = OP::Distance(player->pos, pos);
		vec.x *= distance;
		vec.y *= distance;
		if (abs(vec.x) > WIN_HALFWIDTH || abs(vec.y) > WIN_HALFHEIGHT)
			isHit = false;
	}
}

void Enemy::EnemyCollision()
{
	if (player->GetIsDie() || isDie || !isActive)
		return;

	if (Collision(player->GetHitBox()))
	{
		Vector2 vec = player->pos - pos;
		player->Damage(attack, OP::VecToAngle(OP::GetNomalize(vec)));
	}
	for (Potion* portion : player->GetPortions())
	{
		if (portion->GetIsActive())
		{
			if (portion->Collision(this))
			{
				if (!isHit)
					isHit = true;
				if (!isAttack)
					isAttack = true;

				EFFECT->Play("Hit", portion->pos);
				Vector2 vec = pos - portion->pos;
				buffManager->SetBuff(portion->GetEffect());
				Damage(player->atk, OP::VecToAngle(OP::GetNomalize(vec)), (BUFFTYPE)portion->GetEffect());
				portion->Crash();
			}
		}
	}
}

void Enemy::Die(bool isBoss)
{
	if (hp <= 0 && !isDie)
	{
		if (!isBoss)
		{
			int randNum = OP::Random(0, 9);

			if (randNum <= 8)
			{
				int getItemNumber = OP::Random(0, itemIndex.size());
				if (getItemNumber == itemIndex.size())
					getItemNumber--;
				GUI->GetInven()->GetItem(itemIndex[getItemNumber]);
				if (randNum <= 3) {
					int getItemNumber = OP::Random(0, itemIndex.size());
					if (getItemNumber == itemIndex.size())
						getItemNumber--;
					GUI->GetInven()->GetItem(itemIndex[getItemNumber]);
				}
			}
		}
		else
		{
			for (int i = 0; i < 10; i++)
				GUI->GetInven()->GetItem(itemIndex[OP::Random(0, itemIndex.size() - 1)]);
		}
		isDie = true;
		isAttack = false;
		buffManager->ClearBuff();

		SOUND->Play("MageDie");

		if(curAnimation != NULL)
			curAnimation->Stop();
	}

	if (isDie)
	{
		color.a -= DELTA;

		if (color.a <= 0.0f)
		{
			isActive = false;
			isDie = false;
			color.a = 1.0f;
		}
	}
}

void Enemy::Damage(int damage, float angle, BuffEffect::Buff_Type type)
{
	if (type == BuffEffect::SHOCKWAVE) // 충격 플라스크 -> 밀려나는 거리 2배
	{
		if (def < damage)
			hp -= damage - def;
		else
			hp - 1;
		this->damageAngle = angle;
		isDamage = true;
		this->damageDistanceValue *= 2;
		color = D3DXCOLOR(1, 0, 0, 1);
	}
	else
	{
		if (buffManager->BuffCheck(17)) // 감전일때 추가 뎀지
		{
			if (def < damage)
				hp -= damage - def;
			else
				hp -= 1;
			hp -= 3;
		}
		else
		{
			if (def < damage)
				hp -= damage - def;
			else
				hp -= 1;
		}

		this->damageAngle = angle;
		isDamage = true;
		color = D3DXCOLOR(1, 0, 0, 1);
	}
}

void Enemy::KnockBack()
{
	if (!isDamage)
		return;
	
	if(damageDistance == 0.0f)
	{
		damageTime += DELTA;

		if (damageTime >= 0.1f)
		{
			isDamage = false;
			damageTime = 0.0f;
			color = D3DXCOLOR(1, 1, 1, 1);
		}
	}
	else
	{
		damageDistanceValue -= damagePower;

		if (damageDistanceValue < damageDistance - 20 && !isDie)
			color = D3DXCOLOR(1, 1, 1, 1);


		if (damageDistanceValue <= 0)
		{
			isDamage = false;
			damageDistanceValue = damageDistance;
		}

		pos.x += cos(damageAngle) * damageDistanceValue * DELTA;
		pos.y += sin(damageAngle) * damageDistanceValue * DELTA;
	}
}

void Enemy::Spawn()
{
	isAttack = false;
	isHit = false;
	isActive = true;
	isDie = false;
	spawnDelay = 0;

	float posX = OP::Random(spawnStartPos.x, spawnEndPos.x);
	float posY = OP::Random(spawnStartPos.y, spawnEndPos.y);
	Idle();

	pos = { posX, posY };

	hp = maxHp;
}