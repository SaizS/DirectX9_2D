#pragma once
#define SCENE SceneManager::GetInstance()
#define CURSCENE SceneManager::GetInstance()->GetCurScene()

class SceneManager
{
private:
	static SceneManager* instance;
	map<string, Scene*> sceneList;

	bool isPlayerDie;
	bool isPlayerRevive;

	Scene* curScene;
	SceneManager();
	~SceneManager();
public:
	static SceneManager* GetInstance() { return instance; }
	static void Create();
	static void Delete();

	void DiePlayer() { isPlayerDie = true; }

	void Update();
	void Render();
	Scene* Add(string key, Scene* scene);
	void ChangeScene(string key);
	void ChangeScene(string key, Vector2 pos);
	void DieScene();
	void ReviveScene();

	Scene* GetCurScene() { return curScene; }
};