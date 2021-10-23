#pragma once

class ChildMan1 : public Npc
{
private:

public:
	ChildMan1();
	~ChildMan1();

	virtual void LoadActions() override;
};