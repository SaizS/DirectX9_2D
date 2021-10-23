#include "framework.h"

MountainScene::MountainScene(Player* player) : player(player)
{
	mountain = new Mountain();
	mountain->SetPlayer(player);
	mountain->SetPortion(player->GetPortions());
}

MountainScene::~MountainScene()
{
	delete mountain;
}

void MountainScene::Init()
{
}

void MountainScene::Update()
{
	if (KEYPRESS(VK_DOWN))
		color.a -= DELTA;
	if (KEYPRESS(VK_UP))
		color.a += DELTA;

	mountain->Update();

	renderTarget->Begin();
	CAM->SetView();
	mountain->Render();
	GUI->Render();
	renderTarget->End();
}

void MountainScene::Release()
{
}

void MountainScene::SetPos(Vector2 pos)
{
	player->pos = pos;
}
