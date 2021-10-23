#include "framework.h"

StateBar::StateBar() : curHp(NULL), maxHp(NULL)
{
	isActive = true;
	panel = TEXTURE->Add(L"Resource/Textures/UI/state.png");
	hpBar = TEXTURE->Add(L"Resource/Textures/UI/hp.png");
	playerIcon = TEXTURE->Add(L"Resource/Textures/UI/head.png");
	hpBarWorld = new World();
	hpBarWorld->SetPos(51, 5);
	hpBarWorld->SetParent(&world);
	pIWorld = new World();
	pIWorld->SetPos(-70, 3);
	pIWorld->SetParent(&world);
	hpbarShader = Shader::Add(L"Shader/HpBar.hlsl");
}

StateBar::~StateBar()
{
	delete hpBarWorld;
	delete pIWorld;
}

void StateBar::Render()
{
	World::Update();
	if (!isActive)
		return;
	pIWorld->Update();
	hpBarWorld->Update();

	SetWorld();
	panel->AlphaRender();

	pIWorld->SetWorld();
	playerIcon->AlphaRender();

	if (curHp == NULL || maxHp == NULL)
		return;
	hpbarShader->Begin(); //hp½¦ÀÌ´õ ¿ÀÇÂ
	hpbarShader->SetFloat("value", *curHp / *maxHp);
	hpbarShader->SetTexture("map", hpBar->GetTexture());
	hpbarShader->End(); //hp ½¦ÀÌ´õ ´ÝÀ½

	hpbarShader->Begin(); //hp½¦ÀÌ´õ ¿ÀÇÂ
	hpbarShader->SetFloat("value", *curHp / *maxHp);
	hpbarShader->SetTexture("map", hpBar->GetTexture());
	hpBarWorld->SetWorld();
	hpBar->Render();
	hpbarShader->End(); //hp ½¦ÀÌ´õ ´ÝÀ½

}
