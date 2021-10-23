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
	//각 NPC에서 재정의
	//virtual ~Npc();
	virtual void LoadActions() = 0;

	//Npc에서 정의하는 함수
	virtual void Update();
	virtual void Render();
	virtual void SetActions(State val);
	virtual void Click();
	virtual void Actions();
};