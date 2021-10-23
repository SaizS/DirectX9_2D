#include "framework.h"
SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager() : curScene(NULL)
{
	isPlayerDie = true;
}

SceneManager::~SceneManager()
{
	for (auto index : sceneList)
		delete index.second;
}

void SceneManager::Create()
{
	instance = new SceneManager();
}

void SceneManager::Delete()
{
	delete instance;
}

void SceneManager::Update()
{
	if (curScene == NULL)
		return;
	DieScene();
	ReviveScene();

	curScene->Update();

	for (Effect* effect : EFFECT->GetEffect("Hit"))
		effect->Update();
}

void SceneManager::Render()
{
	if (curScene == NULL)
		return;
	curScene->Render();
}

Scene* SceneManager::Add(string key, Scene* scene)
{
	sceneList.insert({ key, scene });
	return scene;
}

void SceneManager::ChangeScene(string key)
{
	if (sceneList.count(key) == 0)
		return;
	if (sceneList[key] == curScene)
		return;
	if (curScene != NULL) //현재 씬이 있는 경우
		curScene->Release(); //현재 씬을 릴리즈
	curScene = sceneList[key]; //키 값에 해당하는 씬을 현재 씬으로 넣음
	curScene->Init(); //현재 씬을 이니트

	if (key == "Home")
	{
		CAM->SetFix(false);
		CAM->SetFocus(false);
		CAM->pos = { 0, 0 };
	}

	if (key == "Tool")
	{
		CAM->SetFix(false);
		CAM->SetFocus(false);
		CAM->pos = { 0,0 };
		CAM->SetTarget(NULL);
	}

	GUI->GetBossHpBar()->isActive = false;
}

void SceneManager::ChangeScene(string key, Vector2 pos)
{
	if (sceneList.count(key) == 0)
		return;
	if (sceneList[key] == curScene)
		return;
	if (curScene != NULL) //현재 씬이 있는 경우
		curScene->Release(); //현재 씬을 릴리즈
	curScene = sceneList[key]; //키 값에 해당하는 씬을 현재 씬으로 넣음
	curScene->SetPos(pos);
	curScene->Init(); //현재 씬을 이니트

	if (key == "Cave")
		GUI->GetBossHpBar()->isActive = true;
	else
		GUI->GetBossHpBar()->isActive = false;


	if (key == "Home")
	{
		CAM->SetFix(false);
		CAM->SetFocus(false);
		CAM->pos = { 0, 0 };
		if (!SOUND->CheckMusic("Town"))
		{
			SOUND->MusicStop();
			SOUND->Play("Town");
		}
	}
	if (key == "Town")
	{
		CAM->SetMapSize({ 205, 478, -205, -335 });
		CAM->SetFix(true);
		CAM->SetFocus(true);
		if (!SOUND->CheckMusic("Town"))
		{
			SOUND->MusicStop();
			SOUND->Play("Town");
		}
	}
	if (key == "Forest")
	{
		CAM->SetMapSize({ 687, 840, -682, -840 });
		CAM->SetFix(true);
		CAM->SetFocus(true);
		SOUND->MusicStop();
		SOUND->Play("Forest");
		PATICLE->ResetPaticle(Paticle::FOREST);
		ENEMY->ForestSpawn();
	}
	if (key == "Mountain")
	{
		CAM->SetMapSize({ 1200, 1200, -177, -480 });
		CAM->SetFix(true);
		CAM->SetFocus(true);
		CAM->pos = { 0, 0 };
		PATICLE->ResetPaticle(Paticle::MOUNTAIN);
		ENEMY->MountainSpawn();
		SOUND->MusicStop();
		SOUND->Play("Mountain");
	}
	if (key == "Cave")
	{
		CAM->SetMapSize({ 720, 490, 300, 240 });
		CAM->SetFix(true);
		CAM->SetFocus(true);
		CAM->pos = { 0, 0 };
		SOUND->MusicStop();
		SOUND->Play("Cave");
		ENEMY->GetMage()->ReSet();
	}

	curScene->FadeInOn();
}

void SceneManager::DieScene()
{
	if (!isPlayerDie)
		return;

	curScene->GetColor()->a -= DELTA * 0.5f;

	if (curScene->GetColor()->a <= 0)
	{
		sceneList["Home"]->GetColor()->a = 0.0f;
		isPlayerRevive = true;
		isPlayerDie = false;
		Scene* prevScene = curScene;
		ChangeScene("Home");
		prevScene->GetColor()->a = 1.0f;
		curScene->PlayerSpawn();
		
	}
}

void SceneManager::ReviveScene()
{
	if (!isPlayerRevive)
		return;

	curScene->GetColor()->a += DELTA * 0.5f;

	if (curScene->GetColor()->a >= 1.0f)
		isPlayerRevive = false;
}
