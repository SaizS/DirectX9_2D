#pragma once

class RenderTarget : public World {
private:
	UINT width, height;
	Vertex* vertices;

	LPDIRECT3DTEXTURE9 renderTarget;
	LPDIRECT3DSURFACE9 depthStencil;
	LPD3DXRENDERTOSURFACE renderSurface;
	D3DFORMAT colorFormat;
	D3DFORMAT depthFormat;

	Shader* shader;
public:
	Color color;
	RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	~RenderTarget();
	void Begin(DWORD color = BLACK);
	void End();
	void Render();
	LPDIRECT3DTEXTURE9 GetTexture() { return renderTarget; }
};