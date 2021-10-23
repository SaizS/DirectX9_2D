#define EFFECT EffectManager::GetInstance()

class EffectManager
{
private:
	static EffectManager* instance;
	typedef vector<Effect*> Effects;
	EffectManager();
	~EffectManager();
	map<string, Effects> effectList;
public:
	static EffectManager* GetInstance();
	static void Create();
	static void Delete();
	void Update();
	void Render();
	void Add(string key, wstring fileName, int frameX, int frameY, int poolingCount, float speed = 0.1f, int pass = 0);
	void Play(string key, Vector2 pos);

	vector<Effect*> GetEffect(string key);
};

