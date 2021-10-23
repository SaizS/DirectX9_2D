#include "framework.h"

EffectManager* EffectManager::instance = NULL; //�̱� �� ��� - Ŭ���� ���� �� �ν��Ͻ� NULL�� �ʱ�ȭ

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	for (auto index : effectList) { //auto ������ �� ��Ȳ�� �´� �ڷ����� �ڵ����� ä���ִ� �ڷ��� / effectList �� �Ҵ� ����
		for (Effect* effect : index.second) //effectList ���� Effect* ���� �ʱ�ȭ / effectList�� map �ڷ���. map �ڷ����� first�� Ű, second�� �����Ͱ� �����Ƿ� second�� ������ �����͸� �Ҵ� ����
		{
			delete effect;
		}
	}
}

EffectManager* EffectManager::GetInstance()
{
	return instance; //�ν��Ͻ� ��ȯ
}

void EffectManager::Create()
{
	instance = new EffectManager(); //�ν��Ͻ� �Ҵ�
}

void EffectManager::Delete()
{
	delete instance; //�ν��Ͻ� �Ҵ� ����
}

void EffectManager::Update()
{
	for (auto index : effectList) {
		for (Effect* effect : index.second)
		{
			effect->Update();
		}
	}
}

void EffectManager::Render()
{
	for (auto index : effectList) {
		for (Effect* effect : index.second)
		{
			effect->Render();
		}
	}
}

void EffectManager::Add(string key, wstring fileName, int frameX, int frameY, int poolingCount, float speed, int pass)
{
	Effects effects; //effectList�� ���� Effects(vector<Effect*>) ����
	for (int i = 0; i < poolingCount; i++) { //poolingCount ��ŭ ����Ʈ�� ����. (poolingCount�� �� ���� ȭ�鿡 ���ÿ� ��� ����)
		effects.push_back(new Effect(fileName, frameX, frameY, speed, pass));
	}
	effectList.insert({ key, effects }); //�� �Ҵ��� effects�� effectList�� ����
}

void EffectManager::Play(string key, Vector2 pos)
{
	if (effectList.count(key) == 0) //count.key ���� 0�� ���� �ش� key�� �߰����� �� ���� ���.
		return;
	for (Effect* index : effectList[key]) //key ������ effectList ���� �����͸� �˻�
	{
		if (!index->IsActive())
		{
			if (key == "Hit")
				SOUND->Play("PotionHit");
			index->Play(pos);
			return;
		}
	}
}

vector<Effect*> EffectManager::GetEffect(string key)
{
	if(effectList.count(key) == 0)
		return Effects();

	return effectList[key];
}
