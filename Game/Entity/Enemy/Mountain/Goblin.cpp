#include "framework.h"

Goblin::Goblin()
{
	LoadActions();

	maxHp = 60.0f;
	hp = maxHp;
	attack = 20.0f;
	def = 3.0f;
	speed = 120.0f;

	itemIndex.push_back(42); // ±«¼öÀÇ »À
	itemIndex.push_back(43); // ±«¼öÀÇ µÎ°³°ñ
	itemIndex.push_back(44); // ±«¼öÀÇ ÇÇ
	itemIndex.push_back(45); // ±«¼öÀÇ °¡Á×

	spawnStartPos = { -1090.0f, -973.0f };
	spawnEndPos = { -115.0f, -458.0f };

	damageDistance = 100;
	damageDistanceValue = damageDistance;
	damagePower = 5;
	damageAngle = 0.0f;
	isDamage = false;

	pos =
	{ OP::Random(spawnStartPos.x, spawnEndPos.x),
	  OP::Random(spawnStartPos.y, spawnEndPos.y) };

	OP::Random(0, 2) == 0 ? state = RIGHTIDLE : state = LEFTIDLE;
	actions[state]->Play();
	curAnimation = actions[state];

	offset = { 0, 15 };
	SetCollider({ 30, 30 });	// Ãæµ¹ ¹üÀ§
	SetRadius(300);			// °¨Áö ¹üÀ§

	attackHitBox = new World();
	attackHitBox->pos = pos;
	attackHitBox->SetCollider({ 60, 30 });
}

Goblin::~Goblin()
{
	delete attackHitBox;
}

void Goblin::EnemyActions()
{
	attackHitBox->pos = pos;
	attackHitBox->Update();

	if (!isAttack)
		return;

	if (state == RIGHTATTACK || state == LEFTATTACK)
	{
		if (actions[state]->GetClipNum() == 1)
		{
			Vector2 goblinToPlayer = player->pos - pos;
			player->Damage(15, OP::VecToAngle(OP::GetNomalize(goblinToPlayer)));
			if (OP::Random(0, 4) == 0)
				player->SetBuff(29);
		}
	}
	else
	{
		if (attackHitBox->Collision(player->GetHitBox()))
		{
			if (player->pos.x > pos.x)
				SetActions(RIGHTATTACK);
			else
				SetActions(LEFTATTACK);
		}
		else
		{
			Vector2 goblinToPlayer;

			if (player->pos.x > pos.x)
			{
				SetActions(RIGHTWORK);
				goblinToPlayer = Vector2{ player->pos.x - 40, player->pos.y } -pos;
			}
			else
			{
				SetActions(LEFTWORK);
				goblinToPlayer = Vector2{ player->pos.x + 40, player->pos.y } -pos;
			}

			float angle = OP::VecToAngle(OP::GetNomalize(goblinToPlayer));

			pos.x += cos(angle) * speed * DELTA;
			pos.y -= -sin(angle) * speed * DELTA;
		}
	}
}

void Goblin::Idle()
{
	if (state == LEFTWORK || state == LEFTATTACK)
		SetActions(LEFTIDLE);
	else
		SetActions(RIGHTIDLE);
}

void Goblin::LoadActions()
{
	vector<Texture*> clips;

	wstring filePath = L"Resource/Textures/Enemy/Mountain/Goblin.png";

	clips.push_back(TEXTURE->Add(filePath, 0, 2, 6, 4));
	actions.push_back(new Animation(clips));
	clips.clear();

	clips.push_back(TEXTURE->Add(filePath, 0, 3, 6, 4));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 0; i < 6; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 1, 6, 4));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	for (int i = 0; i < 6; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 0, 6, 4));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	for (int i = 1; i < 5; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 2, 6, 4));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 1; i < 5; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 3, 6, 4));
	actions.push_back(new Animation(clips));
	clips.clear();

	actions[LEFTATTACK]->SetEndEvent(bind(&Goblin::Idle, this));
	actions[RIGHTATTACK]->SetEndEvent(bind(&Goblin::Idle, this));
}

void Goblin::SetActions(State state)
{
	if (this->state == state)
		return;

	this->state = state;
	actions[state]->Play();
	curAnimation = actions[state];
}
