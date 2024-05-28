#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <string>
class DXSetup
{
public:
	DXSetup();
	~DXSetup();

	std::string Initialize(HWND hwnd, int width, int height);

private:

	std::string CreateDeviceAndSwapChain(HWND hwnd, int width, int height);
	std::string CreateRenderTargetView();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
};

