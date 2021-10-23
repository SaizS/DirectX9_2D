#include "framework.h"

Texture::Texture(LPDIRECT3DTEXTURE9 texture, Vector2 start, Vector2 end)
{
	this->texture = texture;
	D3DSURFACE_DESC surface;
	texture->GetLevelDesc(0, &surface);

	size.x = end.x == 0.0f ? surface.Width : end.x - start.x;
	size.y = end.y == 0.0f ? surface.Height : end.y - start.y;
	float halfX = size.x * 0.5f;
	float halfY = size.y * 0.5f;

	uvStart.x = start.x / surface.Width;
	uvStart.y = start.y / surface.Height;
	uvEnd.x = end.x == 0 ? 1.0f : end.x / surface.Width;
	uvEnd.y = end.y == 0 ? 1.0f : end.y / surface.Height;

	vertices = new Vertex[6];
	vertices[0] = Vertex(-halfX, -halfY, uvStart.x, uvStart.y);
	vertices[1] = Vertex(halfX, -halfY, uvEnd.x, uvStart.y);
	vertices[2] = Vertex(-halfX, halfY, uvStart.x, uvEnd.y);
	vertices[3] = Vertex(-halfX, halfY, uvStart.x, uvEnd.y);
	vertices[4] = Vertex(halfX, -halfY, uvEnd.x, uvStart.y);
	vertices[5] = Vertex(halfX, halfY, uvEnd.x, uvEnd.y);

}

Texture::Texture(LPDIRECT3DTEXTURE9 texture, int frameX, int frameY, int maxFrameX, int maxFrameY)
{
	this->texture = texture;
	D3DSURFACE_DESC surface;
	texture->GetLevelDesc(0, &surface);

	size.x = (float)(surface.Width / maxFrameX);
	size.y = (float)(surface.Height / maxFrameY);
	float halfX = size.x * 0.5f;
	float halfY = size.y * 0.5f;

	uvStart.x = frameX / (float)maxFrameX;
	uvStart.y = frameY / (float)maxFrameY;

	uvEnd.x = (frameX + 1) / (float)maxFrameX;
	uvEnd.y = (frameY + 1) / (float)maxFrameY;

	vertices = new Vertex[6];
	vertices[0] = Vertex(-halfX, -halfY, uvStart.x, uvStart.y);
	vertices[1] = Vertex(halfX, -halfY, uvEnd.x, uvStart.y);
	vertices[2] = Vertex(-halfX, halfY, uvStart.x, uvEnd.y);
	vertices[3] = Vertex(-halfX, halfY, uvStart.x, uvEnd.y);
	vertices[4] = Vertex(halfX, -halfY, uvEnd.x, uvStart.y);
	vertices[5] = Vertex(halfX, halfY, uvEnd.x, uvEnd.y);

	
}

Texture::~Texture()
{
	delete[] vertices;
}

void Texture::AlphaRender()
{
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetTexture(0, texture);

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//알파연산을 시작하겠다.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//알파연산은 덧셈으로 하겠다.
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//SRC : 원본 이미지(현재 비행기 이미지)
	//DEST : 그려질 뒷 이미지(현재 아이유 이미지)
	//SRCALPHA : 원본이미지의 알파값
	//INVSRCALPHA : 원본이미지 알파값의 역수(1 - SRCALPHA)
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertices, sizeof(Vertex));

	//알파연산을 끝내겠다.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void Texture::SetSize(Vector2 size)
{
	Vector2 halfSize = size * 0.5f;
	vertices[0] = Vertex(-halfSize.x, -halfSize.y, uvStart.x, uvStart.y);
	vertices[1] = Vertex(halfSize.x, -halfSize.y, uvEnd.x, uvStart.y);
	vertices[2] = Vertex(-halfSize.x, halfSize.y, uvStart.x, uvEnd.y);
	vertices[3] = Vertex(-halfSize.x, halfSize.y, uvStart.x, uvEnd.y);
	vertices[4] = Vertex(halfSize.x, -halfSize.y, uvEnd.x, uvStart.y);
	vertices[5] = Vertex(halfSize.x, halfSize.y, uvEnd.x, uvEnd.y);
}

void Texture::Render()
{
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetTexture(0, texture);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	/*
	//알파연산을 시작하겠다.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//알파연산은 덧셈으로 하겠다.
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//SRC : 원본 이미지(현재 비행기 이미지)
	//DEST : 그려질 뒷 이미지(현재 아이유 이미지)
	//SRCALPHA : 원본이미지의 알파값
	//INVSRCALPHA : 원본이미지 알파값의 역수(1 - SRCALPHA)
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	*/
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertices, sizeof(Vertex));

	//알파연산을 끝내겠다.
	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
