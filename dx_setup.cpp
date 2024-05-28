#include "dx_setup.h"

DXSetup::DXSetup()
{
    //Does not need anything as of 5/27/2024
}

DXSetup::~DXSetup()
{
    //Does not need anything as of 5/27/2024

}

std::string DXSetup::Initialize(HWND hwnd, int width, int height)
{
    std::string error = CreateDeviceAndSwapChain(hwnd, width, height);
    if (!error.empty())
    {
        return "Failed to create device and swap chain: " + error;
    }

    error = CreateRenderTargetView();
    if (!error.empty())
    {
        return "Failed to create render target view: " + error;
    }

    return "";
}



std::string DXSetup::CreateDeviceAndSwapChain(HWND hwnd, int width, int height)
{
    DXGI_SWAP_CHAIN_DESC scd = { 0 };

    scd.BufferCount = 1;
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hwnd;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.Windowed = TRUE;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &scd,
        &swapChain,
        &device,
        nullptr,
        &deviceContext);

    if (FAILED(hr))
    {
        return "D3D11CreateDeviceAndSwapChain failed with error: " + std::to_string(hr);
    }

    return "";
}

std::string DXSetup::CreateRenderTargetView()
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    HRESULT hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView);

    if (FAILED(hr))
    {
        return "CreateRenderTargetView failed with error: " + std::to_string(hr);
    }

    return "";
}



