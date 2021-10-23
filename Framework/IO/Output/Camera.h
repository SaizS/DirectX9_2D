#pragma once
#define CAM Camera::GetInstance()
class Camera
{
private:
	static Camera* instance;
	Camera();
	~Camera();

	D3DXMATRIX view;
	float speed;

	World* target;
	bool isFocus;
	Vector4 mapSize; //l t r b

	bool isShake;
	bool isVertical;
	bool isFix;
	float shakePower;
	float shakeDuration;
	Vector2 shakeRadius;

	D3DXMATRIX S, R, T;
public:
	D3DXVECTOR2 pos;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 rot;

	D3DXVECTOR2 offset;

	float angle;

	static void Create();
	static void Delete();
	static Camera* GetInstance() { return instance; }

	void Update();

	void Render();
	void Move();
	void Shake(float power, float duration, bool isVertical = false);
	void Shaking();

	bool IsFocus() { return isFocus; }
	void SetFocus(bool value) { isFocus = value; }
	void SetTarget(World* value) { target = value; }
	void SetMapSize(Vector4 value) { mapSize = value; }
	void SetMapSize(World* world) { mapSize = { world->Left(), world->Top(), world->Right(), world->Bottom()}; }
	void SetPos(float x, float y) { pos.x = x, pos.y = y; }
	void SetPos(Vector2 value) { pos = value; }
	Vector2 GetPos() { return pos; }
	void SetView() { DEVICE->SetTransform(D3DTS_VIEW, &view); } 

	World* GetTarget() { return target; }

	void SetFix(bool val) { isFix = val; }
};

