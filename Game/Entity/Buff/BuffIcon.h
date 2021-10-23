#pragma once
class BuffIcon : public Info
{
private:
	Texture* texture;
	BuffEffect::Buff_Type type;

	bool isFliker;
	float flikerTime;

	Shader* shader;
	D3DXCOLOR color;
public:
	float* duration;

	BuffIcon(int key, float* duration);
	virtual void Update() override;
	virtual void Render() override;
};