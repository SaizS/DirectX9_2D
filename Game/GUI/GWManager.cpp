#include "framework.h"

GWManager::GWManager()
{
}

GWManager::~GWManager()
{
}

void GWManager::Update()
{
	World::Update();
	for (int i = 0; i < windows.size(); i++) {
		if (i < 6) {
			windows[i]->isActive = true;
		}
		else {
			windows[i]->isActive = false;
		}
		windows[i]->Update();
		if (windows[i]->duration <= 0) {
			windows.erase(windows.begin() + i);
			i--;
		}
	}
}

void GWManager::Render()
{
	SetWorld();
	int length = 0;
	Matrix matWorld;
	Matrix matWorld2;
	float startPos = 0;
	for (int i = 0; i < windows.size(); i++)
	{
		D3DXMatrixTranslation(&matWorld, 0, startPos + length, 0);
		matWorld *= world;
		DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
		windows[i]->PanelRender();

		D3DXMatrixTranslation(&matWorld2, -39, startPos + length + 4, 0);
		matWorld2 *= world;
		DEVICE->SetTransform(D3DTS_WORLD, &matWorld2);
		windows[i]->ItemImageRender();
		length -= windows[0]->GetPanel()->GetSize().y + 6;
	}
}

void GWManager::AddWindow(int key, float duration)
{
	GetItemWindow* temp = new GetItemWindow(key, duration);
	temp->SetParent(&world);
	windows.push_back(temp);
}
