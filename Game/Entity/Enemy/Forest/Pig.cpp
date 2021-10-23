#include "framework.h"

Pig::Pig() : rushDelayTime(0.0f), isRush(false), rushAngle(0.0f), rushDistance(0.0f), rushDestination({ 0,0 })
{
	LoadActions();

	maxHp = 20;
	hp = 20;
	attack = 20;
	def = 1;

	// µå¶ø ¾ÆÀÌÅÛ
	itemIndex.push_back(32); // Áü½ÂÀÇ »À
	itemIndex.push_back(33); // Áü½ÂÀÇ µÎ°³°ñ
	itemIndex.push_back(34); // Áü½ÂÀÇ ÇÇ
	itemIndex.push_back(35); // Áü½ÂÀÇ °¡Á×
	itemIndex.push_back(36); // Áü½ÂÀÇ °í±â

	speed = 180;

	spawnStartPos = { 945.0f, -397.0f };
	spawnEndPos = { 1650.0f, 1290.0f };

	damageDistance = 150;
	damageDistanceValue = damageDistance;
	damagePower = 7;
	damageAngle = 0.0f;
	isDamage = false;

	state = IDLE;
	actions[state]->Play();
	curAnimation = actions[state];

	pos =
	{ OP::Random(spawnStartPos.x, spawnEndPos.x),
	  OP::Random(spawnStartPos.y, spawnEndPos.y) };

	offset = { 0, 10 };
	SetCollider({ 30, 40 });  //Ãæµ¹¹üÀ§
	SetCircle(300.0f);

}

Pig::~Pig()
{
}

void Pig::LoadActions()
{
	vector<Texture*> clips;

	wstring filePath = L"Resource/Textures/Enemy/Forest/Pig.png";
	int width = 4;
	int height = 5;

	//IDLE
	for (int i = 0; i < 2; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 3, width, height));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	//LEFTMOVE
	for (int i = 0; i < width; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 2, width, height));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	//RIGHTMOVE
	for (int i = 0; i < width; i++)
		clips.push_back(TEXTURE->Add(filePath, i, 1, width, height));
	actions.push_back(new Animation(clips, Type::LOOP));

}

void Pig::Idle()
{
	SetActions(IDLE);
}

void Pig::SetActions(State state)
{
	if (this->state == state)
		return;
	
	this->state = state;
	actions[state]->Play();
	curAnimation = actions[state];
}

void Pig::EnemyActions()
{
	if (!isAttack)
		return;

	if (isDie)
	{
		isRush = false;
		rushDelayTime = 0.0f;
		rushDistance = 0.0f;
	}

	if (!isRush)
	{
		rushDelayTime += DELTA;

		if (rushDelayTime > RUSH_DELAY)
		{
			rushDelayTime = 0.0f;
			isRush = true;
			Vector2 pigToPlayer = player->pos - pos;
			rushAngle = OP::VecToAngle(OP::GetNomalize(pigToPlayer));
		}

		if (player->pos.x > pos.x)
			SetActions(RIGHTMOVE);
		else
			SetActions(LEFTMOVE);
	}
	else
	{
		pos.x += cos(rushAngle) * speed * DELTA;
		pos.y -= -sin(rushAngle) * speed * DELTA;

		rushDistance += DELTA;

		if (rushDistance > RUSH_DISTANCE || Collision(player->GetHitBox()))
		{
			isRush = false;
			rushDistance = 0.0f;
		}
	}
}
