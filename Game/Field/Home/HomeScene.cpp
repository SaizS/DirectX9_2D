#include "framework.h"

HomeScene::HomeScene(Player* player) : player(player)
{
	home = new Home();

	home->SetPlayer(player);
}

HomeScene::~HomeScene()
{
	delete home;
}

void HomeScene::Init()
{
}

void HomeScene::Update()
{
	home->Update();

	renderTarget->Begin();
	CAM->SetView();
	home->Render();
	GUI->Render();
	renderTarget->End();
}

void HomeScene::Release()
{
}

void HomeScene::SetPos(Vector2 pos)
{
	player->pos = pos;
}
