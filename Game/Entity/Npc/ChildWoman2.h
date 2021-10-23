#pragma once

class ChildWoman2 : public Npc
{
private:
	float speed;

public:
	ChildWoman2();
	~ChildWoman2();

	virtual void Actions() override;
	virtual void LoadActions() override;

};