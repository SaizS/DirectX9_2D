#include "framework.h"

Animation::Animation(vector<Texture*> clips, Type type, float speed)
	: playType(type), curClipNum(0), isPlay(false), isReverse(false), clips(clips), speed(speed), time(0.0f)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (!isPlay)
		return;
	time += DELTATIME;
	if (time >= speed) {
		time = 0.0f;
		switch (playType)
		{
		case Type::END:
			curClipNum++;
			if (curClipNum >= clips.size()) { 
				EndStop();
			}
			break;
		case Type::LOOP:
			curClipNum++;
			curClipNum %= clips.size();
			break;
		case Type::REVERSE:
			if (isReverse) {
				curClipNum--;
				if (curClipNum <= 0)
					isReverse = false;
			}
			else {
				curClipNum++;
				if (curClipNum >= clips.size() - 1)
					isReverse = true;
			}
			break;
		default:
			break;
		}
	}
}

void Animation::Render()
{
	clips[curClipNum]->Render();
}

void Animation::AlphaRender()
{
	clips[curClipNum]->AlphaRender();
}

void Animation::Play()
{
	if (isPlay)
		return;
	curClipNum = 0;
	isPlay = true;
	isReverse = false;
	time = 0.0f;
}

void Animation::Pause()
{
	isPlay = false;
}

void Animation::Stop()
{
	isPlay = false;
	curClipNum = 0;
}

void Animation::EndStop()
{
	isPlay = false;

	if (EndEvent == NULL)
		curClipNum--;
	else
	{
		curClipNum = 0;
		EndEvent();
	}
}

LPDIRECT3DTEXTURE9 Animation::GetTexture()
{
	return clips[curClipNum]->GetTexture();
}
