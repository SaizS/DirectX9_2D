#include "framework.h"

TownScene::TownScene(Player* player) : player(player)
{
	town = new Town();
	town->SetPlayer(player);
	town->InitPortion(player->GetPortions());
}

TownScene::~TownScene()
{
	delete town;
}

void TownScene::Init()
{
}

void TownScene::Update()
{
	town->Update();

	renderTarget->Begin();
	CAM->SetView();
	town->Render();

	if (!isMapEditor)
		GUI->Render();
	else
		MAP->Render();

	renderTarget->End();
}

void TownScene::Release()
{
}