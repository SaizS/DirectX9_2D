#include "framework.h"

Forest::Forest()
{
	backGround.push_back(TEXTURE->Add(L"Resource/Textures/Forest/Forest_BackGround.png"));
	backGround.push_back(TEXTURE->Add(L"Resource/Textures/Forest/Forest_Water.png"));

	Load();
	LoadAnimation();

	pos = { WIN_HALFWIDTH, WIN_HALFHEIGHT };

	paticles = PaticleManager::GetInstance()->GetPaticle("ForestPaticle");
}

Forest::~Forest()
{
	delete waterAni;
}

void Forest::Update()
{
	waterAni->Update();

	ChangeMap();

	ObjectCollision();
	CollectPaticle();
	MouseCollision();

	for (Info* info : textureList)
		info->Update();

	for (Paticle* paticle : paticles)
		paticle->Update();

	World::Update();

	ChangeMap();
}

void Forest::Render()
{
	SetWorld();

	for (Texture* texture : backGround) // BackGround Render
		texture->AlphaRender();

	waterAni->AlphaRender();			// WaterFall Render

	for (Paticle* paticle : paticles)	// Paticle Render
		paticle->Render();

	sort(textureList.begin(), textureList.end(), Compare); // Z Order Sort

	for (Info* info : textureList)		// Player, Enemy, Object Render
		info->Render();
}

void Forest::ChangeMap()
{
	if (player->pos.y < -880)
	{
		if (player->pos.x > 1200 && player->pos.x < 1300)
		{
			CURSCENE->SetFade("Town", { 510, 1000 });
			player->SetIsAttack(false);
			player->SetFade();
			return;
		}
	}

	if (player->pos.y < -830)
	{
		if (player->pos.x > -275 && player->pos.x < -85)
		{
			CURSCENE->SetFade("Mountain", { 1006,1136 });
			player->SetFade();
		}
	}
}

void Forest::InitPortion(vector<Potion*> data)
{
	for (Potion* portion : data)
		textureList.push_back(portion);
}

void Forest::Load()
{
	for (Object* objectData : DATA->GetObjectData("ForestObjects"))
	{
		textureList.push_back(objectData);
		buildings.push_back(objectData);
	}

	for (World* worldData : DATA->GetCollisionWorldData("ForestCollisionWorlds"))
		collisionWorlds.push_back(worldData);

	slimes = ENEMY->FindEnemy("GreenSlime");
	chicken = ENEMY->FindEnemy("BlackChicken");
	mushRoom = ENEMY->FindEnemy("MushRoom");

	for (auto forestEnemies : ENEMY->GetForestEnemy())
	{
		for (Enemy* enemy : forestEnemies)
			textureList.push_back(enemy);
	}

	for (Effect* effect : EFFECT->GetEffect("Hit"))
		textureList.push_back(effect);

	for (Effect* effect : EFFECT->GetEffect("MushRoomAttack"))
		textureList.push_back(effect);
}

void Forest::LoadAnimation()
{
	vector<Texture*> clips;

	for (int i = 0; i < 4; i++)
	{
		wstring str = L"Resource/Textures/Forest/Forest_Ani" + to_wstring(i + 1) + L".png";
		clips.push_back(TEXTURE->Add(str));
	}

	waterAni = new Animation(clips, Type::LOOP, 0.08f);
	waterAni->Play();
}

void Forest::ObjectCollision()
{
	for (Object* object : buildings)
	{
		if (!(object->GetFilePath() == L"Object/26.png" || object->GetFilePath() == L"Object/27.png")) // 꽃 예외 처리
			object->CollisionMove(player);

		for (auto forestEnemies : ENEMY->GetForestEnemy())
		{
			for (Enemy* enemy : forestEnemies)
			{
				Vector2 temp = enemy->pos - player->pos;
				temp.x = abs(temp.x);
				temp.y = abs(temp.y);
				if (enemy->GetIsActive() && temp.x < WIN_HALFWIDTH && temp.y < WIN_HALFHEIGHT)
					object->CollisionMove(enemy);
			}
		}

		for (Potion* portion : player->GetPortions())
		{
			if (portion->GetIsActive())
			{
				if (portion->Collision(object))
				{
					portion->Crash();
				}
			}
		}
	}

	if (collisionWorlds.size() > 0)
	{
		for (World* world : collisionWorlds) // 충돌월드 반복
		{
			world->CollisionMove(player);	// 월드와 플레이어의 충돌 및 이동처리

			for (auto forestEnemies : ENEMY->GetForestEnemy())
			{
				for (Enemy* enemy : forestEnemies) // 숲 몬스터 반복
				{
					//Vector2 temp = { abs(enemy->pos.x - player->pos.x), abs(enemy->pos.y - player->pos.y) }; // 몬스터와 플레이어의 거리 체크

					//if (enemy->GetIsActive() && temp.x < WIN_HALFWIDTH && temp.y < WIN_HALFHEIGHT) // 몬스터가 카메라 범위 안에 있을때만 체크
					world->CollisionMove(enemy); // 몬스터 충돌 및 이동처리
				}
			}
		}
	}
}

void Forest::CollectPaticle()
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

void Forest::MouseCollision()
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

bool Forest::Compare(World* val1, World* val2)
{
	return val1->pos.y + val1->offset.y < val2->pos.y + val2->offset.y;
}