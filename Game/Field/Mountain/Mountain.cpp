#include "framework.h"

Mountain::Mountain()
{
	Load();

	paticles = PATICLE->GetPaticle("MountainPaticle");
}

Mountain::~Mountain()
{
	delete trees;
}

void Mountain::Update()
{
	ChangeMap();
	ObjectCollision();
	CollectPaticle();	
	MouseCollision();

	for (World* world : collisionWorld)
		world->Update();
	for (Info* info : textureList)
		info->Update();
	trees->Update();	
	World::Update();

	for (Paticle* paticle : paticles)
		paticle->Update();	
}

void Mountain::Render()
{
	SetWorld();

	backGround->Render();

	for (Info* info : textureList)
		info->Render();

	for (Paticle* paticle : paticles)
		paticle->Render();

	trees->Render();
}

void Mountain::ObjectCollision()
{
	for (World* world : collisionWorld)
	{
		world->CollisionMove(player);

		for (auto mountainEnemies : ENEMY->GetMountainEnemy())
		{
			for (Enemy* enemy : mountainEnemies)
				world->CollisionMove(enemy);
		}

		for (Potion* potion : player->GetPortions())
		{
			if (potion->Collision(world))
				potion->Crash();
		}
	}

	for (Object* object : buildings)
	{
		object->CollisionMove(player);

		for (auto mountainEnemies : ENEMY->GetMountainEnemy())
		{
			for (Enemy* enemy : mountainEnemies)
				object->CollisionMove(enemy);
		}

		for (Potion* potion : player->GetPortions())
		{
			if (potion->Collision(object))
				potion->Crash();
		}
	}
}

void Mountain::ChangeMap()
{
	if (player->pos.y > 1180)
	{
		if (player->pos.x > 885 && player->pos.x < 1180)
		{
			CURSCENE->SetFade("Forest", { -180, -786 });
			player->SetFade();
		}
	}
	if (player->pos.y < -1040)
	{
		if (player->pos.x > 960 && player->pos.x < 1010)
		{
			CURSCENE->SetFade("Cave", { 525, 440 });
			player->SetFade();
		}
	}
}

void Mountain::SetPlayer(Player* player)
{
	this->player = player;
	textureList.push_back(player);
}

void Mountain::SetPortion(vector<Potion*> data)
{
	for (Potion* portion : data)
		textureList.push_back(portion);
}

void Mountain::CollectPaticle()
{
	for (Paticle* paticle : paticles)
	{
		if (paticle->Collision(player) && paticle->GetIsAcitve())
		{
			if (KEYDOWN(VK_LBUTTON))
			{
				if (paticle->Collision(MOUSEPOS))
				{
					player->SetActions(Player::COLLECTING);
					player->SetPaticle(paticle);
					return;
				}
			}
		}
	}
}

void Mountain::MouseCollision()
{
	bool isCheck = false;

	for (auto forestEnemies : ENEMY->GetForestEnemy())
	{
		for (Enemy* enemy : forestEnemies)
		{
			if (enemy->Collision(MOUSEPOS) && enemy->GetIsActive())
			{
				isCheck = true;
				break;
			}
		}
	}

	if (isCheck)
	{
		INPUTMANAGER->SetIsAttack(true);
	}
	else
	{
		INPUTMANAGER->SetIsAttack(false);
	}

	isCheck = false;

	for (Paticle* paticle : paticles)
	{
		if (paticle->Collision(MOUSEPOS) && paticle->GetIsAcitve())
		{
			isCheck = true;
			break;
		}
	}

	if (isCheck)
	{
		INPUTMANAGER->SetIsGet(true);
	}
	else
	{
		INPUTMANAGER->SetIsGet(false);
	}
}

void Mountain::Load()
{
	backGround = TEXTURE->Add(L"Resource/Textures/Mountain/Mountain_BackGround.png");
	trees = new Object(TEXTURE->Add(L"Resource/Textures/Mountain/Mountain_Trees.png"));

	for(Object* objectData : DATA->GetObjectData("MountainObjects"))
	{
		textureList.push_back(objectData);
		buildings.push_back(objectData);
	}

	for(World* worldData : DATA->GetCollisionWorldData("MountainCollisionWorlds"))
		collisionWorld.push_back(worldData);

	for (auto mountainEnemies : ENEMY->GetMountainEnemy())
	{
		for (Enemy* enemy : mountainEnemies)
			textureList.push_back(enemy);
	}

	for (Effect* effect : EFFECT->GetEffect("Poison"))
		textureList.push_back(effect);

	for (World* worldData : collisionWorld)
	{
		for (Enemy* enemy : ENEMY->FindEnemy("Flower"))
			worldData->CollisionMove(enemy);
	}

	for (Effect* effect : EFFECT->GetEffect("Hit"))
		textureList.push_back(effect);
}

bool Mountain::Compare(World* val1, World* val2)
{
	return false;
}
