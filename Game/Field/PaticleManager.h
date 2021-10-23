#pragma once

class PaticleManager
{
private:
	map<string, vector<Paticle*>> totalPaticle;

	UINT forestPaticleCount;
	UINT mountainPaticleCount;

	static PaticleManager* instance;
	PaticleManager();
	~PaticleManager();
public:
	static void Create();
	static void Delete();
	static PaticleManager* GetInstance();

	vector<Paticle*> GetPaticle(string key);
	
	void ResetPaticle(Paticle::Stage stage);

	void LoadPaticle();

};