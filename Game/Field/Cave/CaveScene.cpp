#include "framework.h"

CaveScene::CaveScene(Player* player) : player(player)
{
	cave = new Cave();
	cave->SetPlayer(player);
}

CaveScene::~CaveScene()
{
	delete cave;
}

void CaveScene::Init()
{
}

void CaveScene::Update()
{
	cave->Update();

	renderTarget->Begin();
	CAM->SetView();
	cave->Render();
	GUI->Render();
	renderTarget->End();
}

void CaveScene::Release()
{
}

void CaveScene::SetPos(Vector2 pos)
{
	player->pos = pos;
}