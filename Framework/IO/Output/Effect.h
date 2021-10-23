
class Effect : public Info
{
private:
	Animation* ani;

	Shader* shader;
	D3DXCOLOR color;

	int pass;
	bool isActive;
	
public:
	Effect(wstring fileName, int frameX, int frameY, float speed = 0.1f, int pass = 0);
	~Effect();


	bool IsActive() { return isActive; }
	void Stop() { isActive = false; }
	
	void Play(Vector2 pos);

	virtual void Update() override;
	virtual void Render() override;
};