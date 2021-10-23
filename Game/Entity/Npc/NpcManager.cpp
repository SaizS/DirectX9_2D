#include "framework.h"

NpcManager* NpcManager::instance = NULL;

NpcManager::NpcManager()
{
	LoadNpc();
}

NpcManager::~NpcManager()
{
	for (auto npc : totalNpc)
		delete npc.second;
}

NpcManager* NpcManager::GetInstance()
{
	return instance;
}

void NpcManager::Create()
{
	instance = new NpcManager();
}

void NpcManager::Delete()
{
	delete instance;
}

Npc* NpcManager::GetNpc(string key)
{
	if (totalNpc.count(key) == 0)
		return NULL;

	return totalNpc[key];
}

void NpcManager::LoadNpc()
{
	totalNpc.insert({ "BlackSmith", new BlackSmith() });
	totalNpc.insert({ "FolkOne", new FolkOne() });
	totalNpc.insert({ "FolkTwo", new FolkTwo() });
	totalNpc.insert({ "ChildMan1", new ChildMan1() });
	totalNpc.insert({ "ChildMan2", new ChildMan2() });
	totalNpc.insert({ "ChildWoman1", new ChildWoman1() });
	totalNpc.insert({ "ChildWoman2", new ChildWoman2() });
	totalNpc.insert({ "Cat", new Cat() });
}
