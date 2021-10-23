#include "framework.h"
//도가니 저장
Cauldron::Cauldron() : pollutionGauge(0.0f), quantity(0), helpActive(false), curBottle(0)
{
	texture = TEXTURE->Add(L"Resource/Textures/UI/cauldron.png");
	SetSize({ texture->GetSize().x, texture->GetSize().y });
	SetOffset(-CAULDRON_X, -CAULDRON_Y);

	itemInfo = new ItemInfo();

	helpBtn = new UIButton(TEXTURE->Add(L"Resource/Textures/UI/help.png"), { 155, 180 }, { 0, 0 });
	helpBtn->SetParent(&world);
	helpTexture = TEXTURE->Add(L"Resource/Textures/UI/cauldronInfo.png");
	helpWorld = new World();
	helpWorld->SetParent(&world);

	pollutionText = new ImageFont(2.0f, ImageFont::RIGHT);
	pollutionText->SetParent(&world);
	pollutionText->SetPos(127, -12);

	quantityText = new ImageFont(2.0f, ImageFont::RIGHT);
	quantityText->SetParent(&world);
	quantityText->SetPos(127, 20);

	mouseOffset = { CAULDRON_X, CAULDRON_Y };

	for (int i = 0; i < 2; i++) { //i - x
		ItemData tempData;
		tempData.key = i;
		tempData.image = i;
		ItemSlot* temp = new ItemSlot(tempData, { i * 74 + 76.0f , -135.0f }, mouseOffset);
		temp->SetIntValue(i);
		temp->SetIntEvent(bind(&Cauldron::SelectBottle, this, placeholders::_1));
		temp->SetParent(&world);
		selectBottle.push_back(temp);
	}
	ItemData tempData;
	tempData.key = 1;
	tempData.image = 1;
	tempData.type = 1;
	tempData.effect = 1;
	resultPotion = new ItemSlot(tempData, { -1.0f, 158.0f }, mouseOffset);
	resultPotion->SetVoidPtr((void*)(&resultPotion->GetData()));
	resultPotion->SetVoidEvent(bind(&Cauldron::ExtractPotion, this, resultPotion->GetVoidItemData()));
	resultPotion->SetParent(&world);

}

Cauldron::~Cauldron()
{
	for (ItemSlot* slot : selectBottle)
		delete slot;
	delete resultPotion;
	delete itemInfo;
}

void Cauldron::Update()
{
	mousePos = WINMOUSEPOS - mouseOffset;

	if (!*invenActive) {
		isActive = false;
		selectItem = NULL;
		selectBottle[0]->isSelected = true;
		selectBottle[1]->isSelected = false;
	}

	if (!*invenActive)
		isActive = false;
	if (!isActive)
		return;

	World::Update();
	for (ItemSlot* index : selectBottle)
		index->Update();
	resultPotion->Update();
	if (quantity <= 0) {
		curEffect.clear();
		pollutionGauge = 0;
		quantity = 0;
		resultPotion->SetData(-1, -1, 1, 0, 0, 0, 0);
	}
	pollutionText->SetValue((UINT)pollutionGauge);
	pollutionText->SetColor(0xffffffff);
	if (pollutionGauge == 100.0f) {
		pollutionText->SetColor(0xff26a64a);
	}
	pollutionText->Update();
	quantityText->SetValue(quantity);
	quantityText->Update();
	helpBtn->Update();
	helpActive = false;
	if (helpBtn->Collision(mousePos)) {
		helpActive = true;
		//Vector2 size = helpTexture->GetSize();
		//helpWorld->SetPos(WINMOUSEPOS - size);
	}
	ResultUpdate();
	ItemInfoUpdate();
}

void Cauldron::ResultUpdate()
{
	resultPotion->SetData(-1, -1, 1, 0, 0, 0, 0);
	//효과 벡터를 정렬
	sort(curEffect.begin(), curEffect.end(), Compare);

	if (curEffect.size() > 1) { //벡터에 인자가 2개 이상인 경우
		map<int, int> temp; //map
		int mostValue = 0; //가장 많은 값을 저장할 변수
		int resultEffect = 0;
		for (int i = 0; i < curEffect.size(); i++) {
			if (curEffect[i] == 0) {
				curEffect.erase(curEffect.begin() + i);
				continue;
			}
			if (i == 0) //최초 실행시 결과물의 효과는 최초로 넣은 재료의 효과를 따라감
				resultEffect = curEffect[i];
			if (temp.count(curEffect[i]) == 0) //해당 효과가 없다면
				temp[curEffect[i]] = 0; // i번째 인자에 현재 i번 효과를 넣음
			else //이미 있는 경우
				temp[curEffect[i]]++;
			if (mostValue < temp[curEffect[i]]) {//set안에 있는 curEffect[i]의 key를 가진 인자를 전부 센 후, 현재 mostValue의 값보다 큰 경우 그 값을 변경
				mostValue = temp[curEffect[i]];
				resultEffect = curEffect[i];
			}
		}
		//반복문이 다 돌았으면 mostValue에 가장 많은 효과가 저장되어 있을 것임.
		if (curBottle == 0) {
			ItemData result = DATA->GetItemData((resultEffect * 2 - 2) + 100);
			resultPotion->SetData(result);
			resultPotion->SetStack(0);
		}
		else {
			ItemData result = DATA->GetItemData((resultEffect * 2 - 1) + 100);
			resultPotion->SetData(result);
			resultPotion->SetStack(0);
		}
	}
	else if (curEffect.size() == 1) {
		if (curBottle == 0) {
			ItemData result = DATA->GetItemData((curEffect[0] * 2 - 2) + 100);
			resultPotion->SetData(result);
			resultPotion->SetStack(0);
		}
		else {
			ItemData result = DATA->GetItemData((curEffect[0] * 2 - 1) + 100);
			resultPotion->SetData(result);
			resultPotion->SetStack(0);
		}
	}
	else {
		resultPotion->SetData(-1, -1, 1, 0, 0, 0, 0);
	}
	if (pollutionGauge >= 100) { //선택된 병의 종류가 없을 경우 결과물은 NULL로
		if (curBottle == 0) {
			ItemData temp = DATA->GetItemData(146);
			resultPotion->SetData(temp);
			resultPotion->SetStack(0);
		}
		else {
			ItemData temp = DATA->GetItemData(147);
			resultPotion->SetData(temp);
			resultPotion->SetStack(0);
		}
	}
	if (!selectBottle[0]->isSelected && !selectBottle[1]->isSelected) //선택된 병의 종류가 없을 경우 결과물은 NULL로
		resultPotion->SetData(-1, -1, 1, 0, 0, 0, 0);
}

void Cauldron::ItemInfoUpdate()
{
	itemInfo->ChangeImage(-1);
	itemInfo->ChangeType(0);
	if (resultPotion->Collision(mousePos)) {
		ItemData temp = resultPotion->GetData();
		itemInfo->ChangeImage(temp.key);
		itemInfo->ChangeType(temp.type);
	}
	Vector2 offset = { CAULDRON_X, CAULDRON_Y };
	switch (itemInfo->GetType())
	{
	case 0:
		itemInfo->SetPos(mousePos + offset + (DATA->GetItemInfoImage(0)->GetSize() * 0.5f));
		break;
	case 1:
		itemInfo->SetPos(mousePos + offset + (DATA->GetItemInfoImage(100)->GetSize() * 0.5f));
		break;
	case 2:
		itemInfo->SetPos(mousePos + offset + (DATA->GetItemInfoImage(200)->GetSize() * 0.5f));
		break;
	default:
		break;
	}
	if (itemInfo->pos.x > WIN_WIDTH - (DATA->GetItemInfoImage(200)->GetSize().x * 0.5f)) {
		float temp = itemInfo->pos.x - WIN_WIDTH + (DATA->GetItemInfoImage(200)->GetSize().x * 0.5f);
		itemInfo->pos.x -= temp;
	}
}

void Cauldron::Render()
{
	if (!isActive)
		return;
	SetWorld();
	texture->AlphaRender();
	for (ItemSlot* slot : selectBottle)
		slot->Render();
	resultPotion->Render();
	pollutionText->Render();
	quantityText->Render();
	helpBtn->Render();
	if (helpActive) {
		helpWorld->Update();
		helpWorld->SetWorld();
		helpTexture->AlphaRender();
	}
}

void Cauldron::ItemInfoRender()
{
	if (isActive && !helpActive)
		itemInfo->Render();
}

void Cauldron::OpenCauldron()
{
	if (isActive)
		return;
	isActive = true;
	GUI->GetInven()->OpenInven();
	GUI->GetInven()->ClearSelectItem();
	selectItem = NULL;
	curBottle = 0;
	selectBottle[0]->isSelected = true;
	selectBottle[1]->isSelected = false;
}

void Cauldron::SelectBottle(int value)
{
	SOUND->Play("btnPress");
	curBottle = value;
	if (value == 0) {
		selectBottle[0]->isSelected = true;
		selectBottle[1]->isSelected = false;
	}
	else {
		selectBottle[0]->isSelected = false;
		selectBottle[1]->isSelected = true;
	}
}

void Cauldron::InsertMaterial(ItemData* item)
{
	item->stack--; //현재 아이템의 소지량을 1 감소
	//효과 주입
	if (item->effect != 0)
		curEffect.push_back(item->effect);

	//분량 주입
	switch (item->key)
	{
	case 20:
		if (OP::Random(1, 10) < 3) {
			SOUND->Play("explosion");
			//폭발 소리
			quantity = 0;
		}
		break;
	case 21:
		if (OP::Random(1, 10) < 4) {
			SOUND->Play("explosion");
			//폭발 소리
			quantity = 0;
		}
		break;
	default:
		break;
	}
	quantity += (item->amount);

	//오염도 주입
	float temp = 5.0f; //기본값 5%
	switch (item->key)
	{
	case 34:
		temp *= 2.0f;
		break;
	case 42:
		temp *= 2.0f;
		break;
	case 43:
		temp *= 2.0f;
		break;
	case 44:
		temp *= 4.0f;
		break;
	case 45:
		temp *= 2.0f;
		break;
	case 47:
		temp *= 2.0f;
		break;
	case 52:
		temp *= 4.0f;
		break;
	case 53:
		temp *= 4.0f;
		break;
	case 54:
		temp *= 6.0f;
		break;
	case 55:
		temp *= 4.0f;
		break;
	case 62:
		SOUND->Play("heal");
		quantity *= 2;
		break;
	case 63:
		SOUND->Play("cure");
		temp = 0;
		pollutionGauge = 0;
		break;
	case 64:
		SOUND->Play("void");
		for (int i = 0; i < curEffect.size(); i++) {
			curEffect.erase(curEffect.begin() + i);
			i--;
		}
		curEffect.push_back(OP::Random(1, 28));
	default:
		break;
	}

	pollutionGauge += temp;
	if (pollutionGauge > 100)
		pollutionGauge = 100.0f;
}

void Cauldron::ExtractPotion(void* value)
{
	if (value != NULL) {
		ItemData* temp = (ItemData*)value;
		selectItem = temp;
		
		//인벤토리 빈 칸 검사

		if (KEYPRESS(VK_SHIFT)) {
			if (quantity >= 10) {
				quantity -= 10;
				if (curBottle == 0) {
					if (!GUI->GetInven()->ItemCheck(0, 10)) { //0번 아이템이 10개 이상 존재하는가
						SOUND->Play("buzzer");
						return;
					}
				}
				else {
					if (!GUI->GetInven()->ItemCheck(1, 10)) { //1번 아이템이 10개 이상 존재하는가
						SOUND->Play("buzzer");
						return;
					}
				}
				SOUND->Play("extract");
				if(curBottle == 0)
					GUI->GetInven()->DeleteItem(0, 10);
				else
					GUI->GetInven()->DeleteItem(1, 10);
				GUI->GetInven()->GetItem(selectItem->key, 10);

			}
			else if (quantity > 0) { //어중간한 양일 때
				int curBottleStack;
				if (curBottle == 0)
					curBottleStack = GUI->GetInven()->ItemStackCheck(0);
				else 
					curBottleStack = GUI->GetInven()->ItemStackCheck(1);

				if (curBottleStack < quantity) { //현재 분량보다 가진 병의 갯수가 많은 경우
					if (curBottle == 0) //병 예외처리
						if (!GUI->GetInven()->ItemCheck(0, curBottleStack)) {
							SOUND->Play("buzzer");
							return;
						}
						else
							if (!GUI->GetInven()->ItemCheck(1, curBottleStack)) {
								SOUND->Play("buzzer");
								return;
							}
					SOUND->Play("extract");
					if (curBottle == 0)
						GUI->GetInven()->DeleteItem(0, curBottleStack);
					else
						GUI->GetInven()->DeleteItem(1, curBottleStack);
					GUI->GetInven()->GetItem(selectItem->key, curBottleStack);
					quantity = curBottleStack;

				}
				else {
					if (curBottle == 0) //병 예외처리
						if (!GUI->GetInven()->ItemCheck(0, quantity)) {
							SOUND->Play("buzzer");
							return;
						}
					else
						if (!GUI->GetInven()->ItemCheck(1, quantity)) {
							SOUND->Play("buzzer");
							return;
						}
					SOUND->Play("extract");
					if (curBottle == 0)
						GUI->GetInven()->DeleteItem(0, quantity);
					else
						GUI->GetInven()->DeleteItem(1, quantity);
					GUI->GetInven()->GetItem(selectItem->key, quantity);
					quantity = 0;
				}
			} else
				SOUND->Play("buzzer");
		}
		else {
			if (quantity >= 1) {
				if (curBottle == 0) //병 예외처리
					if (!GUI->GetInven()->ItemCheck(0, 1)) {
						SOUND->Play("buzzer");
						return;
					}
					else
						if (!GUI->GetInven()->ItemCheck(1, 1)) {
							SOUND->Play("buzzer");
							return;
						}
				quantity--;
				SOUND->Play("extract");
				if (curBottle == 0)
					GUI->GetInven()->DeleteItem(0, 1);
				else
					GUI->GetInven()->DeleteItem(1, 1);
				GUI->GetInven()->GetItem(selectItem->key);
			}
			else {
				SOUND->Play("buzzer");
			}
		}
	}
	else
		return;
}

bool Cauldron::Compare(int val1, int val2)
{
	return val1 < val2;
}

