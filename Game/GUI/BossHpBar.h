#pragma once
class BossHpBar : public UIObject {
private:
	Texture* panel; //�г�
	Texture* hpBar; //ü�� ��
	World* hpBarWorld; //ü�� �� ����
	Shader* hpbarShader; //���̴� (hp�� ��)

	float* curHp; //���� ü�� (����)
	float* maxHp; //�ִ� ü�� (����)
public:
	BossHpBar();
	~BossHpBar();
	void Render();

	void SetHp(float* curHp, float* maxHp) {
		this->curHp = curHp;
		this->maxHp = maxHp;
	}


};