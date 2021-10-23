#pragma once
#define TIMER Timer::GetInstance()
#define DELTATIME Timer::GetInstance()->GetElapsedTime()
class Timer
{
private:
	static Timer* instance;

	LPD3DXFONT font;
	bool isStop; // 일시 정지 여부

	INT64 ticksPerSecond;
	INT64 curTime; //현재 시간
	INT64 lastTime; //마지막 시간

	UINT frameRate; //fps
	UINT frameCount;
	float timeScale; //
	float timeElapsed; //경과된 시간 (업데이트 사이의 간격)

	float oneSecCount; //1초
	float playTime; //프로그램 구동 시간
	bool isLockFPS;
	float lockFPS;

	//생성 소멸자가 private 영역에 있을 경우 일반적인 호출로 선언 불가능
	Timer();
	~Timer();
public:
	static Timer* GetInstance();
	static void Delete();
	static void Create();

	void Update();
	void Render();
	bool IsStop() { return isStop; }
	UINT GetFPS() { return frameRate; }
	float GetElapsedTime(){ return isStop ? 0.0f : timeElapsed; }
	float GetPlayTime() { return playTime; }


};

