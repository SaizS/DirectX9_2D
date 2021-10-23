#include "framework.h"

QuickSlot::QuickSlot() : selectedNum(0)
{
	isActive = false;
	panel = TEXTURE->Add(L"Resource/Textures/UI/quickSlot.png");

	for (int i = 0; i < QUICKSLOTCOUNT; i++) {
		ItemImage* itemImage = new ItemImage();
		itemImage->SetPos(i * 63 - 126, 1);
		itemImage->SetParent(&world);
		potionImages.push_back(itemImage);

		Texture* selectImage = TEXTURE->Add(L"Resource/Textures/UI/selected.png");
		selectImages.push_back(selectImage);

		ItemData* itemData = NULL;
		selectedPotions.push_back(itemData);
	}

	shader = Shader::Add(L"Shader/Object.hlsl");
	color = 0xffffffff;
}

QuickSlot::~QuickSlot()
{
	for (ItemImage* index : potionImages)
		delete index;
}

void QuickSlot::ChangeSlot()
{
	if (GUI->GetStore()->isActive)
		return;
	if (GUI->GetCauldron()->isActive)
		return;
	//인벤토리가 열려있는 경우 단축키는 포션 등록 기능을 수행
	if (GUI->GetInven()->isActive) {
		if (GUI->GUI->GetInven()->GetSelectedPotion() != NULL) {
			if (KEYDOWN(VK_1)) {
				SOUND->Play("set");
				ItemData* temp = GUI->GetInven()->GetSelectedPotion();
				selectedPotions[0] = temp;
			}
			if (KEYDOWN(VK_2)) {
				SOUND->Play("set");
				ItemData* temp = GUI->GetInven()->GetSelectedPotion();
				selectedPotions[1] = temp;
			}
			if (KEYDOWN(VK_3)) {
				SOUND->Play("set");
				ItemData* temp = GUI->GetInven()->GetSelectedPotion();
				selectedPotions[2] = temp;
			}
			if (KEYDOWN(VK_4)) {
				SOUND->Play("set");
				ItemData* temp = GUI->GetInven()->GetSelectedPotion();
				selectedPotions[3] = temp;
			}
			if (KEYDOWN(VK_5)) {
				SOUND->Play("set");
				ItemData* temp = GUI->GetInven()->GetSelectedPotion();
				selectedPotions[4] = temp;
			}
		}
	}
	//그렇지 않으면 단축키에 등록된 포션을 핫바에 입력
	else {
		if (KEYDOWN(VK_1)) {
			SOUND->Play("btnPress2");
			color.a = 1.0f;
			isActive = true;
			selectedNum = 1;
			GUI->GetInven()->SetSelectedPotion(selectedPotions[0]);
		}
		if (KEYDOWN(VK_2)) {
			SOUND->Play("btnPress2");
			color.a = 1.0f;
			isActive = true;
			selectedNum = 2;
			GUI->GetInven()->SetSelectedPotion(selectedPotions[1]);
		}
		if (KEYDOWN(VK_3)) {
			SOUND->Play("btnPress2");
			color.a = 1.0f;
			isActive = true;
			selectedNum = 3;
			GUI->GetInven()->SetSelectedPotion(selectedPotions[2]);
		}
		if (KEYDOWN(VK_4)) {
			SOUND->Play("btnPress2");
			color.a = 1.0f;
			isActive = true;
			selectedNum = 4;
			GUI->GetInven()->SetSelectedPotion(selectedPotions[3]);
		}
		if (KEYDOWN(VK_5)) {
			SOUND->Play("btnPress2");
			color.a = 1.0f;
			isActive = true;
			selectedNum = 5;
			GUI->GetInven()->SetSelectedPotion(selectedPotions[4]);
		}
	}
}

void QuickSlot::SlotCheck()
{
	for (int i = 0; i < selectedPotions.size(); i++) {
		if (selectedPotions[i] != NULL) {
			if (selectedPotions[i]->key == -1)
				selectedPotions[i] = NULL;
			if (selectedPotions[i]->stack == 0)
				selectedPotions[i] = NULL;
		}
	}
}

void QuickSlot::Update()
{
	ChangeSlot();
	SlotCheck();
	for (int i = 0; i < QUICKSLOTCOUNT; i++) {
		if (selectedPotions[i] != NULL) {
			potionImages[i]->ChangeImage(selectedPotions[i]->image);
			potionImages[i]->Update();
		}
		else {
			potionImages[i]->ChangeImage(-1);
		}
	}
	if (GUI->GetInven()->isActive) {
		color.a = 1.0f;
		isActive = true;
	}
	if (color.a < 0)
		isActive = false;
}

void QuickSlot::Render()
{
	if (!isActive)
		return;
	shader->Begin();
	shader->SetVector("color", (float*)&color, 4);
	shader->SetTexture("map", panel->GetTexture());
	shader->End();

	World::Update();
	SetWorld();

	shader->Begin();
	shader->SetTexture("map", panel->GetTexture());
	shader->SetVector("color", (float*)&color, 4);
	panel->Render();
	for (int i = 0; i < QUICKSLOTCOUNT; i++) {
		if (potionImages[i]->GetImageNumber() != -1) {
			shader->SetTexture("map", potionImages[i]->GetTexture());
			potionImages[i]->Render();
		}
		if (selectedNum == i + 1) {
			if (potionImages[i]->GetImageNumber() != -1) {
				shader->SetTexture("map", selectImages[i]->GetTexture());
				selectImages[i]->AlphaRender();
			}
		}
	}
	shader->End();
	color.a -= DELTATIME;
}
