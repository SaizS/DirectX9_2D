#include "framework.h"

PaticleManager* PaticleManager::instance = NULL;

PaticleManager::PaticleManager()
{
	LoadPaticle();
}

PaticleManager::~PaticleManager()
{
	for (auto paticle : totalPaticle)
	{
		for (Paticle* pati : paticle.second)
			delete pati;
	}
}

void PaticleManager::Create()
{
	instance = new PaticleManager();
}

void PaticleManager::Delete()
{
	delete instance;
}

PaticleManager* PaticleManager::GetInstance()
{
	return instance;
}

vector<Paticle*> PaticleManager::GetPaticle(string key)
{
	if(totalPaticle.count(key) == 0)
		return vector<Paticle*>();

	return totalPaticle[key];
}

void PaticleManager::ResetPaticle(Paticle::Stage stage)
{
	if (stage == Paticle::FOREST)
	{
		for (int i = 0; i < forestPaticleCount; i++)
		{
			totalPaticle["ForestPaticle"][i]->SetIsActive(false);

			if (OP::Random(0, 3) == 0)
				totalPaticle["ForestPaticle"][i]->SetIsActive(true);
		}
	}

	if (stage == Paticle::MOUNTAIN)
	{
		for (int i = 0; i < mountainPaticleCount; i++)
		{
			totalPaticle["MountainPaticle"][i]->SetIsActive(false);

			if (OP::Random(0, 2) == 1)
				totalPaticle["MountainPaticle"][i]->SetIsActive(true);
		}
	}
}

void PaticleManager::LoadPaticle()
{
	//Forest
	BinaryReader r = BinaryReader(L"Data/Map/ForestPaticle.data");

	UINT forestSize = r.UInt();
	forestPaticleCount = forestSize;

	vector<Vector2> forestData;
	forestData.resize(forestSize);

	void* ptr = (void*)forestData.data();

	r.Byte(&ptr, sizeof(Vector2) * forestSize);

	vector<Paticle*> forestPaticle;

	for (int i = 0; i < forestSize; i++)
		forestPaticle.push_back(new Paticle(forestData[i], Paticle::FOREST));

	totalPaticle.insert({ "ForestPaticle", forestPaticle });

	//Mountain
	 BinaryReader mR = BinaryReader(L"Data/Map/MountainPaticle.data");

	UINT mountainSize = mR.UInt();
	mountainPaticleCount = mountainSize;

	vector<Vector2> mountainData;
	mountainData.resize(mountainSize);

	void* mountainPtr = (void*)mountainData.data();

	mR.Byte(&mountainPtr, sizeof(Vector2) * mountainSize);

	vector<Paticle*> mountainPaticle;

	for (int i = 0; i < mountainSize; i++)
		mountainPaticle.push_back(new Paticle(mountainData[i], Paticle::MOUNTAIN));

	totalPaticle.insert({ "MountainPaticle", mountainPaticle });
}
