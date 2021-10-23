#include "framework.h"

map<wstring, Shader*> Shader::totalShader;

Shader::Shader(wstring file) : file(file)
{
	D3DXCreateEffectFromFile(DEVICE, file.c_str(),
		NULL, NULL, D3DXSHADER_DEBUG, NULL, &shader, NULL);
}

Shader::~Shader()
{
	shader->Release();
}

Shader* Shader::Add(wstring file)
{
	if (totalShader.count(file) > 0)
	{
		return totalShader[file];
	}

	totalShader[file] = new Shader(file);

	return totalShader[file];
}

void Shader::Delete()
{
	for (auto shader : totalShader)
		delete shader.second;
}

void Shader::Begin(int passNum)
{
	shader->Begin(NULL, NULL);
	shader->BeginPass(passNum);
}

void Shader::End()
{
	shader->EndPass();
	shader->End();
}

void Shader::SetTexture(string param, LPDIRECT3DTEXTURE9 texture)
{
	shader->SetTexture(param.c_str(), texture);
}

void Shader::SetInt(string param, int data)
{
	shader->SetInt(param.c_str(), data);
}

void Shader::SetFloat(string param, float data)
{
	shader->SetFloat(param.c_str(), data);
}

void Shader::SetVector(string param, void* data, int count)
{
	shader->SetFloatArray(param.c_str(), (float*)data, count);
}

