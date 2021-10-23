#pragma once

class Shader
{
private:
	wstring file;

	LPD3DXEFFECT shader;
	static map<wstring, Shader*> totalShader;

	Shader(wstring file);
	~Shader();

public:
	static Shader* Add(wstring file);
	static void Delete();

	void Begin(int passNum = 0);
	void End();

	void SetTexture(string param, LPDIRECT3DTEXTURE9 texture);
	void SetInt(string param, int data);
	void SetFloat(string param, float data);
	void SetVector(string param, void* data, int count);
};