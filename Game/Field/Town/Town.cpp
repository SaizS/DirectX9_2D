#include "framework.h"

Town::Town()
{
	backGround = TEXTURE->Add(L"Resource/Textures/Town/Town_BackGround.png");
	pos = { WIN_HALFWIDTH, WIN_HALFHEIGHT - 70 };
	Load();
	LoadAnimation();
	water = TEXTURE->Add(L"Resource/Textures/Town/Town_Water.png");

	textureSize = backGround->GetSize();
}

Town::~Town()
{
	delete waterObjets;
}

void Town::Update()
{
	waterObjets->Update();

	ChangeMap();

	World::Update();

	if (textureList.size() == 0)
		return;

	for (Info* info : textureList)
	{
		info->Update();
	}

	npcs.back()->Update();

	if (collsionWorld.size() > 0)
	{
		for (World* world : collsionWorld)
		{
			world->CollisionMove(player);
			world->Update();
		}
	}

	NpcEvent();
	ObjectCollision();
	WindowCollision();
	PortionCollision();
	MouseCollision();
}

void Town::Render()
{
	SetWorld();
	water->AlphaRender();
	waterObjets->AlphaRender();
	backGround->AlphaRender();

	if (textureList.size() == 0)
		return;

	sort(textureList.begin(), textureList.end(), Compare);

	for (Info* info : textureList)
		info->Render();

	npcs.back()->Render();
}

void Town::SetPlayer(Player* player)
{
	this->player = player;
	textureList.push_back(player);
}

void Town::InitPortion(vector<Potion*> data)
{
	for (int i = 0; i < data.size(); i++)
		textureList.push_back(data[i]);
}

void Town::Load()
{
	/*for (Object* objectData : DATA->GetObjectData("TownObjects"))
	{
		textureList.push_back(objectData);
		buildings.push_back(objectData);
	}*/

	for (World* worldData : DATA->GetCollisionWorldData("TownCollisionWorlds"))
		collsionWorld.push_back(worldData);

	npcs.push_back(NPC->GetNpc("BlackSmith"));
	textureList.push_back(NPC->GetNpc("BlackSmith"));
	npcs.push_back(NPC->GetNpc("FolkOne"));
	textureList.push_back(NPC->GetNpc("FolkOne"));
	npcs.push_back(NPC->GetNpc("FolkTwo"));
	textureList.push_back(NPC->GetNpc("FolkTwo"));
	npcs.push_back(NPC->GetNpc("ChildMan1"));
	textureList.push_back(NPC->GetNpc("ChildMan1"));
	textureList.push_back(NPC->GetNpc("ChildWoman1"));
	textureList.push_back(NPC->GetNpc("ChildWoman2"));
	textureList.push_back(NPC->GetNpc("Cat"));
	npcs.push_back(NPC->GetNpc("ChildMan2"));
}

void Town::LoadAnimation()
{
	vector<Texture*> clips;
	for (int i = 0; i < 4; i++)
	{
		wstring str = L"Resource/Textures/Town/Town_Ani" + to_wstring(i + 1) + L".png";
		Texture* texture = TEXTURE->Add(str);
		clips.push_back(texture);
	}
	waterObjets = new Animation(clips, Type::LOOP);
	waterObjets->Play();
}

void Town::ObjectCollision()
{
	for (Object* object : buildings)
	{
		if (object->GetFilePath() == L"Object/26.png" || object->GetFilePath() == L"Object/27.png")
			continue;

		object->CollisionMove(player);
	}

	for (Npc* npc : npcs)
		npc->CollisionMove(player);
}

void Town::WindowCollision()
{
	Vector2 LT = { WIN_HALFWIDTH - (textureSize.x * 0.5f), WIN_HALFHEIGHT - (textureSize.y * 0.5f) };
	Vector2 RB = { WIN_HALFWIDTH + (textureSize.x * 0.5f), WIN_HALFHEIGHT + (textureSize.y * 0.5f) };

	if (player->GetHitBox()->Left() < LT.x)
		player->pos.x = LT.x + player->GetHitBox()->HalfSize().x;
	if (player->GetHitBox()->Right() > RB.x)
		player->pos.x = RB.x - player->GetHitBox()->HalfSize().x;
	if (player->GetHitBox()->Top() < LT.y)
		player->pos.y = LT.y + player->GetHitBox()->HalfSize().y;
	if (player->GetHitBox()->Bottom() > RB.y)
		player->pos.y = RB.y - player->GetHitBox()->HalfSize().y;
}

void Town::PortionCollision()
{
	if (player->GetPortions().size() == 0)
		return;

	for (Potion* potion : player->GetPortions())
	{
		if (potion->GetIsActive())
		{
			for (Info* info : buildings)
			{
				if (info->Collision(potion))
				{
					potion->Crash();
					return;
				}
				if (potion->pos.x < -CAM->pos.x - FLASKSIZE) {
					potion->SetIsActive(false);
					return;
				}
				if (potion->pos.y < -CAM->pos.y - FLASKSIZE) {
					potion->SetIsActive(false);
					return;
				}
				if (potion->pos.x > -CAM->pos.x + WIN_HEIGHT + WIN_HALFWIDTH - FLASKSIZE) {
					potion->SetIsActive(false);
					return;
				}
				if (potion->pos.y > -CAM->pos.y + WIN_HEIGHT + WIN_HALFWIDTH - FLASKSIZE) {
					potion->SetIsActive(false);
					return;
				}
			}
		}
	}
}

void Town::MouseCollision()
{
	bool isCheck = false;

	for (Npc* npc : npcs)
	{
		if (npc->Collision(MOUSEPOS))
		{
			isCheck = true;
			break;
		}
	}

	if (isCheck)
		INPUTMANAGER->SetIsTalk(true);
	else
		INPUTMANAGER->SetIsTalk(false);
}

void Town::NpcEvent()
{
	int count = 0;
	for (Npc* npc : npcs)
	{
		if (npc->Collision(player))
		{
			count++;
			if (npcs[0] == npc) // 대장장이
			{
			}

			if (npcs[1] == npc) // FolkOne(상점주인)
			{
				GUI->GetInven()->OpenInven();
				GUI->GetStore()->OpenStore();
			}

			if (npcs[2] == npc) // FolkTwo
			{
			}
		}
	}

	if (player->pos.y < -94) // 보드 이벤트 발생
	{
		if (player->pos.x > 701 && player->pos.x < 767)
		{
		}
	}
}

void Town::ChangeMap()
{
	if (player->pos.y < -202)
	{
		if (player->pos.x > 44 && player->pos.x < 81)
		{
			CURSCENE->SetFade("Home", { 512, 566 });
			player->SetFade();
		}
	}

	if (player->pos.y > 1100)
	{
		CURSCENE->SetFade("Forest", { 1262, -747 });
		player->SetIsAttack(true);
		player->SetFade();
		return;
	}
}

bool Town::Compare(World* val1, World* val2)
{
	return val1->pos.y + val1->offset.y < val2->pos.y + val2->offset.y;
}