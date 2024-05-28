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
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() const;

	
private:

	std::string CreateDeviceAndSwapChain(HWND hwnd, int width, int height);
	std::string CreateRenderTargetView();
	std::string CompileShaders();
	std::string CreateInputLayout();
	
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

