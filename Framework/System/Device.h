#pragma once
#define DEVICE Device::Get()->GetDevice()

class Device
{
private:
	static Device* instance;

	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 device;

	Device();
	~Device();
public:
	static Device* Get();
	static void Create();
	static void Delete();

	LPDIRECT3DDEVICE9 GetDevice() { return device; }
};