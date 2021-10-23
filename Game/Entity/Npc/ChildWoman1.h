#pragma once

class ChildWoman1 : public Npc
{
private:
	float speed;

public:
	ChildWoman1();

	virtual void Actions() override;
	virtual void LoadActions() override;
};