#pragma once

class Mage_Emote : public World
{
private:
	bool isActive;
	Animation* ani;

public:
	Mage_Emote(function<void()> Event);
	~Mage_Emote();

	void Update();
	void Render();

	void Play();

	void IsActiveFalse() { isActive = false; }
};