#ifndef GUI_H
#define GUI_H
#include <vector>
#include <string>
#include <wrl/client.h> // For Microsoft::WRL::ComPtr
#include <d3d11.h> // For ID3D11DeviceContext
#include <string>
#include <memory>

namespace INGUI
{
    class Renderer
    {
    public:
        virtual ~Renderer() = default;
        virtual void DrawButton(float x, float y, size_t width, size_t height) = 0;
    };

    class DirectXRenderer : public Renderer
    {
    public:
        DirectXRenderer(Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext)
            : deviceContext(deviceContext) {}

        void DrawButton(float x, float y, size_t width, size_t height) override;

    private:
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
    };

    class GUI
    {
    public:
        using Id = std::string;

        GUI(std::unique_ptr<Renderer> renderer) : renderer(std::move(renderer)) {}

        std::vector<float> mouse_pos; //mouse posistion on the screen
        bool MOUSE_LBUTTON_DOWN; //Left mouse button pressed
        bool MOUSE_LBUTTON_UP; //Left mouse button released
        bool MOUSE_RBUTTON_DOWN; //right mouse button pressed
        bool MOUSE_RBUTTON_UP; //Right mouse button released
        Id active;

        void begin();
        bool button(Id id, float x, float y, size_t width, size_t height);
        void end();

    private:
        std::unique_ptr<Renderer> renderer;
    };
}
#endif // !GUI_H
