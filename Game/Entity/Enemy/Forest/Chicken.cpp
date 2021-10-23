#include "framework.h"

Chicken::Chicken() : isWave(true), waveValue(0.0f), waveDistance(0.0f)
{
	LoadActions();

	//상속 변수 정의
	maxHp = 15;
	hp = 15;
	attack = 10;
	def = 0;

	// 드랍 아이템
	itemIndex.push_back(33); // 짐승의 두개골
	itemIndex.push_back(34); // 짐승의 피
	itemIndex.push_back(38); // 달걀

	speed = 80;

	spawnStartPos = { 945.0f, -397.0f };
	spawnEndPos = { 1650.0f, 1290.0f };

	damageDistance = 200;
	damageDistanceValue = damageDistance;
	damagePower = 7;
	damageAngle = 0.0f;
	isDamage = false;	

	//BlackChicken 변수 및 월드 정의
	OP::Random(0, 2) == 0 ? RIGHTIDLE : LEFTIDLE;
	actions[state]->Play();
	curAnimation = actions[state];

	pos =
	{ OP::Random(spawnStartPos.x, spawnEndPos.x), 
	  OP::Random(spawnStartPos.y, spawnEndPos.y) };

	SetCollider({ 30, 30 });  //충돌범위
	SetCircle(300.0f);		  //감지범위
}

Chicken::~Chicken()
{
}

void Chicken::EnemyActions()
{
	if (!isAttack || isDie)
		return;

	if (state == RIGHTIDLE || state == LEFTIDLE)
	{
		SetActions(RIGHTMOVE);
	}

	Vector2 vec = player->pos - pos;

	float angle = atan2(OP::GetNomalize(vec).y, OP::GetNomalize(vec).x);

	if (state == RIGHTMOVE || state == LEFTMOVE)
	{
		if (player->pos.x > pos.x)
			SetActions(RIGHTMOVE);
		else
			SetActions(LEFTMOVE);
	}

	if (!isDamage)
	{
		if (isWave)
		{
			if (waveDistance < 0)
			{
				waveValue -= DELTA * 2;
				if (waveValue < -(PI * 0.25f))
					isWave = false;
			}
			else
			{
				waveValue += DELTA * 2;
				if (waveValue > PI * 0.25f)
					isWave = false;
			}

		}
		else
		{
			if (waveValue < 0)
			{
				waveDistance += 1;
				if (waveDistance >= 30)
					isWave = true;
			}
			else
			{
				waveDistance -= 1;
				if (waveDistance <= -30)
					isWave = true;
			}
		}

		angle += waveValue;
		pos.x += cos(angle) * speed * DELTA;
		pos.y -= -sin(angle) * speed * DELTA;
	}
}


void Chicken::LoadActions()
{
	/*
	LEFTIDLE,
	RIGHTIDLE,
	LEFTMOVE,
	RIGHTMOVE,
	UPMOVE
		*/
	vector<Texture*> clips;

	wstring fileName = L"Resource/Textures/Enemy/Forest/Black_Chicken.png";

	//LEFTIDLE
	for (int i = 0; i < 2; i++)
		clips.push_back(TEXTURE->Add(fileName, i, 4, 4, 7));
	actions.push_back(new Animation(clips, Type::LOOP, 0.3f));
	clips.clear();

	//RIGHTIDLE
	for (int i = 0; i < 2; i++)
		clips.push_back(TEXTURE->Add(fileName, i+2, 4, 4, 7));
	actions.push_back(new Animation(clips, Type::LOOP, 0.3f));
	clips.clear();

	//LEFTMOVE
	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(fileName, i, 3, 4, 7));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	//RIGHTMOVE
	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(fileName, i, 1, 4, 7));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();

	//UPMOVE
	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(fileName, i, 2, 4, 7));
	actions.push_back(new Animation(clips, Type::LOOP));
	clips.clear();
}

void Chicken::Idle()
{
	if(state != LEFTIDLE && state != RIGHTIDLE)
	OP::Random(0, 2) ? SetActions(LEFTIDLE) : SetActions(RIGHTIDLE);
}

void Chicken::SetActions(State state)
{
	if (this->state == state)
		return;

	this->state = state;
	actions[state]->Play();
	curAnimation = actions[state];
}