#include "framework.h"

Flower::Flower() : attackDelay(0.0f)
{
	LoadActions();

	maxHp = 40.0f;
	hp = maxHp;
	attack = 10.0f;
	def = 2.0f;
	itemIndex.push_back(47);
	speed = 0.0f;

	spawnStartPos = { 85, 314 };
	spawnEndPos = { 750, 930 };

	damageDistance = 0.0f;
	damageDistanceValue = damageDistance;
	damagePower = 0.0f;
	damageAngle = 0.0f;
	isDamage = false;

	pos =
	{
		OP::Random(spawnStartPos.x, spawnEndPos.x),
		OP::Random(spawnStartPos.y, spawnEndPos.y)
	};

	state = IDLE;
	actions[state]->Play();
	curAnimation = actions[state];

	SetCollider({ 30,25 });
	SetRadius(600);
}

Flower::~Flower()
{
	for (Flower_Bullet* bullet : bullets)
		delete bullet;
}

void Flower::Update()
{
	Enemy::Update();

	for (Flower_Bullet* bullet : bullets)
		bullet->Update();
}

void Flower::Render()
{
	Enemy::Render();

	for (Flower_Bullet* bullet : bullets)
		bullet->Render();
}

void Flower::EnemyActions()
{
	BulletCollision();

	if (!isAttack)
		return;

	switch (state)
	{
	case Flower::IDLE:
		attackDelay += DELTA;
		if (attackDelay > FLOWER_ATTACK_DELAY)
		{
			attackDelay = 0.0f;
			SetActions(FIRE);
		}
		break;
	case Flower::FIRE:
		if (actions[state]->GetClipNum() == 2)
		{
			for (Flower_Bullet* bullet : bullets)
			{
				if (!bullet->GetIsActive() && !isFire)
				{
					Vector2 flowerToPlayer = player->pos - pos;
					bullet->Fire({ pos.x, pos.y - 5 }, OP::VecToAngle(OP::GetNomalize(flowerToPlayer)));
					isFire = true;
					return;
				}
			}
		}
		break;
	default:
		break;
	}
}

void Flower::LoadActions()
{
	vector<Texture*> clips;

	wstring filePath = L"Resource/Textures/Enemy/Mountain/Flower.png";
	int width = 6;
	int height = 1;

	clips.push_back(TEXTURE->Add(filePath, 0, 0, width, height));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 0; i < height; i++)
	{
		switch (i)
		{
		case 0:
			for (int j = 1; j < width; j++)
				clips.push_back(TEXTURE->Add(filePath, j, i, width, height));
			actions.push_back(new Animation(clips, Type::END));
			break;
		default:
			break;
		}		
	}		

	actions[FIRE]->SetEndEvent(bind(&Flower::Idle, this));

	for (int i = 0; i < FLOWER_BULLET_COUNT; i++)
		bullets.push_back(new Flower_Bullet());
}

void Flower::Idle()
{
	SetActions(IDLE);
	if (isFire)
		isFire = false;
}

void Flower::SetActions(State state)
{
	if (this->state == state)
		return;

	this->state = state;
	actions[state]->Play();
	curAnimation = actions[state];
}

void Flower::BulletCollision()
{
	for (Flower_Bullet* bullet : bullets)
	{
		if (bullet->GetIsActive())
		{
			if (bullet->Collision(player->GetHitBox()))
			{
				Vector2 bulletToPlayer = player->pos - bullet->pos;
				player->Damage(bullet->GetAttack(), OP::VecToAngle(OP::GetNomalize(bulletToPlayer)));
				bullet->SetIsActive(false);
				if (OP::Random(0, 1))
					player->SetBuff(13);
			}
			else if (bullet->pos.x < player->pos.x - WIN_HALFWIDTH || bullet->pos.x > player->pos.x + WIN_HALFWIDTH ||
				bullet->pos.y < player->pos.y - WIN_HALFHEIGHT || bullet->pos.y > player->pos.y + WIN_HALFHEIGHT)
				bullet->SetIsActive(false);
		}
	}
}