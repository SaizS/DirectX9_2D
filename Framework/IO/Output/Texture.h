class Texture {
private:
	Vertex* vertices;
	LPDIRECT3DTEXTURE9 texture;
	Vector2 size;
	Vector2 cutStart;
	Vector2 cutEnd;
	Vector2 uvStart;
	Vector2 uvEnd;
public:
	Texture(LPDIRECT3DTEXTURE9 texture, Vector2 start = Vector2(0, 0), Vector2 end = Vector2(0, 0));
	Texture(LPDIRECT3DTEXTURE9 texture, int frameX, int frameY, int maxFrameX, int maxFrameY);
	~Texture();
	void Render();
	void AlphaRender();
	void SetSize(Vector2 size);
	Vector2 GetSize() { return size; }
	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
};