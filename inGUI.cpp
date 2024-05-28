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

    std::tie(mouse_pos[0], mouse_pos[1]) = inputHandler->GetMousePosition();
    MOUSE_LBUTTON_DOWN = inputHandler->IsMouseButtonDown();
    // You might also want to clear or update other state here, depending on your needs
}

bool INGUI::GUI::button(Id id, float x, float y, size_t width, size_t height)
{
    // Check if the renderer is initialized
    if (!renderer) {
        throw std::runtime_error("Renderer is not initialized");
    }

    // Draw the button
    renderer->DrawButton(x, y, width, height);

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

void INGUI::DirectXRenderer::DrawButton(float x, float y, size_t width, size_t height)
{
    // Create a rectangle to represent the button
	RECT buttonRect;
	buttonRect.left = x;
	buttonRect.top = y;
	buttonRect.right = x + width;
	buttonRect.bottom = y + height;

	// Draw the button
	// You can use the rectangle to draw the button using the DirectX API
	// For example, you can use the rectangle to draw a rectangle with a border
	// and a background color, or you can use it to draw a texture
	// You can also use the rectangle to check if the mouse is over the button
	// and if the mouse button is pressed
	// You can also use the rectangle to check if the button is active
	// and if it is, you can set the active element to the button's id
   
}