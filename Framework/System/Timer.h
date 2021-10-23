#pragma once
#define TIMER Timer::GetInstance()
#define DELTATIME Timer::GetInstance()->GetElapsedTime()
class Timer
{
private:
	static Timer* instance;

	LPD3DXFONT font;
	bool isStop; // �Ͻ� ���� ����

	INT64 ticksPerSecond;
	INT64 curTime; //���� �ð�
	INT64 lastTime; //������ �ð�

	UINT frameRate; //fps
	UINT frameCount;
	float timeScale; //
	float timeElapsed; //����� �ð� (������Ʈ ������ ����)

	float oneSecCount; //1��
	float playTime; //���α׷� ���� �ð�
	bool isLockFPS;
	float lockFPS;

	//���� �Ҹ��ڰ� private ������ ���� ��� �Ϲ����� ȣ��� ���� �Ұ���
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

