#include "inGUI.h"


void INGUI::GUI::begin()
{
    if (!inputHandler) {
        throw std::runtime_error("Input handler is not initialized");
    }

    // Clear the active element at the start of each frame
    active = "";

    // Reset mouse button states
    MOUSE_LBUTTON_DOWN = false;
    MOUSE_LBUTTON_UP = false;
    MOUSE_RBUTTON_DOWN = false;
    MOUSE_RBUTTON_UP = false;

    // Check if the mouse_pos vector has at least 2 elements
    if (mouse_pos.size() < 2) {
        throw std::runtime_error("mouse_pos vector does not have enough elements");
    }

    try {
        std::tie(mouse_pos[0], mouse_pos[1]) = inputHandler->GetMousePosition();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting mouse position: " << e.what() << std::endl;
        throw;
    }

    try {
        MOUSE_LBUTTON_DOWN = inputHandler->IsMouseButtonDown();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting mouse button state: " << e.what() << std::endl;
        throw;
    }

    // You might also want to clear or update other state here, depending on your needs
}


bool INGUI::GUI::button(Id id, float x, float y, size_t width, size_t height)
{
    // Check if the renderer is initialized
    if (!renderer) {
        throw std::runtime_error("Renderer is not initialized");
    }

    // Draw the button
    renderer->DrawButton(10, 10, 100, 50, { 1.0f, 0.0f, 0.0f }); // Red color

    // Check if the mouse is over the button
    bool isMouseOver = (mouse_pos[0] >= x && mouse_pos[0] <= x + width &&
        mouse_pos[1] >= y && mouse_pos[1] <= y + height);

    // If the mouse is over the button and the left mouse button is down,
    // set the active element to the button's id
    if (isMouseOver && MOUSE_LBUTTON_DOWN) {
        active = id;
    }

    // Return true if the button is the active element
    return (active == id);
}


void INGUI::GUI::end()
{
	// You might want to do some cleanup here, depending on your needs

}

void INGUI::DirectXRenderer::DrawButton(float x, float y, size_t width, size_t height, const Color& color)
{
    // Create a rectangle to represent the button
    Vertex vertices[] = {
        { x, y, 0.0f, color.r, color.g, color.b, 1.0f },
        { x + width, y, 0.0f, color.r, color.g, color.b, 1.0f },
        { x, y + height, 0.0f, color.r, color.g, color.b, 1.0f },
        { x + width, y + height, 0.0f, color.r, color.g, color.b, 1.0f }
    };

    // Use the DirectX resources to draw the button...
    deviceContext->DrawIndexed(6, 0, 0);
}


std::pair<float, float> INGUI::WindowsInputHandler::GetMousePosition() const
{
    POINT point;
    if (GetCursorPos(&point))
    {
        // Convert the screen coordinates to client coordinates
        ScreenToClient(GetActiveWindow(), &point);
        return std::make_pair(static_cast<float>(point.x), static_cast<float>(point.y));
    }
    else
    {
        // Return an invalid position if GetCursorPos fails
        return std::make_pair(-1.0f, -1.0f);
    }
}

bool INGUI::WindowsInputHandler::IsMouseButtonDown() const
{
    return (GetKeyState(VK_LBUTTON) & 0x100) != 0;
}

void INGUI::DirectXRenderer::InitializeDirectXResources()
{
    // Initialize your DirectX resources here...
    // This might include creating vertex buffers, index buffers, shaders, etc.
}