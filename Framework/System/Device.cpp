#include "framework.h"

Device* Device::instance = NULL;

Device::Device()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS param = {};
	param.Windowed = true;
	param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	param.AutoDepthStencilFormat = D3DFMT_D16;
	param.EnableAutoDepthStencil = true;
	param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&param,
		&device
	);

	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, WIN_WIDTH,
		WIN_HEIGHT, 0.0f, -1.0f, 1.0f);

	device->SetTransform(D3DTS_PROJECTION, &projection);

	device->SetRenderState(D3DRS_LIGHTING, false);
}

Device::~Device()
{
	d3d->Release();
	device->Release();
}

Device* Device::Get()
{
	return instance;
}

void Device::Create()
{
	instance = new Device();
}

void Device::Delete()
{
	delete instance;
}
