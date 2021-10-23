#pragma once

#define CREATE_TIME 30

class BlackSmith : public Npc
{
private:
	float createTime;

	bool isCreate;

public:
	BlackSmith();
	~BlackSmith();

	virtual void Update() override;
	virtual void LoadActions() override;
};