#include "framework.h"

RenderTarget::RenderTarget(UINT width, UINT height)
{
	LPDIRECT3DSURFACE9 colorSurface;
	LPDIRECT3DSURFACE9 depthSurface;

	DEVICE->GetRenderTarget(0, &colorSurface);
	DEVICE->GetDepthStencilSurface(&depthSurface);

	D3DSURFACE_DESC colorDesc;
	colorSurface->GetDesc(&colorDesc);
	D3DSURFACE_DESC depthDesc;
	depthSurface->GetDesc(&depthDesc);

	colorSurface->Release();
	depthSurface->Release();

	colorFormat = colorDesc.Format;
	depthFormat = depthDesc.Format;

	DEVICE->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, colorFormat, D3DPOOL_DEFAULT, &renderTarget, NULL);
	renderTarget->GetSurfaceLevel(0, &depthStencil);
	DEVICE->ColorFill(depthStencil, NULL, RED);
	D3DXCreateRenderToSurface(DEVICE, width, height, colorFormat, TRUE, depthFormat, &renderSurface);
	vertices = new Vertex[6];
	vertices[0] = Vertex(0, 0, 0, 0);
	vertices[1] = Vertex(width, 0, 1, 0);
	vertices[2] = Vertex(0, height, 0, 1);
	vertices[3] = Vertex(0, height, 0, 1);
	vertices[4] = Vertex(width, 0, 1, 0);
	vertices[5] = Vertex(width, height, 1, 1);
}

RenderTarget::~RenderTarget()
{
	renderTarget->Release();
	depthStencil->Release();
	delete[] vertices;
}

void RenderTarget::Begin(DWORD color)
{
	renderSurface->BeginScene(depthStencil, NULL);
	DEVICE->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);
}
void RenderTarget::End()
{
	renderSurface->EndScene(0);
}

void RenderTarget::Render()
{
	Update();
	SetWorld();
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetTexture(0, renderTarget);

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertices, sizeof(Vertex));
}
