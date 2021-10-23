#include "framework.h"

EffectManager* EffectManager::instance = NULL; //싱글 톤 기법 - 클래스 생성 시 인스턴스 NULL로 초기화

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	for (auto index : effectList) { //auto 예약어는 그 상황에 맞는 자료형을 자동으로 채워주는 자료형 / effectList 맵 할당 해제
		for (Effect* effect : index.second) //effectList 안의 Effect* 벡터 초기화 / effectList는 map 자료형. map 자료형은 first에 키, second에 데이터가 있으므로 second를 참조해 데이터를 할당 해제
		{
			delete effect;
		}
	}
}

EffectManager* EffectManager::GetInstance()
{
	return instance; //인스턴스 반환
}

void EffectManager::Create()
{
	instance = new EffectManager(); //인스턴스 할당
}

void EffectManager::Delete()
{
	delete instance; //인스턴스 할당 해제
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
	Effects effects; //effectList에 넣을 Effects(vector<Effect*>) 생성
	for (int i = 0; i < poolingCount; i++) { //poolingCount 만큼 이펙트를 생성. (poolingCount의 수 까지 화면에 동시에 출력 가능)
		effects.push_back(new Effect(fileName, frameX, frameY, speed, pass));
	}
	effectList.insert({ key, effects }); //다 할당한 effects를 effectList에 대입
}

void EffectManager::Play(string key, Vector2 pos)
{
	if (effectList.count(key) == 0) //count.key 값이 0인 경우는 해당 key를 발견하지 못 했을 경우.
		return;
	for (Effect* index : effectList[key]) //key 값으로 effectList 안의 데이터를 검색
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
