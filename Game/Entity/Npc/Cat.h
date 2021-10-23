#pragma once

class Cat : public Npc
{
private:

public:
	Cat();
	~Cat();

	virtual void LoadActions() override;

};