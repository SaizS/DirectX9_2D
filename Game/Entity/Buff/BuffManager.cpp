#include "framework.h"
//������ ���� ������ �� ������ ��������. �ߺ� ���� �����ϰ�
BuffManager::BuffManager(Player* player)
{
	//player�� �ɷ�ġ ����
	maxHp = &player->maxHp;
	hp = &player->hp;
	atk = &player->atk;
	def = &player->def;
	speed = &player->speed;
}

BuffManager::BuffManager(Enemy* enemy)
{
	//enemy�� �ɷ�ġ ����
	maxHp = &enemy->maxHp;
	hp = &enemy->hp;
	atk = &enemy->attack;
	def = &enemy->def;
	speed = &enemy->speed;
}

BuffManager::~BuffManager()
{
}

void BuffManager::Update()
{
	World::Update();
	if (buffFXs.size() > 0) { //������ 1���� ���� �� ����

		//���� ȿ��
		for (int i = 0; i < buffFXs.size(); i++) {
			buffFXs[i]->Update(); //���� ������ ��� ������ �� �� ������Ʈ�Ѵ�

			switch ((BuffEffect::Buff_Type)buffFXs[i]->GetEffectNumber()) //�� �� ���� ����Ʈ �ۿ��� �ذ��ؾ��ϴ� ���(�ٸ� ������ ������ ��ġ�� ����)�� ������Ʈ ���Ŀ� �Ŵ������� ó����. �Ʒ��� �׷� ������
			{
			case BuffEffect::ANTIDOTE_1:
				for (int j = 0; j < buffFXs.size(); j++) {
					if (buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_1) { //�ߵ� ����
						buffFXs.erase(buffFXs.begin() + j);
						j--;
					}
				}
				break;
			case BuffEffect::ANTIDOTE_2:
				for (int j = 0; j < buffFXs.size(); j++) {
					if (buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_1 || //�ߵ�, �͵� ����
						buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_2) {
						buffFXs.erase(buffFXs.begin() + j);
						j--;
					}
				}
				break;
			case BuffEffect::ANTIDOTE_3:
				for (int j = 0; j < buffFXs.size(); j++) {
					if (buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_1 || //�ߵ�, �͵�, �ص� ����
						buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_2 ||
						buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_3) {
						buffFXs.erase(buffFXs.begin() + j);
						j--;
					}
				}
				break;
			case BuffEffect::CURE:
				for (int j = 0; j < buffFXs.size(); j++) {
					if (IsDebuff(buffFXs[j]->GetEffectNumber())) { //�طο� �����̻� ����
						buffFXs[j]->EndBuff();
						//EndBuff �Լ��� Ư�� ������ ������� �� ���� ó���� ���ִ� �Լ��� Ȥ�ö� ������ ������ �� �ݵ�� ������־�� �Ѵ�.
						buffFXs.erase(buffFXs.begin() + j);
						j--;
					}
				}
				break;
			case BuffEffect::VOID_EFFECT:
				for (int j = 0; j < buffFXs.size(); j++) {
					if (IsBuff(buffFXs[j]->GetEffectNumber())) { //�̷ο� �����̻� ����
						buffFXs[j]->EndBuff();
						buffFXs.erase(buffFXs.begin() + j);
						j--;
					}
				}
				break;
			default:
				break;
			}
		}

		for (int i = 0; i < buffFXs.size(); i++) {
			if (buffFXs[i]->duration <= 0 && buffFXs[i]->duration != -1) {
				buffFXs[i]->EndBuff();
				buffFXs.erase(buffFXs.begin() + i);
				i--;
			}
		}
	}
}

void BuffManager::Render()
{
	int length = 0;
	Matrix matWorld;
	float startPos = 0;
	for (int i = 0; i < buffFXs.size(); i++)
	{
		startPos -= DATA->GetBuffIconImage(0)->GetSize().x * 0.5f * buffFXs.size();
		D3DXMatrixTranslation(&matWorld, startPos + length + DATA->GetBuffIconImage(0)->GetSize().x * 0.5f, offset.y, 0);
		matWorld *= world;
		DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
		buffFXs[i]->GetIcon()->Render();
		length += DATA->GetBuffIconImage(0)->GetSize().x * 0.5f * buffFXs.size() + DATA->GetBuffIconImage(0)->GetSize().x;
	}
}

void BuffManager::ClearBuff()
{
	for (int i = 0; i < buffFXs.size(); i++) {
		buffFXs[i]->EndBuff();
		buffFXs.erase(buffFXs.begin() + i);
		i--;
	}
}

void BuffManager::SetBuff(int effectNumber)
{
	for (int i = 0; i < buffFXs.size(); i++) {
		if (buffFXs[i]->GetEffectNumber() == effectNumber) {
			buffFXs[i]->EndBuff();
			buffFXs.erase(buffFXs.begin() + i);
			break;
		}
	}
	//Ư�� ���� A ���� B�� ������ ��� ����ó��
	for (int i = 0; i < buffFXs.size(); i++) {
		if (BUFFTYPE::FREEZE == (BUFFTYPE)effectNumber) {
			if ((BUFFTYPE)buffFXs[i]->GetEffectNumber() == BUFFTYPE::BURN) {
				buffFXs[i]->EndBuff();
				buffFXs.erase(buffFXs.begin() + i);
				i--;
			}
		}
		if (BUFFTYPE::BURN == (BUFFTYPE)effectNumber) {
			if ((BUFFTYPE)buffFXs[i]->GetEffectNumber() == BUFFTYPE::FREEZE) {
				buffFXs[i]->EndBuff();
				buffFXs.erase(buffFXs.begin() + i);
				i--;
			}
		}
	}
	BuffEffect* tempEffect = new BuffEffect(effectNumber, maxHp, hp, atk, def, speed);
	buffFXs.push_back(tempEffect);
}

bool BuffManager::BuffCheck(int key)
{
	for (int i = 0; i < buffFXs.size(); i++) {
		if (buffFXs[i]->GetEffectNumber() == key)
			return true;
	}
	return false;
}

bool BuffManager::BuffCheck(BUFFTYPE key)
{
	for (int i = 0; i < buffFXs.size(); i++) {
		if (buffFXs[i]->GetEffectNumber() == (int)key)
			return true;
	}
	return false;
}

bool BuffManager::IsBuff(int key)
{
	switch (key)
	{
	case 7:
	case 8:
	case 9:
	case 10:
	case 12:
	case 23:
	case 27:
		return true;
		break;
	default:
		break;
	}
	return false;
}

bool BuffManager::IsDebuff(int key)
{
	switch (key)
	{
	case 13:
	case 14:
	case 15:
	case 17:
	case 18:
	case 19:
	case 20:
	case 25:
	case 26:
	case 29:
		return true;
		break;
	default:
		break;
	}
	return false;
}