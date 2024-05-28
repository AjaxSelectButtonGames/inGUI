//DEMO FOR INGUI
#include "ingui.h"
#include "dx_setup.h"


HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow)
{
    const wchar_t* windowClassName = L"MyWindowClass";

    // Register the window class
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = DefWindowProc; // Default window procedure
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = windowClassName;

    if (!RegisterClassEx(&wc))
    {
        throw std::runtime_error("Failed to register the window class");
    }

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        windowClassName,
        L"My Window", // Window title
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, // Window position
        800, 600, // Window size
        NULL, NULL, // Parent window and menu
        hInstance,
        NULL // Additional application data
    );

    if (!hwnd)
    {
        throw std::runtime_error("Failed to create the window");
    }

    // Show the window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return hwnd;
}



int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCMDShow = SW_SHOWDEFAULT;
    // Initialize your window here...
    HWND hwnd = InitializeWindow(hInstance,nCMDShow);
    int width = 800;
    int height = 600;

    // Initialize your DirectX setup...
    DXSetup dxSetup;
    std::string error = dxSetup.Initialize(hwnd, width, height);
    if (!error.empty())
    {
        // Handle error...
    }

    // Get the device context from dxSetup...
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext = dxSetup.GetDeviceContext();

    // Create the renderer, inputHandler, and gui instances
    auto renderer = std::make_unique<INGUI::DirectXRenderer>(deviceContext);
    auto inputHandler = std::make_unique<INGUI::WindowsInputHandler>();
    INGUI::GUI gui(std::move(renderer), std::move(inputHandler));

    // Enter the main loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // Call gui.begin() at the start of each frame...
            gui.begin();

            // Call gui.button() for each button you want to draw...
            gui.button("button1", 10, 10, 100, 50);

            // Call gui.end() at the end of each frame...
            gui.end();
        }
    }

    return 0;
}

