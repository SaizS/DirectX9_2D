#include "framework.h"

EnemyManager* EnemyManager::instance = NULL;

EnemyManager::EnemyManager()
{
	LoadEnemy();
}

EnemyManager::~EnemyManager()
{
	for (auto enemy : totalEnemy)
	{
		for (Enemy* value : enemy.second)
			delete value;
	}

	delete mage;
}

EnemyManager* EnemyManager::GetInstance()
{
	return instance;
}

void EnemyManager::Create()
{
	instance = new EnemyManager();
}

void EnemyManager::Delete()
{
	delete instance;
}

vector<Enemy*> EnemyManager::FindEnemy(string key)
{
	if (totalEnemy.count(key) == 0)
		return vector<Enemy*>();

	return totalEnemy[key];
}

void EnemyManager::ForestSpawn()
{
	for (auto forestEnemy : forestEnemies)
	{
		for (Enemy* enemy : forestEnemy)
			enemy->Spawn();
	}
}

void EnemyManager::MountainSpawn()
{
	for (auto mountainEnemy : mountainEnemies)
	{
		for (Enemy* enemy : mountainEnemy)
			enemy->Spawn();
	}
}

void EnemyManager::LoadEnemy()
{
	vector<Enemy*> data;

	//Forest - Chicken
	for (int i = 0; i < CHICKEN_COUNT; i++)
		data.push_back(new Chicken());

	totalEnemy.insert({ "BlackChicken", data });
	forestEnemies.push_back(data);
	data.clear();

	//Forest - Pig
	for (int i = 0; i < PIG_COUNT; i++)
		data.push_back(new Pig());

	totalEnemy.insert({ "Pig", data });
	forestEnemies.push_back(data);
	data.clear();

	//Forest - Slime
	for (int i = 0; i < SLIME_COUNT; i++)
		data.push_back(new Slime());

	totalEnemy.insert({ "GreenSlime", data });
	forestEnemies.push_back(data);
	data.clear();

	//Mountain - MushRoom
	for (int i = 0; i < MUSHROOM_COUNT; i++)
		data.push_back(new MushRoom());

	totalEnemy.insert({ "MushRoom", data });
	mountainEnemies.push_back(data);
	data.clear();

	//Mountain - Flower
	for (int i = 0; i < FLOWER_COUNT; i++)
		data.push_back(new Flower());

	totalEnemy.insert({ "Flower", data });
	mountainEnemies.push_back(data);
	data.clear();

	//Mountain - Goblin
	for (int i = 0; i < GOBLIN_COUNT; i++)
		data.push_back(new Goblin());

	totalEnemy.insert({ "Goblin", data });
	mountainEnemies.push_back(data);
	data.clear();

	mage = new Mage();
}

void EnemyManager::SetPlayer(Player* player)
{
	for (auto forestEnemy : forestEnemies)
	{
		for (Enemy* enemy : forestEnemy)
			enemy->SetPlayer(player);
	}

	for (auto mountainEnemy : mountainEnemies)
	{
		for (Enemy* enemy : mountainEnemy)
			enemy->SetPlayer(player);
	}

	mage->SetPlayer(player);
}
