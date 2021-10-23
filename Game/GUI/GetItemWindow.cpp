#include "framework.h"

GetItemWindow::GetItemWindow(int key, float duration) : duration(duration), startFlick(0.0f), endFlick(1.0f)
{
	isActive = false;
	panel = TEXTURE->Add(L"Resource/Textures/UI/itemGet.png");


	itemImage = new ItemImage(key);
	itemImage->SetPos(-38, 3);
	itemImage->SetParent(&world);

	shader = Shader::Add(L"Shader/Object.hlsl");
	color = 0xffffffff;
}

GetItemWindow::~GetItemWindow()
{
	delete itemImage;
}

void GetItemWindow::Update()
{
	if (!isActive)
		return;
	if (duration <= 0)
		return;
	World::Update();
	itemImage->Update();
	duration -= DELTATIME;
	if (startFlick < 1) {
		color.a = 1.0f * startFlick;
		startFlick += DELTATIME * 2;
		if (startFlick > 1)
			startFlick = 1;
	}
	if (duration < 1) {
		color.a = 1.0f * endFlick;
		endFlick -= DELTATIME;
		if (endFlick < 0)
			endFlick = 0.0f;
	}

}

void GetItemWindow::PanelRender()
{
	shader->Begin();
	shader->SetVector("color", (float*)& color, 4);
	shader->SetTexture("map", panel->GetTexture());
	shader->End();

	if (!isActive)
		return;
	shader->Begin();
	shader->SetVector("color", (float*)& color, 4);
	shader->SetTexture("map", panel->GetTexture());
	panel->Render();
	shader->End();
}

void GetItemWindow::ItemImageRender()
{
	shader->Begin();
	shader->SetVector("color", (float*)& color, 4);
	shader->SetTexture("map", itemImage->GetTexture());
	shader->End();

	if (!isActive)
		return;
	shader->Begin();
	shader->SetVector("color", (float*)& color, 4);
	shader->SetTexture("map", itemImage->GetTexture());
	itemImage->UnSetWorldRender();
	shader->End();
}
