#include "framework.h"

World::World()
	:pos(0, 0), rot(0, 0, 0), scale(1, 1), pivot(0, 0), collider(0, 0), offset(0, 0)
{
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&P);
	D3DXMatrixIdentity(&IP);
	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&R);
	D3DXMatrixIdentity(&T);

	vertices.clear();
	VertexColor vertex;
	vertex.color = GREEN;
	vertex.position = { Left(), Top(), 0.0f };
	vertices.push_back(vertex);
	vertex.position = { Right(), Top(), 0.0f };
	vertices.push_back(vertex);
	vertex.position = { Right(), Bottom(), 0.0f };
	vertices.push_back(vertex);
	vertex.position = { Left(), Bottom(), 0.0f };
	vertices.push_back(vertex);
	vertex.position = { Left(), Top(), 0.0f };
	vertices.push_back(vertex);
}

void World::Update()
{
	D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
	D3DXMatrixRotationYawPitchRoll(&R, rot.y, rot.x, rot.z);
	D3DXMatrixTranslation(&T, pos.x, pos.y, 0.0f);

	D3DXMatrixTranslation(&P, pivot.x, pivot.y, 0.0f);
	D3DXMatrixInverse(&IP, NULL, &P);

	world = IP * S * R * T * P;
	if (parent != NULL)
		world *= *parent;
}

void World::SetWorld() 
{
	DEVICE->SetTransform(D3DTS_WORLD, &world);
}

void World::SetCollider(float x, float y)
{
	Vector2 pos = { world._41, world._42 };

	collider = { x , y };
	fixedOffset.x = offset.x * abs(scale.x);
	fixedOffset.y = offset.y * abs(scale.y);

	float left = pos.x - collider.x * 0.5f + offset.x;
	float right = pos.x + collider.x * 0.5f + offset.x;
	float top = pos.y - collider.y * 0.5f + offset.y;
	float bottom = pos.y + collider.y * 0.5f + offset.y;

	vertices.clear();
	VertexColor vertex;
	vertex.color = GREEN;
	vertex.position = { left, top, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { right, top, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { right, bottom, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { left, bottom, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { left, top, 0.0f };
	vertices.push_back(vertex);
}

void World::SetCollider(Vector2 value)
{
	Vector2 pos = { world._41, world._42 };

	collider = value;
	fixedOffset.x = offset.x * abs(scale.x);
	fixedOffset.y = offset.y * abs(scale.y);

	float left = pos.x - collider.x * 0.5f + offset.x;
	float right = pos.x + collider.x * 0.5f + offset.x;
	float top = pos.y - collider.y * 0.5f + offset.y;
	float bottom = pos.y + collider.y * 0.5f + offset.y;

	vertices.clear();
	VertexColor vertex;
	vertex.color = GREEN;
	vertex.position = { left, top, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { right, top, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { right, bottom, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { left, bottom, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { left, top, 0.0f };
	vertices.push_back(vertex);
}

void World::SetCollider(float radius)
{
	this->radius = radius;

	for (int i = 0; i < sectorCount; i++)
	{
		float angle = PI * 2.0f / sectorCount * i;

		VertexColor vertex;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = -sin(angle) * radius;
		vertex.color = RED;

		vertices.push_back(vertex);
	}

	vertices.push_back(vertices.front());
}

void World::SetCircle(float radius)
{
	this->radius = radius;

	for (int i = 0; i < sectorCount; i++)
	{
		float angle = PI * 2.0f / sectorCount * i;

		VertexColor vertex;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = -sin(angle) * radius;
		vertex.color = RED;

		circle.push_back(vertex);
	}

	circle.push_back(circle.front());
}

void World::SetSize(Vector2 value)
{
	collider = value;
	fixedOffset.x = offset.x * abs(scale.x);
	fixedOffset.y = offset.y * abs(scale.y);

	float left = -collider.x * 0.5f + offset.x;
	float right = collider.x * 0.5f + offset.x;
	float top = -collider.y * 0.5f + offset.y;
	float bottom = collider.y * 0.5f + offset.y;

	D3DCOLOR saveColor = vertices[0].color;

	vertices.clear();
	VertexColor vertex;
	vertex.color = saveColor;
	vertex.position = { left, top, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { right, top, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { right, bottom, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { left, bottom, 0.0f };
	vertices.push_back(vertex);
	vertex.position = { left, top, 0.0f };
	vertices.push_back(vertex);
}

void World::SetColor(D3DCOLOR color)
{
	if (vertices.size() < 4)
		return;

	for (int i = 0; i < 5; i++)
	{
		vertices[i].color = color;
	}
}

bool World::Collision(Vector2 pos)
{
	if (pos.x > Left() && pos.x < Right()) {
		if (pos.y > Top() && pos.y < Bottom()) {
			return true;
		}
	}
	return false;
}

bool World::Collision(World world)
{
	float minX = max(Left(), world.Left());
	float maxX = min(Right(), world.Right());
	float minY = max(Top(), world.Top());
	float maxY = min(Bottom(), world.Bottom());
	Vector2 temp = { maxX - minX, maxY - minY };
	if (temp.x > 0 && temp.y > 0)
		return true;
	return false;
}

bool World::Collision(World* world)
{
	float minX = max(Left(), world->Left());
	float maxX = min(Right(), world->Right());
	float minY = max(Top(), world->Top());
	float maxY = min(Bottom(), world->Bottom());
	Vector2 temp = { maxX - minX, maxY - minY };
	if (temp.x > 0 && temp.y > 0) { //충돌 여부 확인
		return true;
	}
	return false;
}

bool World::CollisionMove(World* world)
{
	float minX = max(Left(), world->Left());
	float maxX = min(Right(), world->Right());
	float minY = max(Top(), world->Top());
	float maxY = min(Bottom(), world->Bottom());
	Vector2 temp = { maxX - minX, maxY - minY };
	if (temp.x > 0 && temp.y > 0) { //충돌 여부 확인
		if (temp.x > temp.y) { //상하 충돌
			if (pos.y + offset.y > world->pos.y + world->offset.y) {
				world->pos.y = (Top() - world->collider.y * 0.5f) - world->offset.y;
			}
			else {
				world->pos.y = (Bottom() + world->collider.y * 0.5f) - world->offset.y;
			}
		}
		else { //좌우 충돌
			if (pos.x + offset.x > world->pos.x + world->offset.x) {
				world->pos.x = Left() - world->collider.x * 0.5f;
			}
			else {
				world->pos.x = Right() + world->collider.x * 0.5f;
			}
		}
		return true;
	}
	return false;
}

bool World::Collision(Vector4* dest, World* src1, World* src2) //src1이 src2를 밀어냄
{
	float minX = max(src1->Left(), src2->Left());
	float maxX = min(src1->Right(), src2->Right());
	float minY = max(src1->Top(), src2->Top());
	float maxY = min(src1->Bottom(), src2->Bottom());
	Vector2 temp = { maxX - minX, maxY - minY };
	dest->x = minX;
	dest->y = minY;
	dest->z = maxX;
	dest->w = maxY;
	if (temp.x > 0 && temp.y > 0) { //충돌 여부 확인
		if (temp.x >= temp.y) { //상하 충돌
			if (src1->GetPos()->y + src1->offset.y > src2->GetPos()->y) {
				src2->GetPos()->y -= temp.y;
			}
			else {
				src2->GetPos()->y += temp.y;
			}
		}
		else { //좌우 충돌
			if (src1->GetPos()->x > src2->GetPos()->x) {
				src2->GetPos()->x -= temp.x;
			}
			else {
				src2->GetPos()->x += temp.x;
			}
		}	
		return true;
	}
	return false;
}

bool World::ObbCollision(World* world)
{
	ObbDesc obbA = SetObb();
	ObbDesc obbB = world->SetObb();

	Vector2 nea1 = obbA.direction[0];
	Vector2 ea1 = nea1 * obbA.length[0];
	Vector2 nea2 = obbA.direction[1];
	Vector2 ea2 = nea2 * obbA.length[1];

	Vector2 neb1 = obbB.direction[0];
	Vector2 eb1 = neb1 * obbB.length[0];
	Vector2 neb2 = obbB.direction[1];
	Vector2 eb2 = neb2 * obbB.length[1];

	Vector2 distance = obbA.position - obbB.position;

	float lengthA = D3DXVec2Length(&ea1);
	float lengthB = SeparateAxis(nea1, eb1, eb2);
	float length = abs(D3DXVec2Dot(&distance, &nea1));
	if (length > lengthA + lengthB)
		return false;

	distance = obbA.position - obbB.position;
	lengthA = D3DXVec2Length(&ea2);
	lengthB = SeparateAxis(nea2, eb1, eb2);
	length = abs(D3DXVec2Dot(&distance, &nea2));
	if (length > lengthA + lengthB)
		return false;

	distance = obbA.position - obbB.position;
	lengthA = D3DXVec2Length(&eb1);
	lengthB = SeparateAxis(neb1, ea1, ea2);
	length = abs(D3DXVec2Dot(&distance, &neb1));
	if (length > lengthA + lengthB)
		return false;

	distance = obbA.position - obbB.position;
	lengthA = D3DXVec2Length(&eb2);
	lengthB = SeparateAxis(neb2, ea1, ea2);
	length = abs(D3DXVec2Dot(&distance, &neb2));
	if (length > lengthA + lengthB)
		return false;

	return true;
}

bool World::CollisionCircle(World* world)
{
	float distance;

	if (parent == NULL)
		distance = OP::Distance(pos, world->pos);
	else
		distance = OP::Distance(pos + offset, world->pos);

	return distance < radius;
}

bool World::CollisionCircleRect(World* world)
{
	Vector2 edge[4];
	edge[0] = { world->Left(), world->Top() };
	edge[1] = { world->Right(), world->Top() };
	edge[2] = { world->Left(), world->Bottom() };
	edge[3] = { world->Right(), world->Bottom() };

	for (int i = 0; i < 4; i++)
	{
		Vector2 vec = edge[i] - pos + offset;

		if (D3DXVec2Length(&vec) < radius)
			return true;
	}

	float left = pos.x + offset.x - radius;
	float right = pos.x + offset.x + radius;
	float top = pos.y + offset.y - radius;
	float bottom = pos.y + offset.y + radius;

	float minX = max(left, world->Left());
	float maxX = min(right, world->Right());
	float minY = max(top, world->Top());
	float maxY = min(bottom, world->Bottom());
	Vector2 temp = { maxX - minX, maxY - minY };
	if (temp.x > 0 && temp.y > 0) { //충돌 여부 확인
		return true;
	}
	return false;

	return false;
}

World::ObbDesc World::SetObb()
{
	ObbDesc desc;
	//desc.position = pos;
	desc.length[0] = HalfSize().x;
	desc.length[1] = HalfSize().y;
	
	D3DXVec2TransformCoord(&desc.position, &offset, &world);

	desc.direction[0] = { world._11, world._12 };
	desc.direction[1] = { world._21, world._22 };

	D3DXVec2Normalize(&desc.direction[0], &desc.direction[0]);
	D3DXVec2Normalize(&desc.direction[1], &desc.direction[1]);

	return desc;
}

float World::SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2)
{
	float r1 = abs(D3DXVec2Dot(&separate, &e1));
	float r2 = abs(D3DXVec2Dot(&separate, &e2));

	return r1 + r2;
}

void World::Render()
{
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetFVF(VertexColor::fvf);
	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, vertices.begin()._Ptr, sizeof(VertexColor));
}

void World::RenderBox()
{
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetFVF(VertexColor::fvf);
	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, vertices.begin()._Ptr, sizeof(VertexColor));
}

void World::RenderCircle()
{
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetFVF(VertexColor::fvf);
	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, vertices.size()-1, vertices.begin()._Ptr,
		sizeof(VertexColor));
}

void World::CircleRender()
{
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetFVF(VertexColor::fvf);
	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, circle.size() - 1, circle.begin()._Ptr,
		sizeof(VertexColor));
}
