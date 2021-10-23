#include "framework.h"

BuffIcon::BuffIcon(int key, float* duration) : isFliker(false), flikerTime(0.0f), duration(duration)
{
	type = (BuffEffect::Buff_Type)key;
	texture = DATA->GetBuffIconImage(key-1);
	shader = Shader::Add(L"Shader/Object.hlsl");
	color = D3DXCOLOR(1, 1, 1, 1);
}

void BuffIcon::Update()
{	
	World::Update();
	if (*duration <= 3)
	{
		if (isFliker)
		{
			color.a += DELTA * 5;

			if (color.a >= 1)
				isFliker = false;
		}
		else
		{
			color.a -= DELTA * 5;

			if (color.a <= 0.0)
				isFliker = true;
		}
	}
}

void BuffIcon::Render()
{
	shader->SetTexture("map", texture->GetTexture());
	shader->SetVector("color", &color, 4);
	shader->Begin();
	texture->Render();
	shader->End();
}