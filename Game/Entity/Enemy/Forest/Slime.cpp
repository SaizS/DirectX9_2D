#include "framework.h"
#include "Slime.h"

Slime::Slime() : jumpDelay(0.0f), jumpAngle(0.0f)
{
	LoadActions();

	//상속 변수 정의
	maxHp = 30.0f;
	hp = maxHp;
	attack = 15.0f;
	def = 3.0f;
	itemIndex.push_back(46);
	speed = 200;

	spawnStartPos = { -630.0f, -375.0f };
	spawnEndPos = { 90.0f, 1450.0f };

	damageDistance = 200;
	damageDistanceValue = damageDistance;
	damagePower = 5;
	damageAngle = 0.0f;	
	isDamage = false;

	//Slime 변수 및 월드 정의
	pos = 
	{ OP::Random(spawnStartPos.x, spawnEndPos.x), 
	  OP::Random(spawnStartPos.y, spawnEndPos.y) };

	state = IDLE;
	actions[state]->Play();
	curAnimation = actions[state];

	offset = { 0, 15 };
	SetCollider({30, 30});	// 충돌 범위
	SetRadius(300);			// 감지 범위
}

Slime::~Slime()
{
}

void Slime::LoadActions()
{
	vector<Texture*> blueSlimeClips;
	vector<Texture*> purpleSlimeClips;

	wstring blueSlimePath = L"Resource/Textures/Enemy/Forest/Blue_Slime.png";
	wstring purpleSlimePath = L"Resource/Textures/Enemy/Forest/Purple_Slime.png";

	for (int i = 0; i < 2; i++)
	{
		switch (i)
		{
		case 0:
			for (int j = 0; j < 4; j++)
			{
				blueSlimeClips.push_back(TEXTURE->Add(blueSlimePath, j, i, 5, 2));
				purpleSlimeClips.push_back(TEXTURE->Add(purpleSlimePath, j, i, 5, 2));
			}
			blueSlime.push_back(new Animation(blueSlimeClips, Type::LOOP));
			purpleSlime.push_back(new Animation(purpleSlimeClips, Type::LOOP));

			blueSlimeClips.clear();
			purpleSlimeClips.clear();
			break;
		case 1:
			for (int j = 0; j < 5; j++)
			{
				blueSlimeClips.push_back(TEXTURE->Add(blueSlimePath, j, i, 5, 2));
				purpleSlimeClips.push_back(TEXTURE->Add(purpleSlimePath, j, i, 5, 2));
			}
			blueSlime.push_back(new Animation(blueSlimeClips, Type::END));
			purpleSlime.push_back(new Animation(purpleSlimeClips, Type::END));

			blueSlimeClips.clear();
			purpleSlimeClips.clear();
			break;
		default:
			break;
		}
	}

	blueSlime[JUMP]->SetEndEvent(bind(&Slime::Idle, this));
	purpleSlime[JUMP]->SetEndEvent(bind(&Slime::Idle, this));

	OP::Random(0, 2) ? actions = purpleSlime : actions = blueSlime;
}

void Slime::Idle()
{
	SetActions(IDLE);
}

void Slime::SetActions(State state)
{
	if (this->state == state)
		return;

	this->state = state;
	actions[state]->Play();
	curAnimation = actions[state];
}

void Slime::EnemyActions()
{
	if (isDamage || isDie || !isAttack)
		return;

	if (Collision(player->GetHitBox()))
	{
		if (OP::Random(0, 1))
			player->SetBuff(26);
	}

	switch (state)
	{
	case Slime::IDLE:
		jumpDelay += DELTATIME * 2;

		if (jumpDelay >= SLIME_JUMP_DELAY)
		{
			jumpDelay = 0.0f;
			SetActions(JUMP);

			Vector2 vec = player->pos - pos;
			jumpAngle = OP::VecToAngle(OP::GetNomalize(vec));
		}
		break;
	case Slime::JUMP:
		pos.x += cos(jumpAngle) * speed * DELTA;
		pos.y += sin(jumpAngle) * speed * DELTA;
		break;
	default:
		break;
	}
}
