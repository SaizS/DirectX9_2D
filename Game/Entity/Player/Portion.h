#pragma once
#define FLASKSIZE 32

class Potion : public Info
{
private:
	Texture* texture;

	int effect;

	float speed;
	float angle;
	float rotSpeed;

	bool isActive;

public:
	Potion();
	~Potion();

	virtual void Update() override;
	virtual void Render() override;

	void Fire(float angle, Vector2 pos);
	void Fire(Texture* texture, float angle, Vector2 pos);

	bool GetIsActive() { return isActive; }
	Texture* GetTexture() { return texture; }
	int GetEffect() { return effect; }

	void SetEffect(int value) { effect = value; }
	void SetIsActive(bool value) { isActive = value; }
	void SetTexture(Texture* texture) { this->texture = texture; }

	void Crash();

	void LoadActions();
};