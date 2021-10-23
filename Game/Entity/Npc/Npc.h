#pragma once

class Npc : public Info
{
public:
	enum State
	{
		UPIDLE,
		UPWALK,
		DOWNIDLE,
		DOWNWALK,
		LEFTIDLE,
		LEFTWALK,
		RIGHTIDLE,
		RIGHTWALK,
		ACT1,
		ACT2,
		ACT3,
		ACT4
	};
protected:
	State state;
	vector<Animation*> actions;

public:
	//�� NPC���� ������
	//virtual ~Npc();
	virtual void LoadActions() = 0;

	//Npc���� �����ϴ� �Լ�
	virtual void Update();
	virtual void Render();
	virtual void SetActions(State val);
	virtual void Click();
	virtual void Actions();
};