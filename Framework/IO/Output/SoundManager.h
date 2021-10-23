#pragma once
using namespace FMOD;
#define SOUND SoundManager::GetInstance()
#define SOUNDCOUNT 50 //동시에 실행할 수 있는 사운드의 갯수

struct SoundInfo { //재생에 필요한 정보를 담은 구조체
	Sound* sound; //소리
	Channel* channel; //볼륨
	bool isBgm;

	SoundInfo() : sound(NULL), channel(NULL), isBgm(false)
	{
	}
	~SoundInfo() {
		sound->release();
	}
};
class SoundManager
{
private:
	System* soundSystem;
	map<string, SoundInfo*> soundList;
	static SoundManager* instance;
	SoundManager();
	~SoundManager();
public:
	float bgmVolume;
	float sEVolume;
	static SoundManager* GetInstance();
	static void Create();
	static void Delete();
	void Update();
	void Add(string key, string fileName, bool isBgm = false, bool isLoop = false);
	void Play(string key, float volume = 1.0f);
	void SinglePlay(string key, float volume = 1.0f);
	void MusicStop();
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);

	bool CheckMusic(string key);
};

