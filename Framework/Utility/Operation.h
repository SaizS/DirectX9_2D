#pragma once
#define OP Operation
#define LERP(s, e, t) {s + (e - s) * t}
#define PI 3.141592
class Operation
{
public:
	static int Random(int min, int max);
	static float Random(float min, float max);
	static float GetRadian(int angle) { return (float)(angle * (PI / 180)); }
	static D3DXVECTOR2 GetNomalize(D3DXVECTOR2 vector) { return { vector.x / VectorLength(vector), vector.y / VectorLength(vector) }; }
	static float VectorLength(D3DXVECTOR2 vector) { return sqrt(vector.x * vector.x + vector.y * vector.y); }
	static float Distance(Vector2 p1, Vector2 p2) { return VectorLength(p2 - p1); }
	static D3DXVECTOR3 Cross(float x1, float y1, float z1, float x2, float y2, float z2);
	static D3DXVECTOR3 Cross(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2);
	static float VecToAngle(D3DXVECTOR2 vec);
};

