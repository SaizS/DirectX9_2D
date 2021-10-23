#include "framework.h"
//다음에 버프 구현할 땐 맵으로 구현하자. 중복 방지 쉽게하게
BuffManager::BuffManager(Player* player)
{
	//player의 능력치 연동
	maxHp = &player->maxHp;
	hp = &player->hp;
	atk = &player->atk;
	def = &player->def;
	speed = &player->speed;
}

BuffManager::BuffManager(Enemy* enemy)
{
	//enemy의 능력치 연동
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
	if (buffFXs.size() > 0) { //버프가 1개라도 있을 때 실행

		//버프 효과
		for (int i = 0; i < buffFXs.size(); i++) {
			buffFXs[i]->Update(); //버프 벡터의 모든 버프를 한 번 업데이트한다

			switch ((BuffEffect::Buff_Type)buffFXs[i]->GetEffectNumber()) //그 중 버프 이펙트 밖에서 해결해야하는 기능(다른 버프에 영향을 끼치는 버프)은 업데이트 이후에 매니저에서 처리함. 아래는 그런 버프들
			{
			case BuffEffect::ANTIDOTE_1:
				for (int j = 0; j < buffFXs.size(); j++) {
					if (buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_1) { //중독 해제
						buffFXs.erase(buffFXs.begin() + j);
						j--;
					}
				}
				break;
			case BuffEffect::ANTIDOTE_2:
				for (int j = 0; j < buffFXs.size(); j++) {
					if (buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_1 || //중독, 맹독 해제
						buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_2) {
						buffFXs.erase(buffFXs.begin() + j);
						j--;
					}
				}
				break;
			case BuffEffect::ANTIDOTE_3:
				for (int j = 0; j < buffFXs.size(); j++) {
					if (buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_1 || //중독, 맹독, 극독 해제
						buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_2 ||
						buffFXs[j]->GetEffectNumber() == BuffEffect::POISON_3) {
						buffFXs.erase(buffFXs.begin() + j);
						j--;
					}
				}
				break;
			case BuffEffect::CURE:
				for (int j = 0; j < buffFXs.size(); j++) {
					if (IsDebuff(buffFXs[j]->GetEffectNumber())) { //해로운 상태이상 해제
						buffFXs[j]->EndBuff();
						//EndBuff 함수는 특정 버프가 사라지기 전 예외 처리를 해주는 함수로 혹시라도 버프를 해제할 땐 반드시 사용해주어야 한다.
						buffFXs.erase(buffFXs.begin() + j);
						j--;
					}
				}
				break;
			case BuffEffect::VOID_EFFECT:
				for (int j = 0; j < buffFXs.size(); j++) {
					if (IsBuff(buffFXs[j]->GetEffectNumber())) { //이로운 상태이상 해제
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
	//특정 버프 A 위에 B를 덧씌울 경우 예외처리
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