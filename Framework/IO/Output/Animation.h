#pragma once
enum class Type {
	END, 
	LOOP, 
	REVERSE
};
class Animation
{
private:
	function<void()> EndEvent;
	vector<Texture*> clips;
	Type playType;
	bool isPlay;
	bool isReverse;
	DWORD playTime;
	UINT curClipNum;

	float time;
	float speed;
public:
	Animation(vector<Texture*> clips, Type type = Type::END, float speed = 0.1f);
	~Animation();
	void Update();
	void Render();
	void AlphaRender();
	void Play();
	void Pause();
	void Stop();
	void EndStop();
	void SetEndEvent(function<void()> func) { EndEvent = func; }
	LPDIRECT3DTEXTURE9 GetTexture();
	UINT GetClipNum() { return curClipNum; }
	Vector2 GetSize() { return clips[curClipNum]->GetSize(); }
	bool GetIsPlay() { return isPlay; }
	void SetClipNum(UINT num) { curClipNum = num; }
};

