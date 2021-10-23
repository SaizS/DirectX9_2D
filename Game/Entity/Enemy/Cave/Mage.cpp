#include "framework.h"

Mage::Mage() : multiFireBallTime(0.0f), isEmote(false)
{
	LoadActions();
	pos = { 0, -300 };
	SetCollider({ 60, 150 });
	SetCircle(250);

	state = TRANSFORM;
	curAnimation = actions[state];

	itemIndex.push_back(11);
	itemIndex.push_back(20);
	itemIndex.push_back(21);
	itemIndex.push_back(23);
	itemIndex.push_back(24);
	itemIndex.push_back(25);
	itemIndex.push_back(26);
	itemIndex.push_back(27);
	itemIndex.push_back(28);
	itemIndex.push_back(29);

	damageDistance = 0.0f;

	attack = 20.0f;
	def = 10.0f;

	attackPattern = NONE;

	eyes.push_back(new Mage_Eye({ -85, -68 }, this, bind(&Mage::AttackPatternEnd, this)));
	eyes.push_back(new Mage_Eye({ 85, -68 }, this, bind(&Mage::AttackPatternEnd, this)));

	for (int i = 0; i < 20; i++)
		fireBalls.push_back(new Mage_FireBall());

	fireBallAttackDelay = 0;
	fireBallAttackCount = 0;

	maxHp = 100;
	mageMaxHp = 1000;
	hp = mageMaxHp;

	blackBall = new Mage_BlackBall();
	blackBall->SetEvent(bind(&Mage::AttackPatternEnd, this));

	isActive = true;
	buffManager->SetOffset(0, -120);

	emote = new Mage_Emote(bind(&Mage::TransForm, this));
}

Mage::~Mage()
{
	for (Mage_Eye* eye : eyes)
		delete eye;

	for (Mage_FireBall* ball : fireBalls)
		delete ball;

	delete blackBall;
	delete emote;
}

void Mage::Update()
{
	if (!isActive)
		return;

	if (CollisionCircleRect(player->GetHitBox()) && !isEmote)
	{
		isEmote = true;
		emote->Play();
	}

	emote->Update();

	if (KEYDOWN('H'))
		actions[state]->Play();
	if (KEYDOWN(VK_SPACE))
		ReSet();

	Die(true);

	if(state != TRANSFORM)
		Enemy::EnemyCollision();
	Enemy::KnockBack();

	TeleportEvent();
	EnemyActions();

	actions[state]->Update();

	World::Update();
	
	for (Mage_Eye* eye : eyes)
		eye->Update();

	for (Mage_FireBall* fireBall : fireBalls)
	{
		fireBall->Update();
	}

	blackBall->Update();

	buffManager->Update();
}

void Mage::Render()
{
	if (!isActive)
		return;

	SetWorld();

	shader->SetTexture("map", actions[state]->GetTexture());
	shader->SetVector("color", &color, 4);
	shader->Begin();
	actions[state]->Render();
	shader->End();

	for (Mage_Eye* eye : eyes)
		eye->Render();

	for (Mage_FireBall* fireBall : fireBalls)
		fireBall->Render();

	buffManager->Render();

	blackBall->Render();

	emote->Render();
}

void Mage::Idle()
{
	if (state == TRANSFORM)
	{
		GUI->GetBossHpBar()->isActive = true;
		OnEye();
	}

	SetActions(IDLE);
}

void Mage::Attack()
{
	SetActions(ATTACK);
}

void Mage::SetActions(MageState state)
{
	if (this->state == state)
		return;

	if ((attackPattern == EYE_LASERLEFTMOVE || attackPattern == EYE_LASERRIGHTMOVE) && state == ATTACKREADY)
	{
		eyes[0]->LaserShoot();
		eyes[1]->LaserShoot();
	}

	if ((attackPattern == EYE_ROTATIONLASER && state == ATTACKREADY))
	{
		eyes[0]->RotaionLaserShoot();
		eyes[1]->RotaionLaserShoot();
	}

	if (attackPattern == MAGE_BLACKBALL && state == ATTACK)
	{
		blackBall->Shoot(pos);
		SOUND->Play("BlackBallShoot");
	}

	if (state == INTELEPORT)
		SOUND->Play("MageTeleport");

	this->state = state;
	actions[state]->Play();
	curAnimation = actions[state];
}

void Mage::OnEye()
{
	for (Mage_Eye* eye : eyes)
		eye->SetIsActive(true);
}

void Mage::LoadActions()
{
	vector<Texture*> clips;

	wstring filePath = L"Resource/Textures/Enemy/Mage/Mage_";

	//TRANSFORM
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 12; j++)
			clips.push_back(TEXTURE->Add(filePath + L"TransForm.png", j, i, 12, 4));
	}
	actions.push_back(new Animation(clips, Type::END, 0.07f));
	clips.clear();

	//IDLE
	for (int i = 4; i < 8; i++)
		clips.push_back(TEXTURE->Add(filePath + L"IdleAndMove.png", i, 0, 12, 1));
	actions.push_back(new Animation(clips, Type::LOOP, 0.1f));
	clips.clear();

	//LEFTMOVE
	for (int i = 8; i < 12; i++)
		clips.push_back(TEXTURE->Add(filePath + L"IdleAndMove.png", i, 0, 12, 1));
	actions.push_back(new Animation(clips, Type::LOOP, 0.07f));
	clips.clear();

	//RIGHTMOVE
	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(filePath + L"IdleAndMove.png", i, 0, 12, 1));
	actions.push_back(new Animation(clips, Type::LOOP, 0.07f));
	clips.clear();

	//INTELEPORT
	for (int i = 7; i >= 0; i--)
		clips.push_back(TEXTURE->Add(filePath + L"Teleport.png", i, 0, 8, 1));
	actions.push_back(new Animation(clips, Type::END, 0.07f));
	clips.clear();

	//OUTTELEPORT
	for (int i = 0; i < 8; i++)
		clips.push_back(TEXTURE->Add(filePath + L"Teleport.png", i, 0, 8, 1));
	actions.push_back(new Animation(clips, Type::END , 0.07f));
	clips.clear();

	//ATTACKREADY
	for (int i = 0; i < 4; i++)
		clips.push_back(TEXTURE->Add(filePath + L"AttackReady.png", i, 0, 4, 1));
	actions.push_back(new Animation(clips, Type::END, 0.1f));
	clips.clear();

	//ATTACK
	for (int i = 0; i < 2; i++)
		clips.push_back(TEXTURE->Add(filePath + L"Attack.png", i, 0, 2, 1));
	actions.push_back(new Animation(clips, Type::LOOP, 0.1f));
	clips.clear();

	actions[TRANSFORM]->SetEndEvent(bind(&Mage::Idle, this));
	actions[ATTACKREADY]->SetEndEvent(bind(&Mage::Attack, this));
	actions[INTELEPORT]->SetEndEvent(bind(&Mage::InTeleportEndEvent, this));
	actions[OUTTELEPORT]->SetEndEvent(bind(&Mage::OutTeleportEndEvent, this));
}

void Mage::SetPlayer(Player* player)
{
	this->player = player;
	
	for (Mage_Eye* eye : eyes)
		eye->SetPlayer(player);

	for (Mage_FireBall* fireBall : fireBalls)
		fireBall->SetPlayer(player);

	blackBall->SetPlayer(player);
}

void Mage::AttackPatternEnd()
{	
	actions[ATTACK]->Stop();
	SetActions(IDLE);
	attackPattern = NONE;
}

void Mage::TeleportEvent()
{
	if (!isTeleport)
		return;

	teleportTime += DELTA;

	if (teleportTime >= 0.5f)
	{
		isTeleport = false;
		color.a = 1.0f;
		SetActions(OUTTELEPORT);
	}
}

void Mage::InTeleportEndEvent()
{
	color.a = 0;
	
	if (attackPattern == EYE_ROTATIONLASER)
	{
		pos = { 56, 72 };
	}
	else
	{
		pos.x = player->pos.x;
		pos.y = player->pos.y - 200;
	}

	isTeleport = true;
}

void Mage::OutTeleportEndEvent()
{
	if (attackPattern == EYE_ROTATIONLASER)
	{
		SetActions(ATTACKREADY);
	}
	else
	{
		if (pos.x < -300)
			attackPattern = EYE_LASERRIGHTMOVE;
		else if (pos.x > 400)
			attackPattern = EYE_LASERLEFTMOVE;
		else
			OP::Random(0, 1) ? attackPattern = EYE_LASERRIGHTMOVE : attackPattern = EYE_LASERLEFTMOVE;

		SetActions(ATTACKREADY);
	}


}

void Mage::TransForm()
{
	actions[state]->Play();
	emote->IsActiveFalse();
}

void Mage::ReSet()
{
	if (state == TRANSFORM)
		return;

	state = TRANSFORM;
	eyes[0]->SetIsActive(false);
	eyes[1]->SetIsActive(false);
	hp = mageMaxHp;
	attackDelay = 0.0f;
	pos = { 0, -300 };
	isEmote = false;
	isActive = true;
}

void Mage::SetUI()
{
	GUI->SetBossHp(&hp, &mageMaxHp);
}

void Mage::EnemyActions()
{
	switch (state)
	{
	case Mage::TRANSFORM:
		break;
	case Mage::IDLE:
	case Mage::LEFTMOVE:
	case Mage::RIGHTMOVE:
		if (attackPattern == NONE)
		{
			if (player->pos.x > pos.x)
				SetActions(RIGHTMOVE);
			else
				SetActions(LEFTMOVE);

			pos = LERP(pos, player->pos, DELTA * 0.5f);

			attackDelay += DELTA;

			if (attackDelay >= MAGE_ATTACK_DELAY)
			{
				attackDelay = 0.0f;

				switch (OP::Random(0, 6))
				{
				case 0:
					attackPattern = EYE_ROTATION;
					eyes[0]->InTeleport();
					eyes[1]->InTeleport();
					break;
				case 1:
					SetActions(ATTACKREADY);
					attackPattern = MAGE_FIREBALL;
					break;
				case 2:
					SetActions(INTELEPORT);
					break;
				case 4:
					attackPattern = MAGE_8DIR_FIREBALL;
					SetActions(ATTACKREADY);
					break;
				case 5:
					attackPattern = EYE_ROTATIONLASER;
					SetActions(INTELEPORT);
					break;
				case 6:
					attackPattern = MAGE_BLACKBALL;
					SetActions(ATTACKREADY);
					break;
				}
			}
		}

		if (attackPattern == EYE_ROTATION)
		{
			Vector2 vec = player->pos - pos;

			if (D3DXVec2Length(&vec) > 200 || D3DXVec2Length(&vec) < 200)
			{
				pos.x += cos(OP::VecToAngle(OP::GetNomalize(vec))) * 2;
				pos.y -= -sin(OP::VecToAngle(OP::GetNomalize(vec))) * 2;
			}
		}
		break;
	case Mage::ATTACK:
		switch (attackPattern)
		{
		case Mage::EYE_LASERLEFTMOVE:
			pos.x -= 100 * DELTA;
			break;
		case Mage::EYE_LASERRIGHTMOVE:
			pos.x += 100 * DELTA;
			break;
		case Mage::MAGE_FIREBALL:
			if (attackPattern == MAGE_FIREBALL)
			{
				fireBallAttackDelay += DELTA;

				if (fireBallAttackDelay >= 0.5f)
				{
					Vector2 mageToPlayer = player->pos - pos;
					fireBalls[fireBallAttackCount]->Shoot(pos, OP::VecToAngle(OP::GetNomalize(mageToPlayer)));
					fireBallAttackDelay = 0.0f;
					fireBallAttackCount++;
					SOUND->Play("FireBallShoot");
				}
			}
			break;
		case Mage::MAGE_8DIR_FIREBALL:
		{
			multiFireBallTime += DELTA;

			if (multiFireBallTime > 1.0f)
			{
				multiFireBallTime = 0.0f;
				int count = 0;

				for (int i = 0; i < fireBalls.size(); i++)
				{
					if (!fireBalls[i]->GetIsActive())
					{
						fireBalls[i]->Shoot(pos, (i* (PI * 0.25)));
					}

				}

				SOUND->Play("FireBall8DirShoot");

				AttackPatternEnd();
			}
		}
			break;
		case Mage::MAGE_BLACKBALL:

			break;
		case Mage::NONE:
			break;
		default:
			break;
		}
	default:
		break;
	}

	if (fireBallAttackCount >= FIREBALLCOUNT)
	{
		AttackPatternEnd();
		fireBallAttackCount = 0;
	}
}
