#include "framework.h"
int Operation::Random(int min, int max) //min ~ max까지 출력
{
	if (max < min)
		return 0;
	return rand() % (max + 1 - min) + min;
}

float Operation::Random(float min, float max) {
	float random = (float)rand() / (float)RAND_MAX;
	float temp = max - min;
	return min + temp * random;
}

D3DXVECTOR3 Operation::Cross(float x1, float y1, float z1, float x2, float y2, float z2)
{
	D3DXVECTOR3 result;
	D3DXVECTOR3 cross1 = { x1, y1, z1 };
	D3DXVECTOR3 cross2 = { x2, y2, z2 };
	D3DXVec3Cross(&result, &cross1, &cross2);
	return result;
}

D3DXVECTOR3 Operation::Cross(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2)
{
	D3DXVECTOR3 result;
	D3DXVec3Cross(&result, &vec1, &vec2);
	return result;
}

float Operation::VecToAngle(D3DXVECTOR2 vec)
{
	return atan2(vec.y, vec.x);
}