#include "framework.h"

MushRoom::MushRoom() : attackDelay(0.0f), jumpAngle(0.0f), moveDelay(0.0f)
{
	LoadActions();

	//»ó¼Ó º¯¼ö Á¤ÀÇ
	maxHp = 50;
	hp = maxHp;
	attack = 25;
	def = 2;
	speed = 250;

	itemIndex.push_back(42); // ±«¼öÀÇ »À
	itemIndex.push_back(43); // ±«¼öÀÇ µÎ°³°ñ
	itemIndex.push_back(44); // ±«¼öÀÇ ÇÇ
	itemIndex.push_back(45); // ±«¼öÀÇ °¡Á×
	
	spawnStartPos = { -1136.0f, 394.0f };
	spawnEndPos = { -606.0f, 1100.0f };

	damageDistance = 150;
	damageDistanceValue = damageDistance;
	damagePower = 5;
	damageAngle = 0.0f;
	isDamage = false;
	Vector2 randPos;

	pos =
	{
		OP::Random(spawnStartPos.x, spawnEndPos.x),
		OP::Random(spawnStartPos.y, spawnEndPos.y)
	};

	OP::Random(0, 2) == 0 ? state = RIGHTIDLE : state = LEFTIDLE;
	actions[state]->Play();
	curAnimation = actions[state];

	SetCollider({ 30, 55 });
	SetCircle(300.0f);
	SetColor(BLUE);

	attackHitBox = new World();
	//attackHitBox->pos = pos;	
	//attackHitBox->offset = { 0, 30 };
	attackHitBox->SetParent(&world);
	attackHitBox->SetCollider({ 120, 120 });
}

MushRoom::~MushRoom()
{
	delete attackHitBox;
}

void MushRoom::EnemyActions()
{
	attackHitBox->pos = pos;
	attackHitBox->Update();

	if (!isAttack)
		return;

	switch (state)
	{
	case MushRoom::RIGHTIDLE:
	case MushRoom::LEFTIDLE:
	{
		if (player->pos.x > pos.x)
			SetActions(RIGHTIDLE);
		else
			SetActions(LEFTIDLE);

		if (speed == 0)
			speed = 230;

		if (attackHitBox->Collision(player->GetHitBox()))
		{
			attackDelay += DELTA;

			if (attackDelay > MUSHROOMATTACKDELAY)
			{
				attackDelay = 0.0f;

				if (state == RIGHTIDLE)
					SetActions(RIGHTATTACK);
				else
					SetActions(LEFTATTACK);
			}
		}
		else
		{
			moveDelay += DELTA;

			if (moveDelay > MUSHROOMMOVEDELAY)
			{
				moveDelay = 0.0f;
				Vector2 mushToPlayer = player->pos - pos;
				jumpAngle = OP::VecToAngle(OP::GetNomalize(mushToPlayer));

				if (state == RIGHTIDLE)
					SetActions(RIGHTJUMP);
				else
					SetActions(LEFTJUMP);
			}
		}
	}
		break;
	case MushRoom::RIGHTJUMP:
	case MushRoom::LEFTJUMP:
	{
		pos.x += cos(jumpAngle) * speed * DELTA;
		pos.y += sin(jumpAngle) * speed * DELTA;
		if (attackHitBox->Collision(player->GetHitBox()))
			speed = 0;
	}
	break;
	case MushRoom::RIGHTATTACK:
	case MushRoom::LEFTATTACK:
		if (actions[state]->GetClipNum() == 4)
		{
			Vector2 leftPos = { pos.x - 70, pos.y + 10 };
			Vector2 downPos = { pos.x - 10, pos.y + 55 };
			Vector2 rightPos = { pos.x + 50, pos.y + 10 };
			Vector2 upPos = { pos.x - 10, pos.y - 55 };
			EFFECT->Play("Poison", leftPos);
			EFFECT->Play("Poison", downPos);
			EFFECT->Play("Poison", rightPos);
			EFFECT->Play("Poison", upPos);

			if (attackHitBox->Collision(player->GetHitBox()))
			{
				player->Damage(5, OP::VecToAngle(OP::GetNomalize(player->pos - pos)));
				player->SetBuff(14);
			}
		}
		break;
	default:
		break;
	}
}

void MushRoom::LoadActions()
{
	vector<Texture*> clips;

	//ºÒ·¯¿Ã ÆÄÀÏ Á¤º¸
	wstring filePath = L"Resource/Textures/Enemy/Mountain/MushRoom.png";
	int width = 5;
	int height = 6;

	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			for (int j = 0; j < 4; j++)
				clips.push_back(TEXTURE->Add(filePath, j, i, width, height));
			actions.push_back(new Animation(clips, Type::LOOP));
			clips.clear();
			break;
		case 1:
			for (int j = 0; j < 4; j++)
				clips.push_back(TEXTURE->Add(filePath, j, i, width, height));
			actions.push_back(new Animation(clips, Type::LOOP));
			clips.clear();
			break;
		case 2:
			for (int j = 0; j < 4; j++)
				clips.push_back(TEXTURE->Add(filePath, j, i, width, height));
			actions.push_back(new Animation(clips, Type::END));
			clips.clear();
			break;
		case 3:
			for (int j = 0; j < 4; j++)
				clips.push_back(TEXTURE->Add(filePath, j, i, width, height));
			actions.push_back(new Animation(clips, Type::END));
			clips.clear();
			break;
		case 4:
			for (int j = 0; j < 5; j++)
				clips.push_back(TEXTURE->Add(filePath, j, i, width, height));
			actions.push_back(new Animation(clips, Type::END));
			clips.clear();
			break;
		case 5:
			for (int j = 0; j < 5; j++)
				clips.push_back(TEXTURE->Add(filePath, j, i, width, height));
			actions.push_back(new Animation(clips, Type::END));
			clips.clear();
			break;
		default:
			break;
		}
	}

	actions[RIGHTJUMP]->SetEndEvent(bind(&MushRoom::Idle, this));
	actions[LEFTJUMP]->SetEndEvent(bind(&MushRoom::Idle, this));
	actions[RIGHTATTACK]->SetEndEvent(bind(&MushRoom::Idle, this));
	actions[LEFTATTACK]->SetEndEvent(bind(&MushRoom::Idle, this));

}

void MushRoom::Idle()
{
	if (state == RIGHTJUMP || state == RIGHTATTACK)
		SetActions(RIGHTIDLE);
	else
		SetActions(LEFTIDLE);
}

void MushRoom::SetActions(State state)
{
	if (this->state == state)
		return;

	this->state = state;
	actions[state]->Play();
	curAnimation = actions[state];
}
