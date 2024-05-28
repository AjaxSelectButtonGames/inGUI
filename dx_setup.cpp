#include "dx_setup.h"
#include <d3dcompiler.h>

DXSetup::DXSetup()
{
    // Constructor code
}

DXSetup::~DXSetup()
{
    // Destructor code
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

    error = CompileShaders();
    if (!error.empty())
    {
        return "Failed to compile shaders: " + error;
    }

    error = CreateInputLayout();
    if (!error.empty())
    {
        return "Failed to create input layout: " + error;
    }

    return "";
}

std::string DXSetup::CompileShaders()
{
    const char* vertexShaderSrc = R"(
    struct VS_INPUT {
        float4 Pos : POSITION;
        float4 Col : COLOR;
    };

    struct PS_INPUT {
        float4 Pos : SV_POSITION;
        float4 Col : COLOR;
    };

    PS_INPUT VS(VS_INPUT input) {
        PS_INPUT output;
        output.Pos = input.Pos;
        output.Col = input.Col;
        return output;
    }
    )";

    const char* pixelShaderSrc = R"(
    struct PS_INPUT {
        float4 Pos : SV_POSITION;
        float4 Col : COLOR;
    };

    float4 PS(PS_INPUT input) : SV_TARGET {
        return input.Col;
    }
    )";

    Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderBlob;
    Microsoft::WRL::ComPtr<ID3DBlob> pixelShaderBlob;
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

    HRESULT hr = D3DCompile(vertexShaderSrc, strlen(vertexShaderSrc), nullptr, nullptr, nullptr, "VS", "vs_5_0", 0, 0, &vertexShaderBlob, &errorBlob);
    if (FAILED(hr))
    {
        if (errorBlob) {
            return std::string(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
        }
        return "Failed to compile vertex shader.";
    }

    hr = D3DCompile(pixelShaderSrc, strlen(pixelShaderSrc), nullptr, nullptr, nullptr, "PS", "ps_5_0", 0, 0, &pixelShaderBlob, &errorBlob);
    if (FAILED(hr))
    {
        if (errorBlob) {
            return std::string(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
        }
        return "Failed to compile pixel shader.";
    }

    hr = device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vertexShader);
    if (FAILED(hr))
    {
        return "Failed to create vertex shader.";
    }

    hr = device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &pixelShader);
    if (FAILED(hr))
    {
        return "Failed to create pixel shader.";
    }

    deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);

    return "";
}

std::string DXSetup::CreateInputLayout()
{
    D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderBlob;
    HRESULT hr = D3DCompile(vertexShaderSrc, strlen(vertexShaderSrc), nullptr, nullptr, nullptr, "VS", "vs_5_0", 0, 0, &vertexShaderBlob, nullptr);
    if (FAILED(hr))
    {
        return "Failed to compile vertex shader for input layout.";
    }

    hr = device->CreateInputLayout(layoutDesc, ARRAYSIZE(layoutDesc), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &inputLayout);
    if (FAILED(hr))
    {
        return "Failed to create input layout.";
    }

    deviceContext->IASetInputLayout(inputLayout.Get());

    return "";
}
