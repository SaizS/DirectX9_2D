#include "framework.h"

Home::Home()
{
	backGround = TEXTURE->Add(L"Resource/Textures/Home/Home.png");

	Vector2 backSize = backGround->GetSize();

	pos = { WIN_HALFWIDTH, WIN_HALFHEIGHT };

	Load();
}

Home::~Home()
{
}

void Home::Update()
{
	CollisionObject();

	for (Info* info : textureList)
		info->Update();

	for (World* world : collisionWorld)
		world->Update();

	World::Update();

	InTown();
}

void Home::Render()
{
	SetWorld();

	backGround->Render();

	sort(textureList.begin(), textureList.end(), Compare);

	for (Info* info : textureList)
		info->Render();
}

void Home::SetPlayer(Player* player)
{
	this->player = player;
	textureList.push_back(player);
}

void Home::Load()
{
	for (Object* objectData : DATA->GetObjectData("HomeObjects"))
	{
		textureList.push_back(objectData);
		buildings.push_back(objectData);
	}

	for(World* worldData : DATA->GetCollisionWorldData("HomeCollisionWorlds"))
		collisionWorld.push_back(worldData);
}

void Home::CollisionObject()
{
	for (Object* object : buildings)
	{
		if(object != buildings.back())
			object->CollisionMove(player);
		if (object == buildings.back() && object->CollisionMove(player))
		{
			GUI->GetCauldron()->OpenCauldron();
		}
	}

	for (World* world : collisionWorld)
	{
		world->CollisionMove(player);
	}
}

void Home::InTown()
{
	if (collisionWorld.back()->CollisionMove(player))
	{
		CURSCENE->SetFade("Town", { 61, -185 });
		player->SetFade();
	}
}

bool Home::Compare(World* val1, World* val2)
{
	return val1->pos.y + val1->offset.y < val2->pos.y + val2->offset.y;
}
