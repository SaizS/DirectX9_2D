#pragma once
class StateBar : public UIObject {
private:
	Texture* panel; //�г�
	Texture* hpBar; //ü�� ��
	World* hpBarWorld; //ü�� �� ����
	Texture* playerIcon; //�÷��̾� ������
	World* pIWorld; //�÷��̾� ������ ����
	Shader* hpbarShader; //���̴� (hp�� ��)

	float* curHp; //���� ü�� (�÷��̾�)
	float* maxHp; //�ִ� ü�� (�÷��̾�)
public:
	StateBar();
	~StateBar();
	void Render();

	void SetHp(float* curHp, float* maxHp) {
		this->curHp = curHp;
		this->maxHp = maxHp;
	}


};