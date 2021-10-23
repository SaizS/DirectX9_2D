#include "framework.h"


ImageFont::ImageFont(float space, Align align) : space(space), align(align), value(0), color(1, 1, 1, 1), fontLength(0)
{
	for (int i = 0; i < 10; i++)
	{
		Texture* texture = TEXTURE->Add(L"Resource/Textures/UI/imageFont.png", i, 0, 10, 1);
		textures.push_back(texture);
		width.push_back(texture->GetSize().x);
	}
	shader = Shader::Add(L"Shader/Object.hlsl");
}

ImageFont::ImageFont(vector<Texture*> textures, float space, Align align) : textures(textures), space(space), align(align), value(0), color(1, 1, 1, 1), fontLength(0)
{
	shader = Shader::Add(L"Shader/Object.hlsl");

	for (Texture* texture : textures)
		width.push_back(texture->GetSize().x);
}

ImageFont::~ImageFont()
{
}

void ImageFont::Render()
{
	string str = to_string(value);

	shader->SetVector("color", &color, 4);

	int length = 0;
	Matrix matWorld;

	float startPos = 0.0f;

	switch (align)
	{
	case ImageFont::LEFT:
		startPos = 0.0f;
		break;
	case ImageFont::CENTER:
		startPos = -(fontLength * 0.5f);
		break;
	case ImageFont::RIGHT:
		startPos = -fontLength;
		break;
	default:
		break;
	}

	for (int i = 0; i < str.size(); i++)
	{
		D3DXMatrixTranslation(&matWorld, startPos + length, 0, 0);
		matWorld *= world;
		DEVICE->SetTransform(D3DTS_WORLD, &matWorld);

		int index = str[i] - '0';

		shader->SetTexture("map", textures[index]->GetTexture());

		shader->Begin();
		textures[index]->Render();
		shader->End();
		//length += textures[index]->GetSize().x + space;
		length += width[0] + space;
	}
}

void ImageFont::SetValue(UINT val)
{
	value = val;
	fontLength = 0.0f;
	string str = to_string(value);
	for (UINT i = 0; i < str.size(); i++)
	{
		int index = str[i] - '0';
		fontLength += width[0] + space;
	}
}
