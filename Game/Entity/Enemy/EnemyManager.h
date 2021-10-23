#pragma once

#define CHICKEN_COUNT 5
#define PIG_COUNT 5
#define SLIME_COUNT 10
#define FLOWER_COUNT 5
#define MUSHROOM_COUNT 5
#define GOBLIN_COUNT 5
#define ENEMY_COUNT 10

class EnemyManager
{
private:
	static EnemyManager* instance;
	EnemyManager();
	~EnemyManager();

	map<string, vector<Enemy*>> totalEnemy; // 키 = 적 이름 , vector로 폴링을 위해 여러개를 생성해둠
	vector<vector<Enemy*>> forestEnemies;
	vector<vector<Enemy*>> mountainEnemies;
	Mage* mage;

public:
	static EnemyManager* GetInstance();
	static void Create();
	static void Delete();

	vector<Enemy*> FindEnemy(string key);

	vector<vector<Enemy*>> GetForestEnemy() { return forestEnemies; }
	vector<vector<Enemy*>> GetMountainEnemy() { return mountainEnemies; }
	Mage* GetMage() { return mage; }

	void ForestSpawn();
	void MountainSpawn();

	void LoadEnemy();
	void SetPlayer(Player* player);
};