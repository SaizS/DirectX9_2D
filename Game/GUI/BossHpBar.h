#pragma once
class BossHpBar : public UIObject {
private:
	Texture* panel; //패널
	Texture* hpBar; //체력 바
	World* hpBarWorld; //체력 바 월드
	Shader* hpbarShader; //쉐이더 (hp바 용)

	float* curHp; //현재 체력 (보스)
	float* maxHp; //최대 체력 (보스)
public:
	BossHpBar();
	~BossHpBar();
	void Render();

	void SetHp(float* curHp, float* maxHp) {
		this->curHp = curHp;
		this->maxHp = maxHp;
	}


};