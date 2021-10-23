#include "framework.h"

ForestScene::ForestScene(Player* player) : player(player)
{
	forest = new Forest();
	forest->SetPlayer(player);

	forest->InitPortion(player->GetPortions());
}

ForestScene::~ForestScene()
{
	delete forest;
}

void ForestScene::Init()
{
}

void ForestScene::Release()
{

}

void ForestScene::Update()
{
	forest->Update();

	renderTarget->Begin();
	CAM->SetView();
	forest->Render();
	GUI->Render();
	renderTarget->End();
}
