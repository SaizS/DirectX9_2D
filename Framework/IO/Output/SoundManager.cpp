#include "framework.h"
SoundManager* SoundManager::instance = NULL;

SoundManager::SoundManager() : bgmVolume(0.5f), sEVolume(1.0f)
{
	System_Create(&soundSystem);
	soundSystem->init(SOUNDCOUNT, FMOD_INIT_NORMAL, NULL);
}

SoundManager::~SoundManager()
{
	for (auto index : soundList)
		delete index.second;
	soundSystem->release();
}

SoundManager* SoundManager::GetInstance()
{
	return instance;
}

void SoundManager::Create()
{
	instance = new SoundManager();
}

void SoundManager::Delete()
{
	delete instance;
}

void SoundManager::Update()
{
	soundSystem->update();
	//사용한 소리 초기화
}

void SoundManager::Add(string key, string fileName, bool isBgm, bool isLoop)
{
	SoundInfo* info = new SoundInfo();
	if (isBgm) {
		info->isBgm = true;
		soundSystem->createSound(fileName.c_str(), FMOD_LOOP_NORMAL, NULL, &info->sound);
	}
	else if (isLoop) {
		soundSystem->createSound(fileName.c_str(), FMOD_LOOP_NORMAL, NULL, &info->sound);
	}
	else {
		soundSystem->createSound(fileName.c_str(), FMOD_DEFAULT, NULL, &info->sound);
	}
	soundList.insert({key, info});
}

void SoundManager::Play(string key, float volume)
{
	if (soundList.count(key) > 0) {
		if (soundList[key]->isBgm == true) {
			soundSystem->playSound(soundList[key]->sound, NULL, false, &soundList[key]->channel);
			soundList[key]->channel->setVolume(volume * bgmVolume);
		}
		else {
			soundSystem->playSound(soundList[key]->sound, NULL, false, &soundList[key]->channel);
			soundList[key]->channel->setVolume(volume * sEVolume);
		}
	}
}

void SoundManager::SinglePlay(string key, float volume)
{
	if (soundList.count(key) > 0) {
		bool isPlay = false;
		soundList[key]->channel->isPlaying(&isPlay);
		if (!isPlay) {
			if (soundList.count(key) > 0) {
				if (soundList[key]->isBgm == true) {
					soundSystem->playSound(soundList[key]->sound, NULL, false, &soundList[key]->channel);
					soundList[key]->channel->setVolume(volume * bgmVolume);
				}
				else {
					soundSystem->playSound(soundList[key]->sound, NULL, false, &soundList[key]->channel);
					soundList[key]->channel->setVolume(volume * sEVolume);
				}
			}
		}
	}
}

void SoundManager::MusicStop()
{
	for (auto temp : soundList)
	{
		bool isPlay = false;
		temp.second->channel->isPlaying(&isPlay);
		if (isPlay)
			temp.second->channel->stop();
	}
}

void SoundManager::Stop(string key)
{
	if (soundList.count(key) > 0) {
		bool isPlay = false;
		soundList[key]->channel->isPlaying(&isPlay);
		if (isPlay)
			soundList[key]->channel->stop();
	}
}

void SoundManager::Pause(string key)
{
	if (soundList.count(key) > 0) {
		bool isPlay = false;
		soundList[key]->channel->isPlaying(&isPlay);
		if (isPlay)
			soundList[key]->channel->setPaused(true);
	}
}

void SoundManager::Resume(string key)
{
	if (soundList.count(key) > 0) {
		bool isPlay = false;
		soundList[key]->channel->isPlaying(&isPlay);
		if (isPlay)
			soundList[key]->channel->setPaused(false);
	}
}

bool SoundManager::CheckMusic(string key)
{
	bool isPlay = false;
	soundList[key]->channel->isPlaying(&isPlay);

	if (isPlay)
		return true;
	else
		return false;
}
