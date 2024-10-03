#include "Application.h"

#include <Corrade/Containers/ArrayView.h>

#include <Magnum/GL/Context.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Version.h>

#include <Magnum/Math/Color.h>

Application::Application(const Arguments &arguments)
    : Magnum::Platform::Application{arguments, Configuration{}
                                                   .setTitle("Magnum Triangle Example")}
{
    using namespace Magnum;
    using namespace Math::Literals;

    struct TriangleVertex {
        Vector2 position;
        Color3 color;
    };

    const TriangleVertex vertices[]{
        {{0.f - 0.5f, 0.f - 0.5f}, 0xff0000_rgbf}, /* Left  vertex, red   color */
        {{0.f + 0.5f, 0.f - 0.5f}, 0x00ff00_rgbf}, /* Right vertex, green color */
        {{0.f + 0.0f, 0.f + 0.5f}, 0x0000ff_rgbf}  /* Top   vertex, blue  color */
    };

    m_mesh.setCount((Magnum::Int)(Containers::arraySize(vertices)))
        .addVertexBuffer(GL::Buffer{vertices}, 0,
                         Shaders::VertexColor2D::Position{},
                         Shaders::VertexColor2D::Color3{});

    GL::Renderer::setClearColor(0xa5c9ea_rgbf);

    using namespace Math::Literals;
    Debug{} << "Hello! This application is running on"
            << GL::Context::current().version() << "using"
            << GL::Context::current().rendererString().c_str();
}

void Application::drawEvent()
{
    using namespace Magnum;

    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    m_shader.draw(m_mesh);

    swapBuffers();
}

void Application::keyPressEvent(KeyEvent &event)
{
    if (event.key() == KeyEvent::Key::Esc)
        exit();
}
