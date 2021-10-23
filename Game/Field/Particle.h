#pragma once

class Paticle : public Info
{
public:
	enum Stage
	{
		FOREST,
		MOUNTAIN
	};

private:
	Stage stage;

	Animation* paticle;
	bool isActive;

public:
	Paticle();
	Paticle(Vector2 pos, Stage stage, bool isActive = false);
	~Paticle();
	
	virtual void Update() override;
	virtual void Render() override;

	Stage GetStage() { return stage; }
	bool GetIsAcitve() { return isActive; }

	void SetIsActive(bool value) { isActive = value; }
};