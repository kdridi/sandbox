#include <Magnum/GL/Mesh.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/VertexColor.h>

class Application : public Magnum::Platform::Application {
public:
    explicit Application(const Arguments &arguments);

private:
    void drawEvent() override;
    void keyPressEvent(KeyEvent &event) override;

    Magnum::GL::Mesh m_mesh;
    Magnum::Shaders::VertexColor2D m_shader;
};
