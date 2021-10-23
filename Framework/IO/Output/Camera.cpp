#include "framework.h"
Camera* Camera::instance = NULL;

Camera::Camera() : pos(0, 0), speed(800), target(NULL), mapSize(-WIN_WIDTH, -WIN_HEIGHT, WIN_WIDTH, WIN_HEIGHT),
isFocus(true), angle(0.0f), scale(1, 1), rot(1, 1), offset(WIN_HALFWIDTH, WIN_HALFHEIGHT), isFix(true)
{
	D3DXMatrixIdentity(&view);
}

Camera::~Camera()
{
}

void Camera::Create()
{
	instance = new Camera();
}

void Camera::Delete()
{
	delete instance;
}

void Camera::Update()
{
	if (KEYDOWN(VK_F8))
	{
		if (isFocus)
		{
			//isFix = false;
			isFocus = false;
		}
		else
		{
			//isFix = true;
			isFocus = true;
		}
	}

	if (KEYDOWN(VK_F7))
	{
		if (isFix)
		{
			//isFix = false;
			isFix = false;
		}
		else
		{
			//isFix = true;
			isFix = true;
		}
	}

	if (KEYDOWN(VK_F9))
		target = nullptr;

	Move();
	Render();
	Shaking();

	D3DXMatrixScaling(&S, scale.x, scale.y, 0.0f);
	D3DXMatrixRotationZ(&R, angle);
	D3DXMatrixTranslation(&T, pos.x, pos.y, 0.0f);

	Matrix P, IP;
	Vector2 pivot = offset - pos;
	D3DXMatrixTranslation(&P, pivot.x, pivot.y, 0.0f);
	D3DXMatrixInverse(&IP, NULL, &P);

	view = IP * S * R * T * P;
}

void Camera::Render()
{
	if (isFocus && target != NULL) {
		pos.x = -target->GetPos()->x + WIN_HALFWIDTH;
		pos.y = -target->GetPos()->y + WIN_HALFHEIGHT;
	}

	if (isFix)
	{
		if (pos.y < mapSize.w)
			pos.y = mapSize.w;
		if (pos.x < mapSize.z)
			pos.x = mapSize.z;
		if (pos.y > mapSize.y)
			pos.y = mapSize.y;
		if (pos.x > mapSize.x)
			pos.x = mapSize.x;
	}

	if (isShake) {
		D3DXMatrixTranslation(&view, pos.x + shakeRadius.x, pos.y + shakeRadius.y, 0.0f);
	}
	else {
		D3DXMatrixTranslation(&view, pos.x, pos.y, 0.0f);
	}
}

void Camera::Move()
{
	if (!isFocus && target == NULL) {
		if (KEYPRESS(VK_RIGHT)) {
			pos.x -= speed * DELTA;
		}
		if (KEYPRESS(VK_LEFT)) {
			pos.x += speed * DELTA;
		}
		if (KEYPRESS(VK_UP)) {
			pos.y += speed * DELTA;
		}
		if (KEYPRESS(VK_DOWN)) {
			pos.y -= speed * DELTA;
		}
	}
}

void Camera::Shake(float power, float duration, bool isVertical)
{
	isShake = true;
	this->isVertical = isVertical;
	shakeDuration = duration;
	shakePower = power / duration;
}

void Camera::Shaking()
{
	if (!isShake)
		return;
	shakeDuration -= DELTATIME;
	if (shakeDuration < 0) {
		isShake = false;
		return;
	}
	if (int(shakeDuration * 100) % 2 == 1) {
		if (isVertical)
			shakeRadius.y = shakePower * shakeDuration;
		else
			shakeRadius.x = shakePower * shakeDuration;
	}
	else {
		if (isVertical)
			shakeRadius.y = -(shakePower * shakeDuration);
		else
			shakeRadius.x = -(shakePower * shakeDuration);
	}
}