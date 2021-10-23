#include "framework.h"

Mage_Eye::Mage_Eye(Vector2 pos, World* world, function<void()> AttackEndEvent) : isActive(false), isTeleport(false), isRotationAttack(false), isPattern1(false), AttackEndEvent(AttackEndEvent)
{
	LoadActions();

	state = IDLE;

	this->pos = { 0,0 };

	basicPos = pos;

	pos.x > 0 ? isRight = true : isRight = false;

	rotDistance = OP::VectorLength(pos - this->pos);
	rotAngle = OP::VecToAngle(OP::GetNomalize(pos - this->pos));

	basicDistance = OP::VectorLength(pos - this->pos);
	basicAngle = OP::VecToAngle(OP::GetNomalize(pos - this->pos));

	this->pos.x = cos(rotAngle) * rotDistance;
	this->pos.y = sin(rotAngle) * rotDistance;

	SetCircle(20.0f);

	SetParent(world->GetWorld());

	teleportDelay = 0;
	rotationAttackTime = 0;

	magePos = &world->pos;

	laser = new Mage_EyeLaser(this);

	laser->EndEvent(AttackEndEvent);
}

Mage_Eye::~Mage_Eye()
{
	delete laser;
}

void Mage_Eye::Update()
{
	if (!isActive)
		return;

	for (Potion* potion : player->GetPortions())
	{
		if (potion->GetIsActive())
		{
			if (potion->Collision(this))
				potion->Crash();
		}
	}

	offset = *magePos;

	Teleport();
	RotationAttack();
	LaserCollision();

	this->pos.x = cos(rotAngle) * rotDistance;
	this->pos.y = sin(rotAngle) * rotDistance;

	RotationLaser();

	if (CollisionCircleRect(player->GetHitBox()) && state == IDLE)
	{
		Vector2 eyeToPlayaer = player->pos - pos;
		player->Damage(20, OP::VecToAngle(OP::GetNomalize(eyeToPlayaer)));
	}

	actions[state]->Update();

	World::Update();

	laser->Update();
}

void Mage_Eye::Render()
{
	if (!isActive)
		return;

	SetWorld();

	shader->SetTexture("map", actions[state]->GetTexture());
	shader->SetVector("color", &color, 4);
	shader->Begin();
	actions[state]->Render();
	shader->End();

	laser->Render();
}

void Mage_Eye::EnemyActions()
{
}

void Mage_Eye::Idle()
{
	SetActions(IDLE);
}

void Mage_Eye::LoadActions()
{
	vector<Texture*> clips;

	clips.push_back(TEXTURE->Add(L"Resource/Textures/Enemy/Mage/Mage_Eye.png"));
	actions.push_back(new Animation(clips));
	clips.clear();

	for (int i = 0; i < 5; i++)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Enemy/Mage/Mage_EyeTeleport.png", i, 0, 5, 1));
	actions.push_back(new Animation(clips, Type::END, 0.15f));
	clips.clear();

	for (int i = 4; i >= 0; i--)
		clips.push_back(TEXTURE->Add(L"Resource/Textures/Enemy/Mage/Mage_EyeTeleport.png", i, 0, 5, 1));
	actions.push_back(new Animation(clips, Type::END, 0.15f));
	clips.clear();

	actions[INTELEPORT]->SetEndEvent(bind(&Mage_Eye::SetTeleport, this));
	actions[OUTTELEPORT]->SetEndEvent(bind(&Mage_Eye::SetRotationAttack, this));
}

void Mage_Eye::Teleport()
{
	if (!isTeleport)
		return;

	teleportDelay += DELTA;

	if (teleportDelay >= 1.0f)
	{
			color.a = 1.0f;
			teleportDelay = 0;
			isTeleport = false;
			SetActions(OUTTELEPORT);
	}
}

void Mage_Eye::RotationAttack()
{
	if (!isRotationAttack)
		return;

	rotAngle += DELTA * 4;
	rotationAttackTime += DELTA;

	if (rotationAttackTime >= 3)
	{
		rotationAttackTime = 0.0f;
		isRotationAttack = false;

		SetActions(INTELEPORT);
	}
}

void Mage_Eye::SetActions(Mage_EyeState state)
{
	if (this->state == state)
		return;

	this->state = state;
	actions[state]->Play();
}

void Mage_Eye::SetTeleport()
{
	isTeleport = true;
	color.a = 0.0f;

	if (isPattern1)
	{
		rotDistance = basicDistance;
		rotAngle = basicAngle;
	}
	else
	{
		isRight ? rotAngle = PI *0.5f : rotAngle = -(PI * 0.5f);
		rotDistance = 200;
		if (!SOUND->CheckMusic("RotationEye"))
			SOUND->Play("RotationEye");
	}
}

void Mage_Eye::SetRotationAttack()
{
	if (!isPattern1)
	{
		isRotationAttack = true;
		isPattern1 = true;
		Idle();
	}
	else
	{
		isPattern1 = false;
		Idle();
		AttackEndEvent();
	}
}

void Mage_Eye::InTeleport()
{
	SetActions(INTELEPORT);
}

void Mage_Eye::LaserShoot()
{
	laser->SetLaser();
}

void Mage_Eye::RotationLaser()
{
	if (!isRotationLaser)
		return;

	if (!laser->GetIsShoot())
		laser->SetLaser(true);

	if (laser->GetIsShoot())
	{
		rot.z += DELTA * 1.2f;
		rotAngle += DELTA * 1.2f;
	}

	if (rot.z >= 2 * PI)
	{
		rot.z = 0.0f;
		rotAngle = basicAngle;
		AttackEndEvent();
		isRotationLaser = false;
		laser->LaserEnd();
		SOUND->Stop("LaserBurst");
	}
}

void Mage_Eye::RotaionLaserShoot()
{
	isRotationLaser = true;
	laser->SetLaser(true);
}

void Mage_Eye::LaserCollision()
{
	if (isRotationLaser)
	{
		if (laser->GetIsShoot() && laser->ObbCollision(player->GetHitBox()))
		{
			float angle = isRight ? PI + rot.z : rot.z;
			player->Damage(50, angle);
		}
	}
	else
	{
		if (laser->GetIsShoot() && laser->Collision(player->GetHitBox()))
		{
			float angle = isRight ? PI + rot.z : rot.z;
			player->Damage(50, angle);
		}
	}
}
