#pragma once

class Scene
{
protected:
	RenderTarget* renderTarget;
	Shader* shader;
	D3DXCOLOR color;

	bool isFadeIn;
	bool isFadeOut;

	string key;
	Vector2 pos;

	bool isMapEditor;
public:
	Scene();
	virtual ~Scene();
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void Release() = 0;
	virtual void SetPos(Vector2 pos) = 0;
	virtual void PlayerSpawn() = 0;

	void SetFade(string key, Vector2 pos);

	void FadeInOn() { if (color.a < 1.0f) isFadeIn = true; }

	void FadeIn();
	void FadeOut();

	bool GetIsFadeOut() { return isFadeOut; }
	bool GetIsFadeIn() { return isFadeIn; }

	D3DXCOLOR* GetColor() { return &color; }
};