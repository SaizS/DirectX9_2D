#include "framework.h"

Inventory::Inventory() : gold(3000), page(MATERIAL), editMode(false)
{
	isActive = false;
	texture = TEXTURE->Add(L"Resource/Textures/UI/inven.png");
	SetSize({ texture->GetSize().x, texture->GetSize().y });
	SetOffset(-INVEN_X, -INVEN_Y);

	goldText = new ImageFont();
	goldText->SetParent(&world);
	goldText->SetPos(-95, 185);

	itemInfo = new ItemInfo();

	mouseOffset = { INVEN_X, INVEN_Y };

	invenTabs[0] = new InvenTab({ 160, -160 }, 12, mouseOffset);
	invenTabs[0]->canClick = false;
	invenTabs[0]->SetIntValue(0);
	invenTabs[0]->SetIntEvent(bind(&Inventory::SetPage, this, placeholders::_1));
	invenTabs[1] = new InvenTab({ 210, -80 }, 100, mouseOffset);
	invenTabs[1]->SetIntValue(1);
	invenTabs[1]->SetIntEvent(bind(&Inventory::SetPage, this, placeholders::_1));
	invenTabs[2] = new InvenTab({ 210, 0 }, 200, mouseOffset);
	invenTabs[2]->SetIntValue(2);
	invenTabs[2]->SetIntEvent(bind(&Inventory::SetPage, this, placeholders::_1));
	for (int i = 0; i < 3; i++) {
		invenTabs[i]->SetParent(&world);
	}

	for (int j = 0; j < WIDTHCELLCOUNT; j++) { //j - y
		for (int i = 0; i < WIDTHCELLCOUNT; i++) { //i - x
			ItemData tempData;
			ItemSlot* temp = new ItemSlot(tempData, { i * 62 - 124.0f , j * 62 - 120.0f }, mouseOffset);
			temp->SetVoidPtr((void*)(&temp->GetData()));
			temp->SetVoidEvent(bind(&Inventory::SetSelectedItem, this, temp->GetVoidItemData()));
			temp->SetIntValue(i + (j * WIDTHCELLCOUNT));
			temp->SetIntEvent(bind(&Inventory::SelectSlot, this, placeholders::_1));
			temp->SetParent(&world);
			materials.push_back(temp);
		}
	}

	for (int j = 0; j < WIDTHCELLCOUNT; j++) { //j - y
		for (int i = 0; i < WIDTHCELLCOUNT; i++) { //i - x
			ItemData tempData;
			tempData.type = 1;
			ItemSlot* temp = new ItemSlot(tempData, { i * 62 - 124.0f , j * 62 - 120.0f }, mouseOffset);
			temp->SetVoidPtr((void*)(&temp->GetData()));
			temp->SetVoidEvent(bind(&Inventory::SetSelectedItem, this, temp->GetVoidItemData()));
			temp->SetIntValue(i + (j * WIDTHCELLCOUNT));
			temp->SetIntEvent(bind(&Inventory::SelectSlot, this, placeholders::_1));
			temp->SetParent(&world);
			potions.push_back(temp);
		}
	}

	for (int j = 0; j < WIDTHCELLCOUNT; j++) { //j - y
		for (int i = 0; i < WIDTHCELLCOUNT; i++) { //i - x
			ItemData tempData;
			tempData.type = 2;
			ItemSlot* temp = new ItemSlot(tempData, { i * 62 - 124.0f , j * 62 - 120.0f }, mouseOffset);
			temp->SetVoidPtr((void*)(&temp->GetData()));
			temp->SetVoidEvent(bind(&Inventory::SetSelectedItem, this, temp->GetVoidItemData()));
			temp->SetIntValue(i + (j * WIDTHCELLCOUNT));
			temp->SetIntEvent(bind(&Inventory::SelectSlot, this, placeholders::_1));
			temp->SetParent(&world);
			keys.push_back(temp);
		}
	}

	Load();
}

Inventory::~Inventory()
{
	for (ItemSlot* slot : materials)
		delete slot;
	for (ItemSlot* slot : potions)
		delete slot;
	for (ItemSlot* slot : keys)
		delete slot;
	for (InvenTab* index : invenTabs)
		delete index;
	delete itemInfo;
	delete goldText;
}

void Inventory::Update()
{
	if (KEYDOWN('E')) {
		for (ItemSlot* index : materials)
			index->isSelected = false;
		for (ItemSlot* index : potions)
			index->isSelected = false;
		for (ItemSlot* index : keys)
			index->isSelected = false;
		selectItem = NULL;
		selectedNum = 0;

		isActive = !isActive;
		if (isActive)
			SOUND->Play("on");
		else
			SOUND->Play("off");
	}

	if (KEYDOWN(VK_OEM_3)) {
		editMode = !editMode;
		if (editMode)
			SOUND->Play("on");
		else
			SOUND->Play("off");
	}

	if (selectItem != NULL) { //���� �̿��� �������� ������ ��� ������ ���õ� ������ �״�� �����ǰ� ���� ó�� + �� ĭ�� ������ �ٲ��� �ʰ�
		if (selectItem->type == 1 && selectItem->key != -1)
			curPotion = selectItem;
	}

	//���õ� �������� ������ ��� �ֹٿ� ���
	if (curPotion != NULL)
		GUI->GetHotBar()->SetSelectedPotion(curPotion);
	else
		GUI->GetHotBar()->SetSelectedPotion(NULL);

	for (ItemSlot* slot : materials)
		if (slot->GetData().stack <= 0)
			slot->SetData(-1, -1, 0, 0, 0, 0);
	for (ItemSlot* slot : potions)
		if (slot->GetData().stack <= 0)
			slot->SetData(-1, -1, 1, 0, 0, 0);
	for (ItemSlot* slot : keys)
		if (slot->GetData().stack <= 0)
			slot->SetData(-1, -1, 2, 0, 0, 0);

	if (!isActive)
		return;
	World::Update();
	InvenUpdate();
	ItemInfoUpdate();
	Edit();

}

void Inventory::InvenUpdate()
{
	mousePos = WINMOUSEPOS - mouseOffset; //UI�� �ν��ϴ� ���콺 ��ġ�� offset��ŭ �̵�

	for (InvenTab* index : invenTabs)
		index->Update();
	switch (page)
	{
	case Inventory::MATERIAL:
		for (ItemSlot* slot : materials) {
			slot->Update();
		}
		break;
	case Inventory::POTION:
		for (ItemSlot* slot : potions) {
			slot->Update();
		}
		break;
	case Inventory::KEY:
		for (ItemSlot* slot : keys) {
			slot->Update();
		}
		break;
	default:
		break;
	}
	goldText->SetValue(gold);
	goldText->Update();
}

void Inventory::ItemInfoUpdate()
{
	itemInfo->ChangeImage(-1);
	itemInfo->ChangeType(0);
	for (ItemSlot* index : materials) {
		if (index->Collision(mousePos) && page == Inventory::MATERIAL) {
			ItemData temp = index->GetData();
			itemInfo->ChangeImage(temp.key);
			itemInfo->ChangeType(temp.type);
			break;
		}
	}
	for (ItemSlot* index : potions) {
		if (index->Collision(mousePos) && page == Inventory::POTION) {
			ItemData temp = index->GetData();
			itemInfo->ChangeImage(temp.key);
			itemInfo->ChangeType(temp.type);
			break;
		}
	}
	for (ItemSlot* index : keys) {
		if (index->Collision(mousePos) && page == Inventory::KEY) {
			ItemData temp = index->GetData();
			itemInfo->ChangeImage(temp.key);
			itemInfo->ChangeType(temp.type);
			break;
		}
	}
	Vector2 offset = { INVEN_X, INVEN_Y };
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
	if (itemInfo->pos.x > WIN_WIDTH - (DATA->GetItemInfoImage(0)->GetSize().x * 0.5f)) {
		float temp = itemInfo->pos.x - WIN_WIDTH + (DATA->GetItemInfoImage(0)->GetSize().x * 0.5f);
		itemInfo->pos.x -= temp;
	}
}

void Inventory::Edit()
{
	if (selectItem != NULL && editMode) {
		if (KEYPRESS(VK_SHIFT)) {
			if (WHEELUP) {
				SOUND->Play("mouseWheel");
				switch (selectItem->type)
				{
					case 1: {
						if (selectItem->key == -1)
							selectItem->key = 99;
					}
							break;
					case 2: {
						if (selectItem->key == -1)
							selectItem->key = 199;
					}
							break;
					default:
						break;
				}
				int temp = selectItem->key + 1;
				if (temp > 300)
					temp = 300;
				selectItem->key = DATA->GetItemData(temp).key;
				selectItem->image = DATA->GetItemData(temp).image;
				selectItem->effect = DATA->GetItemData(temp).effect;
				selectItem->amount = DATA->GetItemData(temp).amount;
				selectItem->price = DATA->GetItemData(temp).price;
				Save();
			}
			if (WHEELDOWN) {
				SOUND->Play("mouseWheel");
				switch (selectItem->type)
				{
				case 1: {
					if (selectItem->key == 100)
						selectItem->key = 0;
				}
						break;
				case 2: {
					if (selectItem->key == 200)
						selectItem->key = 0;
				}
						break;
				default:
					break;
				}
				int temp = selectItem->key - 1;
				if (temp < -1)
					temp = -1;
				selectItem->key = DATA->GetItemData(temp).key;
				selectItem->image = DATA->GetItemData(temp).image;
				selectItem->effect = DATA->GetItemData(temp).effect;
				selectItem->amount = DATA->GetItemData(temp).amount;
				selectItem->price = DATA->GetItemData(temp).price;
				Save();
			}
		}
		else {
			if (WHEELUP) {
				SOUND->Play("mouseWheel");
				selectItem->stack++;
				Save();
			}
			if (WHEELDOWN) {
				SOUND->Play("mouseWheel");
				selectItem->stack--;
				Save();
			}
		}
	}
}

void Inventory::Render()
{
	if (!isActive)
		return;
	SetWorld();
	for (InvenTab* index : invenTabs)
		index->Render();
	SetWorld();
	texture->AlphaRender();
	switch (page)
	{
	case Inventory::MATERIAL:
		for (ItemSlot* slot : materials)
			slot->Render();
		break;
	case Inventory::POTION:
		for (ItemSlot* slot : potions)
			slot->Render();
		break;
	case Inventory::KEY:
		for (ItemSlot* slot : keys)
			slot->Render();
		break;
	default:
		break;
	}
	goldText->Render();
}

void Inventory::ItemInfoRender()
{
	if (!GUI->GetStore()->GetSellWindow()->isActive &&
		!GUI->GetStore()->GetBuyWindow()->isActive && 
		isActive)
		itemInfo->Render();
}

void Inventory::SetPage(int value)
{
	if (GUI->GetStore()->GetSellWindow()->isActive)
		return;
	SOUND->Play("pushTab");
	invenTabs[0]->SetPos(210, -160);
	invenTabs[0]->canClick = true;
	invenTabs[1]->SetPos(210, -80);
	invenTabs[1]->canClick = true;
	invenTabs[2]->SetPos(210, 0);
	invenTabs[2]->canClick = true;

	page = (Inventory::Page)value;

	switch (page)
	{
	case Inventory::MATERIAL:
		invenTabs[0]->SetPos(160, -160);
		invenTabs[0]->canClick = false;
		break;
	case Inventory::POTION:
		invenTabs[1]->SetPos(160, -80);
		invenTabs[1]->canClick = false;
		break;
	case Inventory::KEY:
		invenTabs[2]->SetPos(160, 0);
		invenTabs[2]->canClick = false;
		break;
	default:
		break;
	}
}
void Inventory::SelectSlot(int value)
{
	if (GUI->GetStore()->GetSellWindow()->isActive)
		return;
	if (isSelect) {
		for (ItemSlot* index : materials)
			index->isSelected = false;
		for (ItemSlot* index : potions)
			index->isSelected = false;
		for (ItemSlot* index : keys)
			index->isSelected = false;
		if (selectedNum == value && selectdPage == page) {
			isSelect = false;
			selectItem = NULL;
		}
		else {
			selectedNum = value;
			switch (page)
			{
			case Inventory::MATERIAL:
				selectdPage = MATERIAL;
				materials[value]->isSelected = true;
				break;
			case Inventory::POTION: {
				selectdPage = POTION;
				potions[value]->isSelected = true;
			}
				break;
			case Inventory::KEY:
				selectdPage = KEY;
				keys[value]->isSelected = true;
				break;
			default:
				break;
			}
			//������ �����ִ� ��� �Ǹ� ��ư ��� ����
			if (GUI->GetStore()->isActive && !GUI->GetStore()->GetBuyWindow()->isActive && selectItem->key != -1) {
				GUI->GetStore()->GetSellWindow()->SetActive({ WIN_HALFWIDTH, STORE_Y }, selectItem);
				SOUND->Play("btnPress");
				return;
			}
			//�����ϰ� �����ִ� ��� ��� ���� ��� ����
			if (GUI->GetCauldron()->isActive) {
				if (selectItem->key > 1 && page == Inventory::MATERIAL) {
					GUI->GetCauldron()->InsertMaterial(selectItem);
					SOUND->Play("water"); //��� �ִ� �Ҹ�
					ClearSelectItem();
					return;
				}
				else {
					SOUND->Play("buzzer");
					ClearSelectItem();
					return;
				}
			}
			SOUND->Play("btnPress");
		}
	}
	else {
		selectedNum = value;
		switch (page)
		{
		case Inventory::MATERIAL:
			selectdPage = MATERIAL;
			materials[value]->isSelected = true;
			break;
		case Inventory::POTION: {
			selectdPage = POTION;
			potions[value]->isSelected = true;
		}
			break;
		case Inventory::KEY:
			selectdPage = KEY;
			keys[value]->isSelected = true;
			break;
		default:
			break;
		}
		isSelect = true;
		//������ �����ִ� ��� �Ǹ� ��ư ��� ����
		if (GUI->GetStore()->isActive && !GUI->GetStore()->GetBuyWindow()->isActive && selectItem->key != -1) {
			GUI->GetStore()->GetSellWindow()->SetActive({ WIN_HALFWIDTH, STORE_Y }, selectItem);
			SOUND->Play("btnPress");
			return;
		}
		//�����ϰ� �����ִ� ��� ��� ���� ��� ����
		if (GUI->GetCauldron()->isActive) {
			if (selectItem->key > 1 && page == Inventory::MATERIAL) {
				GUI->GetCauldron()->InsertMaterial(selectItem);
				SOUND->Play("water"); //��� �ִ� �Ҹ�
				ClearSelectItem();
				return;
			}
			else {
				SOUND->Play("buzzer");
				ClearSelectItem();
				return;
			}
		}
		SOUND->Play("btnPress");
	}
}

void Inventory::ClearSelectItem()
{
	for (ItemSlot* index : materials)
		index->isSelected = false;
	for (ItemSlot* index : potions)
		index->isSelected = false;
	for (ItemSlot* index : keys)
		index->isSelected = false;
	isSelect = false;
	selectedNum = 0;
	selectItem = NULL;
}

bool Inventory::ItemCheck(int key, int stack)
{
	int temp = 0;
	for (ItemSlot* slot : materials) {
		if (slot->GetData().key == key) {
			temp += (int)slot->GetData().stack;
		}
	}
	for (ItemSlot* slot : potions) {
		if (slot->GetData().key == key) {
			temp += (int)slot->GetData().stack;
		}
	}
	for (ItemSlot* slot : keys) {
		if (slot->GetData().key == key) {
			temp += (int)slot->GetData().stack;
		}
	}
	if (temp >= stack)
		return true;
	return false;
}

int Inventory::ItemStackCheck(int key)
{
	int temp = 0;
	for (ItemSlot* slot : materials) {
		if (slot->GetData().key == key) {
			temp += (int)slot->GetData().stack;
		}
	}
	for (ItemSlot* slot : potions) {
		if (slot->GetData().key == key) {
			temp += (int)slot->GetData().stack;
		}
	}
	for (ItemSlot* slot : keys) {
		if (slot->GetData().key == key) {
			temp += (int)slot->GetData().stack;
		}
	}
	return temp;
}

void Inventory::OpenInven()
{
	for (ItemSlot* index : materials)
		index->isSelected = false;
	for (ItemSlot* index : potions)
		index->isSelected = false;
	for (ItemSlot* index : keys)
		index->isSelected = false;
	selectItem = NULL;
	selectedNum = 0;

	if (isActive == false)
		SOUND->Play("on");
	isActive = true;
}

void Inventory::CloseInven()
{
	for (ItemSlot* index : materials)
		index->isSelected = false;
	for (ItemSlot* index : potions)
		index->isSelected = false;
	for (ItemSlot* index : keys)
		index->isSelected = false;
	selectItem = NULL;
	selectedNum = 0;

	if (isActive == true)
		SOUND->Play("off");
	isActive = false;
}

void Inventory::DeleteItem(int key, int stack)
{
	for (ItemSlot* slot : materials) {
		if (slot->GetData().key == key) {
			if (slot->GetData().stack >= stack) {
				slot->AddStack(-stack);
				return;
			}
		}
	}
	for (ItemSlot* slot : potions) {
		if (slot->GetData().key == key) {
			if (slot->GetData().stack >= stack) {
				slot->AddStack(-stack);
				return;
			}
		}
	}
	for (ItemSlot* slot : keys) {
		if (slot->GetData().key == key) {
			if (slot->GetData().stack >= stack) {
				slot->AddStack(-stack);
				return;
			}
		}
	}
}

void Inventory::GetItem(int key, int stack)
{
	//������ �˸�
	ItemData item;
	item = DATA->GetItemData(key);
	switch (item.type)
	{
	case 0: {
		ItemSlot* nullSlot = NULL; //������ �������� ���� �� ����
		for (ItemSlot* slot : materials) {
			if (slot->GetData().key == -1) {
				nullSlot = slot;
				break;
			}
		}
		if (nullSlot == NULL) {
			SOUND->Play("buzzer");
			printf("�κ��丮 ���� \n");
			return;
		}
		SOUND->Play("itemGet2");
		GUI->GetGWM()->AddWindow(item.key, 4);
		nullSlot->SetData(DATA->GetItemData(item.key));
		nullSlot->SetStack(stack);
		InvenSort();
		Save();
	}
	break;
			//����
	case 1: {
		ItemSlot* nullSlot = NULL; //������ �������� ���� �� ����
		for (ItemSlot* slot : potions) {
			if (slot->GetData().key == -1) {
				nullSlot = slot;
				break;
			}
		}
		if (nullSlot == NULL) {
			SOUND->Play("buzzer");
			printf("�κ��丮 ���� \n");
			return;
		}
		SOUND->Play("itemGet2");
		GUI->GetGWM()->AddWindow(item.key, 4);
		nullSlot->SetData(DATA->GetItemData(item.key));
		nullSlot->SetStack(stack);
		InvenSort();
		Save();
	}
	break;
			//�߿�
	case 2: {
		ItemSlot* nullSlot = NULL; //������ �������� ���� �� ����
		for (ItemSlot* slot : keys) {
			if (slot->GetData().key == -1) {
				nullSlot = slot;
				break;
			}
		}

		if (nullSlot == NULL) {
			SOUND->Play("buzzer");
			printf("�κ��丮 ���� \n");
			return;
		}
		SOUND->Play("itemGet2");
		GUI->GetGWM()->AddWindow(item.key, 4);
		nullSlot->SetData(DATA->GetItemData(item.key));
		nullSlot->SetStack(stack);
		InvenSort();
		Save();
	}
	break;
	default:
		break;
	}
}

void Inventory::BuyItem(void* item, UINT stack)
{
	ItemData* buyItem = (ItemData*)item;
	if (gold < (UINT)(buyItem->stack * stack)) {
		SOUND->Play("buzzer");
		printf("������ ���� \n");
		return;
	}

	switch (buyItem->type)
	{
		//���
	case 0: {
		ItemSlot* nullSlot = NULL; //������ �������� ���� �� ����
		for (ItemSlot* slot : materials) {
			if (slot->GetData().key == -1) {
				nullSlot = slot;
				break;
			}
		}

		if (nullSlot == NULL) {
			SOUND->Play("buzzer");
			printf("�κ��丮 ���� \n");
			return;
		}

		SOUND->Play("cash");
		gold -= (UINT)(buyItem->stack * stack);
		GUI->GetGWM()->AddWindow(buyItem->key, 4);
		nullSlot->SetData(DATA->GetItemData(buyItem->key));
		nullSlot->SetStack(stack);
		GUI->GetStore()->GetBuyWindow()->Inactive();
		InvenSort();
		Save();
	}
		break;
		//����
	case 1: {
		ItemSlot* nullSlot = NULL; //������ �������� ���� �� ����
		for (ItemSlot* slot : potions) {
			if (slot->GetData().key == -1) {
				nullSlot = slot;
				break;
			}
		}

		if (nullSlot == NULL) {
			SOUND->Play("buzzer");
			printf("�κ��丮 ���� \n");
			return;
		}

		SOUND->Play("cash");
		gold -= (UINT)(buyItem->stack * stack);
		GUI->GetGWM()->AddWindow(buyItem->key, 4);
		nullSlot->SetData(DATA->GetItemData(buyItem->key));
		nullSlot->SetStack(stack);
		GUI->GetStore()->GetBuyWindow()->Inactive();
		InvenSort();
		Save();
	}
		break;
		//�߿�
	case 2: {
		ItemSlot* nullSlot = NULL; //������ �������� ���� �� ����
		for (ItemSlot* slot : keys) {
			if (slot->GetData().key == -1) {
				nullSlot = slot;
				break;
			}
		}

		if (nullSlot == NULL) {
			SOUND->Play("buzzer");
			printf("�κ��丮 ���� \n");
			return;
		}

		SOUND->Play("cash");
		gold -= (UINT)(buyItem->stack * stack);
		GUI->GetGWM()->AddWindow(buyItem->key, 4);
		nullSlot->SetData(DATA->GetItemData(buyItem->key));
		nullSlot->SetStack(stack);
		GUI->GetStore()->GetBuyWindow()->Inactive();
		InvenSort();
		Save();
	}
		break;
	default:
		break;
	}
}

void Inventory::SellItem(void* item, UINT stack)
{
	ItemData* sellItem = (ItemData*)item;
	if (sellItem->price == 0) {//������ 0�� �������� ���ǰ
		SOUND->Play("buzzer");
		printf("���ǰ�� �Ǹ��� �� ����\n");
		return;
	}
	SOUND->Play("coin");
	gold += sellItem->price * stack * 0.2f;
	sellItem->stack -= stack;
	if (sellItem->stack <= 0) {
		sellItem->key = -1;
		sellItem->image = -1;
		sellItem->effect = 0;
		sellItem->amount = 0;
		sellItem->stack = 0;
		sellItem->price = 0;
	}
	GUI->GetStore()->GetSellWindow()->Inactive();
	InvenSort();
	Save();
}

void Inventory::InvenSort()
{
	vector<ItemData> tempItemList;
	vector<ItemData> tempVector;
	ClearSelectItem();
	//��� ����
	//material ������ ������ �����͸� �ӽ� ���Ϳ� ����.
	for (ItemSlot* slot : materials)
		tempItemList.push_back(slot->GetData());
	//�ӽ� ���͸� key���� ���� ������������ ����. materials�� ���� �ʴ� ������ ���� ��ü�� ���ĵǾ� ������ ���� ������!
	sort(tempItemList.begin(), tempItemList.end(), Compare);
	//Ű ���� -1�̸� �� ����. ���Ŀ� ���� �� ������ ���� �� �տ� �������״� �� ������ ������ �����۵��� �ӽ� ���Ϳ� �־��ش�
	for (ItemData data : tempItemList) {
		if (data.key != -1) {
			tempVector.push_back(data);
		}
	}
	//�ӽ� ���� ���� �����۵��� ���ϸ� ���� Ű���� ���� �������� ��� ��ģ��
	if (tempVector.size() >= 2) {
		for (int i = 1; i < tempVector.size(); i++) {
			if (tempVector[i - 1].key == tempVector[i].key && tempVector[i - 1].key != -1 && tempVector[i - 1].stack < 99) {
				UINT stackA = tempVector[i - 1].stack;
				UINT stackB = tempVector[i].stack;
				UINT result = stackA + stackB;
				if (result > 99) { //�� �������� ���� ���� ���� 99�� �ʰ��� ���
					result -= 99;
					tempVector[i - 1].stack = 99;
					tempVector[i].stack = result;
				}
				else { //�� �������� ������ ���� ���� 99�� �ʰ����� ���� ���
					tempVector[i - 1].stack = result;
					tempVector.erase(tempVector.begin() + i);
					//�ش� ������ �����͸� �����
				}
			}
		}

		for (ItemSlot* slot : materials) {
			slot->SetData(-1, -1, 0, 0, 0, 0, 0);
		}
		for (int i = 0; i < tempVector.size(); i++) {
			materials[i]->SetData(tempVector[i]);
		}
	}
	//�� ���ĵ� �ӽ� ���͸� ������ ���Կ� ���ʴ�� �ֱ� �� ��� ������ ������ �����͸� �ʱ�ȭ�����ش�.
	tempItemList.clear();
	tempVector.clear();

	//���� ����
	for (ItemSlot* slot : potions)
		tempItemList.push_back(slot->GetData());
	sort(tempItemList.begin(), tempItemList.end(), Compare);
	for (ItemData data : tempItemList) {
		if (data.key != -1) {
			tempVector.push_back(data);
		}
	}
	if (tempVector.size() >= 2) {
		for (int i = 1; i < tempVector.size(); i++) {
			if (tempVector[i - 1].key == tempVector[i].key && tempVector[i - 1].key != -1 && tempVector[i - 1].stack < 99) {
				UINT stackA = tempVector[i - 1].stack;
				UINT stackB = tempVector[i].stack;
				UINT result = stackA + stackB;
				if (result > 99) {
					result -= 99;
					tempVector[i - 1].stack = 99;
					tempVector[i].stack = result;
				}
				else {
					tempVector[i - 1].stack = result;
					tempVector.erase(tempVector.begin() + i);
				}
			}
		}
		int tempPotionKey = -1;
		vector<int> tempSlotPotion(5);
		fill(tempSlotPotion.begin(), tempSlotPotion.end(), -1); //fill �Լ� Ư�� ����A���� B���� Ư�� ��ҷ� ä���
		if (curPotion != NULL) //������ ������ �ִٸ� �� ������ Ű���� �ӽ� ������ ����
			tempPotionKey = curPotion->key;

		for (int i = 0; i < QUICKSLOTCOUNT; i++) { //����� ������ �ִٸ� ~~
			if (GUI->GetQuickSlot()->GetSelectedPotion(i) != NULL)
				tempSlotPotion[i] = GUI->GetQuickSlot()->GetSelectedPotion(i)->key;
		}

		for (ItemSlot* slot : potions) {
			slot->SetData(-1, -1, 0, 0, 0, 0, 0);
		}
		for (int i = 0; i < tempVector.size(); i++) {
			potions[i]->SetData(tempVector[i]);
		}
		if (tempPotionKey != -1) { //������ ������ �ִ� ���
			for (ItemSlot* slot : potions) { //���� �� �ش� Ű ���� �ش��ϴ� ������ �����Ϳ� ������Ŵ
				if (slot->GetData().key == tempPotionKey) {
					curPotion = slot->GetDataRef();
					break;
				}
			}
		}

		for (int i = 0; i < QUICKSLOTCOUNT; i++) {
			if (tempSlotPotion[i] != -1) { //����� ������ �ִ� ���
				for (ItemSlot* slot : potions) { //���� �� �ش� Ű ���� �ش��ϴ� ������ �����Ϳ� ������Ŵ
					if (slot->GetData().key == tempSlotPotion[i]) {
						GUI->GetQuickSlot()->SetSelectedPotion(slot->GetDataRef(), i);
						break;
					}
				}
			}
		}
	}

	tempItemList.clear();
	tempVector.clear();

	for (ItemSlot* slot : keys)
		tempItemList.push_back(slot->GetData());
	sort(tempItemList.begin(), tempItemList.end(), Compare);
	for (ItemData data : tempItemList) {
		if (data.key != -1) {
			tempVector.push_back(data);
		}
	}
	if (tempVector.size() >= 2) {
		for (int i = 1; i < tempVector.size(); i++) {
			if (tempVector[i - 1].key == tempVector[i].key && tempVector[i - 1].key != -1 && tempVector[i - 1].stack < 99) {
				UINT stackA = tempVector[i - 1].stack;
				UINT stackB = tempVector[i].stack;
				UINT result = stackA + stackB;
				if (result > 99) {
					result -= 99;
					tempVector[i - 1].stack = 99;
					tempVector[i].stack = result;
				}
				else {
					tempVector[i - 1].stack = result;
					tempVector.erase(tempVector.begin() + i);
				}
			}
		}
		for (ItemSlot* slot : keys) {
			slot->SetData(-1, -1, 0, 0, 0, 0, 0);
		}
		for (int i = 0; i < tempVector.size(); i++) {
			keys[i]->SetData(tempVector[i]);
		}
	}

	tempItemList.clear();
	tempVector.clear();
}

void Inventory::Save()
{
	BinaryWriter* w = new BinaryWriter(L"Data/Save/inven.item");

	w->Int(gold); //������ ����

	vector<ItemData> datas; //������ ����� ����
	//��� -> ���� -> �߿� ������
	for (ItemSlot* item : materials)
		datas.push_back(item->GetData());
	for (ItemSlot* item : potions)
		datas.push_back(item->GetData());
	for (ItemSlot* item : keys)
		datas.push_back(item->GetData());

	for (ItemData data : datas)
	{
		w->Int(data.key);
		w->Int(data.image);
		w->Int(data.type);
		w->Int(data.effect);
		w->Int(data.amount);
		w->UInt(data.price);
		w->UInt(data.stack);
	}

	delete w;
}
void Inventory::Load()
{
	wstring path = L"Data/Save/inven.item";
	if (!BinaryReader::IsExistFile(path)) { //�ε��� �����Ͱ� ���ٸ� �ε带 �������� ���� (�� ����� ��)
		ItemData data;
		
		data = DATA->GetItemData(0);
		data.stack = 5;
		materials[0]->SetData(data);

		data = DATA->GetItemData(1);
		data.stack = 5;
		materials[1]->SetData(data);

		data = DATA->GetItemData(2);
		data.stack = 3;
		materials[2]->SetData(data);

		data = DATA->GetItemData(12);
		data.stack = 3;
		materials[3]->SetData(data);

		data = DATA->GetItemData(101);
		data.stack = 10;
		potions[0]->SetData(data);

		data = DATA->GetItemData(124);
		data.stack = 10;
		potions[1]->SetData(data);

		data = DATA->GetItemData(130);
		data.stack = 10;
		potions[2]->SetData(data);

		Save();

		return;
	}

	BinaryReader* r = new BinaryReader(path);

	gold = r->Int(); //������ �ε�

	for (int i = 0; i < 25; i++)
	{
		ItemData data;
		data.key = r->Int();
		data.image = r->Int();
		data.type = r->Int();
		data.effect = r->Int();
		data.amount = r->Int();
		data.price = r->UInt();
		data.stack = r->UInt();

		materials[i]->SetData(data);
	}

	for (int i = 0; i < 25; i++)
	{
		ItemData data;
		data.key = r->Int();
		data.image = r->Int();
		data.type = r->Int();
		data.effect = r->Int();
		data.amount = r->Int();
		data.price = r->UInt();
		data.stack = r->UInt();

		potions[i]->SetData(data);
	}

	for (int i = 0; i < 25; i++)
	{
		ItemData data;
		data.key = r->Int();
		data.image = r->Int();
		data.type = r->Int();
		data.effect = r->Int();
		data.amount = r->Int();
		data.price = r->UInt();
		data.stack = r->UInt();

		keys[i]->SetData(data);
	}

	delete r;
}

bool Inventory::Compare(ItemData val1, ItemData val2)
{
	return val1.key < val2.key;
}
