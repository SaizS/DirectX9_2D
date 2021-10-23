#pragma once
#define BUFF BuffEffect
#define BUFFTYPE BuffEffect::Buff_Type

class BuffIcon;

class BuffEffect {
public:
	enum Buff_Type {
		NONE = 0,
		HEAL_1,
		HEAL_2,
		HEAL_3,
		ANTIDOTE_1,
		ANTIDOTE_2,
		ANTIDOTE_3,
		REGENERATION_1,
		REGENERATION_2,
		REGENERATION_3,
		HASTE,
		CURE,
		PROTECT,
		POISON_1,
		POISON_2,
		POISON_3,
		SHOCKWAVE,
		SHOCK,
		PARALYZE,
		BURN,
		FREEZE,
		EXPLOSION,
		EXTINCTION,
		HARDENING,
		POLLUTION,
		CORROSION,
		SLOW,
		ENHANCE_HP,
		VOID_EFFECT,
		BLEEDING
	};
private:
	BuffIcon* Icon;
	int effectNumber;
	float* maxHp;
	float* hp;
	float* atk;
	float* def;
	float* speed;

	int intValue;
	float floatValue;
	float tick;
public:
	float duration;

	BuffEffect(int effectNum, float* maxHp, float* hp, float* atk, float* def, float* speed);
	~BuffEffect();
	void Update();
	void BuffSetting();
	void EndBuff();

	int GetEffectNumber() { return effectNumber; }
	BuffIcon* GetIcon() { return Icon; }

};