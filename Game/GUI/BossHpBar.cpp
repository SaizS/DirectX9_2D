#include "framework.h"

BossHpBar::BossHpBar() : curHp(NULL), maxHp(NULL)
{
	panel = TEXTURE->Add(L"Resource/Textures/UI/bossGauge.png");
	hpBar = TEXTURE->Add(L"Resource/Textures/UI/bossHp.png");
	hpBarWorld = new World();
	hpBarWorld->SetPos(0, 14);
	hpBarWorld->SetParent(&world);
	hpbarShader = Shader::Add(L"Shader/HpBar.hlsl");
	if (curHp == NULL || maxHp == NULL)
		return;
	if (*curHp == 0)
		isActive = false;
}

BossHpBar::~BossHpBar()
{
	delete hpBarWorld;
}

void BossHpBar::Render()
{
	World::Update();
	if (!isActive)
		return;

	SetWorld();
	panel->AlphaRender();

	if (curHp == NULL || maxHp == NULL)
		return;
	hpbarShader->Begin(); //hp½¦ÀÌ´õ ¿ÀÇÂ
	hpbarShader->SetFloat("value", *curHp / *maxHp);
	hpbarShader->SetTexture("map", hpBar->GetTexture());
	hpbarShader->End(); //hp ½¦ÀÌ´õ ´ÝÀ½

	hpbarShader->Begin(); //hp½¦ÀÌ´õ ¿ÀÇÂ
	hpbarShader->SetFloat("value", *curHp / *maxHp);
	hpbarShader->SetTexture("map", hpBar->GetTexture());
	hpBarWorld->Update();
	hpBarWorld->SetWorld();
	hpBar->Render();
	hpbarShader->End(); //hp ½¦ÀÌ´õ ´ÝÀ½

}
