#include "framework.h"

BuffEffect::BuffEffect(int effectNum, float* maxHp, float* hp, float* atk, float* def, float* speed) : effectNumber(effectNum), duration(-1.0f), maxHp(maxHp), hp(hp), atk(atk), def(def), speed(speed), intValue(0), floatValue(0.0f), tick(0.0f)
{
	Icon = new BuffIcon(effectNum, &duration);
}

BuffEffect::~BuffEffect()
{
}

void BuffEffect::Update()
{
	if (duration == -1.0f) {
		BuffSetting();
		return; //함수를 끝내는 이유는 지속시간이 0일 때 업데이트를 한 번 더 돌리므로 1회 더 돌아가는 것을 방지하기 위함
	}
	if (tick > 0)
		tick -= DELTATIME;
	duration -= DELTATIME;
	switch ((Buff_Type)effectNumber)
	{
	case BuffEffect::REGENERATION_1:
	case BuffEffect::REGENERATION_2:
	case BuffEffect::REGENERATION_3:
		if (tick <= 0) {
			tick = 1.0f;
			*hp += floatValue;
			if (*hp > * maxHp) {
				*hp = *maxHp;
			}
		}
		break;
	case BuffEffect::POISON_1:
	case BuffEffect::POISON_2:
	case BuffEffect::POISON_3:
		if (tick <= 0) {
			tick = 1.0f;
			*hp -= floatValue;
		}
		break;
	case BuffEffect::BURN:
		if (tick <= 0) {
			tick = 1.0f;
			*hp -= floatValue;
		}
		break;
	case BuffEffect::BLEEDING:
		if (tick <= 0) {
			tick = 1.0f;
			*hp -= floatValue;
		}
		break;
	default:
		break;
	}

	Icon->Update();
}

void BuffEffect::BuffSetting()
{
	duration = 0.0f;
	switch ((Buff_Type)effectNumber)
	{
	case BuffEffect::HEAL_1:
		SOUND->Play("heal", 0.5f);
		floatValue = *maxHp * 0.1f;
		*hp += floatValue;
		break;
	case BuffEffect::HEAL_2:
		SOUND->Play("heal", 0.5f);
		floatValue = *maxHp * 0.1f;
		*hp += floatValue * 2.0f;
		break;
	case BuffEffect::HEAL_3:
		SOUND->Play("heal", 0.5f);
		floatValue = *maxHp * 0.1f;
		*hp += floatValue * 3.0f;
		break;
	case BuffEffect::ANTIDOTE_1:
	case BuffEffect::ANTIDOTE_2:
	case BuffEffect::ANTIDOTE_3:
		SOUND->Play("antidote", 0.5f);
		break;
	case BuffEffect::REGENERATION_1:
		SOUND->Play("regeneration", 0.5f);
		tick = 1.0f;
		floatValue = *maxHp * 0.1f;
		floatValue *= 3.0f;
		floatValue *= 0.1f;
		duration = 10.0f;
		break;
	case BuffEffect::REGENERATION_2:
		SOUND->Play("regeneration", 0.5f);
		tick = 1.0f;
		floatValue = *maxHp * 0.1f;
		floatValue *= 6.0f;
		floatValue *= 0.1f;
		duration = 10.0f;
		break;
	case BuffEffect::REGENERATION_3:
		SOUND->Play("regeneration", 0.5f);
		tick = 1.0f;
		floatValue = *maxHp * 0.1f;
		duration = 10.0f;
		break;
	case BuffEffect::HASTE:
		SOUND->Play("haste", 0.5f);
		floatValue = *speed * 0.5f;
		*speed += floatValue;
		duration = 8.0f;
		break;
	case BuffEffect::CURE:
		SOUND->Play("cure", 0.5f);
		break;
	case BuffEffect::PROTECT:
		//피해 면역
		SOUND->Play("protect", 0.5f);
		duration = 5.0f;
		break;
	case BuffEffect::POISON_1:
		SOUND->Play("poison", 0.5f);
		tick = 1.0f;
		floatValue = (*maxHp * 0.01f) + 1.0f;
		duration = 10.0f;
		break;
	case BuffEffect::POISON_2:
		SOUND->Play("poison", 0.5f);
		tick = 1.0f;
		floatValue = (*maxHp * 0.02f) + 2.0f;
		duration = 10.0f;
		break;
	case BuffEffect::POISON_3:
		SOUND->Play("poison", 0.5f);
		tick = 1.0f;
		floatValue = (*maxHp * 0.03f) + 3.0f;
		duration = 10.0f;
		break;
	case BuffEffect::SHOCKWAVE:
		SOUND->Play("shockwave", 0.5f);
		*hp -= 5;
		break;
	case BuffEffect::SHOCK:
		SOUND->Play("shock", 0.5f);
		floatValue = 3.0f;
		*def += floatValue;
		duration = 6.0f;
		break;
	case BuffEffect::PARALYZE:
		SOUND->Play("paralyze", 0.5f);
		floatValue = *speed;
		*speed -= floatValue;
		duration = 4.0f;
		break;
	case BuffEffect::BURN:
		SOUND->Play("burn", 0.5f);
		tick = 1.0f;
		floatValue = 5.0f;
		duration = 10.0f;
		break;
	case BuffEffect::FREEZE:
		SOUND->Play("freeze", 0.5f);
		duration = 4.0f;
		break;
	case BuffEffect::EXPLOSION:
		SOUND->Play("explosion", 0.5f);
		*hp -= 40;
		break;
	case BuffEffect::EXTINCTION:
		SOUND->Play("extinction", 0.5f);
		*hp -= 999;
		break;
	case BuffEffect::HARDENING:
		SOUND->Play("hardening", 0.5f);
		floatValue = 5.0f;
		*def += floatValue;
		duration = 10.0f;
		break;
	case BuffEffect::POLLUTION:
		break;
	case BuffEffect::CORROSION:
		SOUND->Play("corrosion", 0.5f);
		floatValue = 5.0f;
		*def -= floatValue;
		duration = 10.0f;
		break;
	case BuffEffect::SLOW:
		SOUND->Play("slow", 0.5f);
		floatValue = *speed * 0.5f;
		*speed -= floatValue;
		duration = 8.0f;
		break;
	case BuffEffect::ENHANCE_HP:
		SOUND->Play("enhanceHp", 0.5f);
		floatValue = *maxHp * 0.5f;
		*maxHp += floatValue;
		*hp += floatValue;
		duration = 30.0f;
		break;
	case BuffEffect::VOID_EFFECT:
		SOUND->Play("void", 0.5f);
		break;
	case BuffEffect::BLEEDING:
		SOUND->Play("bleeding", 0.5f);
		tick = 1.0f;
		floatValue = 4.0f;
		duration = 5.0f;
		break;
	default:
		break;
	}
}

void BuffEffect::EndBuff()
{
	switch ((Buff_Type)effectNumber) {
	case BuffEffect::HASTE:
		duration = 0.0f;
		*speed -= floatValue;
		break;
	case BuffEffect::SHOCK:
		duration = 0.0f;
		*def += floatValue;
		break;
	case BuffEffect::PARALYZE:
		duration = 0.0f;
		*speed += floatValue;
		break;
	case BuffEffect::HARDENING:
		duration = 0.0f;
		*def -= floatValue;
		break;
	case BuffEffect::CORROSION:
		duration = 0.0f;
		*def += floatValue;
		break;
	case BuffEffect::SLOW:
		duration = 0.0f;
		*speed += floatValue;
		break;
	case BuffEffect::ENHANCE_HP:
		duration = 0.0f;
		*maxHp -= floatValue;
		break;
	default:
		break;
	}
}
