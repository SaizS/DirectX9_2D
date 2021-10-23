class World
{
protected:
	struct VertexColor { //����
		Vector3 position;
		D3DCOLOR color;
		static const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	};
	vector<VertexColor> vertices;
	vector<VertexColor> circle;

	struct ObbDesc {
		Vector2 position;
		Vector2 direction[2];
		float length[2];
	};	
	
	Vector2 pivot;//���� - ��ȯ ������
	Matrix world;
	Matrix* parent;
	Matrix P, IP, S, R, T;

	float radius;

	const int sectorCount = 36;
public:
	Vector2 pos; //��ġ - ��ǥ
	Vector3 rot; //ȸ�� - ȸ������
	Vector2 scale; //ũ�� ����
	Vector2 offset;
	Vector2 collider;//�浹 ���� ũ��
	Vector2 fixedOffset;

	World();
	virtual ~World() {};
	void Update();
	void SetWorld();
	

	void SetPos(float x, float y) { pos = { x, y }; }
	void SetPos(Vector2 value) { pos = value; }
	Vector2* GetPos() { return &pos; } 

	void SetCollider(float x, float y);
	void SetCollider(Vector2 value);
	void SetCollider(float radius);
	void SetRadius(float radius) { this->radius = radius; }
	void SetCircle(float radius);
	void SetSize(Vector2 value);
	Vector2* GetColider() { return &collider; } 

	void SetOffset(float x, float y) {	offset = { x , y };	}
	void SetOffset(Vector2 value) { offset = value; }
	void ReverseOffsetX() { offset.x *= -1.0f; fixedOffset.x *= -1.0f; }
	Vector2 GetOffset() { return offset; }

	Vector2 HalfSize() { return {collider.x * 0.5f * abs(scale.x), collider.y * 0.5f * abs(scale.y) }; }
	float Top() { 
		return pos.y - HalfSize().y + offset.y; 
	}
	float Bottom() {
		return pos.y + HalfSize().y + offset.y; 
	}
	float Right() {
		return pos.x + HalfSize().x + offset.x; 
	}
	float Left() {
		return pos.x - HalfSize().x + offset.x; 
	}

	void SetRot(float x, float y, float z) { rot = { x, y, z}; }
	void SetRot(Vector3 value) { rot = value; }
	Vector3* GetRot() { return &rot; } 

	void SetScale(float x, float y) { scale = { x, y }; }
	void SetScale(Vector2 value) { scale = value; }
	Vector2* GetScale() { return &scale; } 

	void SetPivot(float x, float y) { pivot = { x, y }; }
	void SetPivot(Vector2 value) { pivot = value; }
	Vector2* GetPivot() { return &pivot; } 

	void SetColor(D3DCOLOR color);

	Matrix* GetWorld() { return &world; } 
	void SetParent(Matrix* value) { parent = value; } //�θ� ���� ����

	bool Collision(Vector2 pos);
	bool Collision(World world);
	bool Collision(World* world);
	bool CollisionMove(World* world);
	static bool Collision(Vector4* dest, World* src1, World* src2);
	bool ObbCollision(World* world);
	bool CollisionCircle(World* world);
	bool CollisionCircleRect(World* world);

	World::ObbDesc SetObb();
	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2);
	void Render();

	void RenderBox();
	void RenderCircle();
	void CircleRender();
};