#include "framework.h"

Effect::Effect(wstring fileName, int frameX, int frameY, float speed, int pass) : pass(pass), color(0xffffffff)
{
	vector<Texture*> clips;
	clips.clear();
	for (int j = 0; j < frameY; j++) {
		for (int i = 0; i < frameX; i++) {
			clips.push_back(TEXTURE->Add(fileName, i, j, frameX, frameY, MAGENTA));
		}
	}
	ani = new Animation(clips, Type::END, speed);
	ani->SetEndEvent(bind(&Effect::Stop, this));
	shader = Shader::Add(L"Shader/Effect.hlsl");
	isActive = false;
}

Effect::~Effect()
{
	delete ani;
}

void Effect::Render()
{
	if (!isActive)
		return;
	SetWorld();
	shader->SetTexture("map", ani->GetTexture());
	shader->SetVector("color", (float*)& color, 4);
	shader->Begin(pass);
	ani->Render();
	shader->End();
}

void Effect::Play(Vector2 pos)
{
	SetPos(pos);
	ani->Play();
	isActive = true;
}

void Effect::Update()
{
	if (!isActive)
		return;


	ani->Update();
	World::Update();
	
}
