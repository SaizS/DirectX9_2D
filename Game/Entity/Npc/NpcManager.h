#pragma once

class NpcManager
{
private:
	static NpcManager* instance;
	NpcManager();
	~NpcManager();

	map<string, Npc*> totalNpc;

public:
	static NpcManager* GetInstance();
	static void Create();
	static void Delete();

	Npc* GetNpc(string key);

	void LoadNpc();
};