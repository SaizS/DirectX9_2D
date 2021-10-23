#pragma once
class Enemy;
class Player;

class BuffManager : public World {
private:
	vector<BuffEffect*> buffFXs; //현재 보유한 버프
	float* maxHp;
	float* hp;
	float* atk;
	float* def;
	float* speed;
public:
	BuffManager(Player* player);
	BuffManager(Enemy* enemy);
	~BuffManager();
	void Update();
	void Render();
	void ClearBuff();
	void SetBuff(int effectNumber);
	bool BuffCheck(int key);
	bool BuffCheck(BUFFTYPE key);
	bool IsBuff(int key);
	bool IsDebuff(int key);
};