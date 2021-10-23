#pragma once

class ImageFont : public World
{
public:
	enum Align
	{
		LEFT,
		CENTER,
		RIGHT
	};
private:
	vector<Texture*> textures;
	vector<float> width;
	UINT value;
	float space;
	Align align;
	float fontLength;

	Shader* shader;
	Color color;
public:
	ImageFont(float space = 2.0f, Align align = LEFT);
	ImageFont(vector<Texture*> textures, float space = 5.0f, Align align = LEFT);
	~ImageFont();

	void Render();

	void SetValue(UINT val);
	UINT GetValue() { return value; }
};