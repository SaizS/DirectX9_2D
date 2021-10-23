#include "framework.h"
#include "Scene.h"

Scene::Scene() : isFadeIn(false), isFadeOut(false), isMapEditor(false)
{
	renderTarget = new RenderTarget(WIN_WIDTH, WIN_HEIGHT);
	shader = Shader::Add(L"Shader/MapShader.hlsl");
	color = D3DXCOLOR(1, 1, 1, 0);
}

Scene::~Scene()
{
	delete renderTarget;
}

void Scene::Render()
{
	if (KEYDOWN(VK_F7))
		isMapEditor ? isMapEditor = false : isMapEditor = true;

	FadeIn();
	FadeOut();

	shader->SetTexture("map", renderTarget->GetTexture());
	shader->SetVector("color", &color, 4);
	shader->Begin();
	renderTarget->Render();
	shader->End();
}

void Scene::SetFade(string key, Vector2 pos)
{
	if (isFadeIn)
		isFadeIn = false;

	isFadeOut = true;
	this->key = key;
	this->pos = pos;
}

void Scene::FadeIn()
{
	if (!isFadeIn)
		return;

	color.a += DELTA * 2;

	if (color.a >= 1.0f)
		isFadeIn = false;
}

void Scene::FadeOut()
{
	if (!isFadeOut)
		return;

	color.a -= DELTA * 2;

	if (color.a <= 0.0f)
	{
		SCENE->ChangeScene(key, pos);
		isFadeOut = false;
	}
}