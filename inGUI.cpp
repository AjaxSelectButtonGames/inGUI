#include "inGUI.h"


void INGUI::GUI::begin()
{
    // Clear the active element at the start of each frame
    active = "";

    // Reset mouse button states
    MOUSE_LBUTTON_DOWN = false;
    MOUSE_LBUTTON_UP = false;
    MOUSE_RBUTTON_DOWN = false;
    MOUSE_RBUTTON_UP = false;

    // You might also want to clear or update other state here, depending on your needs
}

bool INGUI::GUI::button(Id id, float x, float y, size_t width, size_t height)
{
	//call the rendering function to draw the button DirectX support as of right now
	//drawButton(x, y, width, height);

	return false;

}

void INGUI::GUI::end()
{


}