#include <iostream>
#include <optional>

#include <GL/glew.h>
#include <SFML/Window.hpp>

// --------------------------------------------------
// OpenGL initialization
// --------------------------------------------------

bool InitializeOpenGL() {

    glewExperimental = GL_TRUE;

    GLenum result = glewInit();

    if (result != GLEW_OK) {

        std::cerr
            << "GLEW initialization failed: "
            << glewGetErrorString(result)
            << '\n';

        return false;
    }

    // GLEW can generate an invalid enum when
    // initializing with a Core Profile context.
    while (glGetError() != GL_NO_ERROR) {}

    // Enable depth testing for 3D rendering.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable back-face culling.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Dark 3D scene background.
    glClearColor(
        0.035f,
        0.055f,
        0.085f,
        1.0f
    );

    return true;
}

// --------------------------------------------------
// Print graphics information
// --------------------------------------------------

void PrintOpenGLInformation() {

    std::cout << "\n========== OPENGL INFORMATION ==========\n";

    std::cout
        << "Vendor: "
        << glGetString(GL_VENDOR)
        << '\n';

    std::cout
        << "Renderer: "
        << glGetString(GL_RENDERER)
        << '\n';

    std::cout
        << "OpenGL Version: "
        << glGetString(GL_VERSION)
        << '\n';

    std::cout
        << "GLSL Version: "
        << glGetString(GL_SHADING_LANGUAGE_VERSION)
        << '\n';

    std::cout << "========================================\n\n";
}

// --------------------------------------------------
// Main
// --------------------------------------------------

int main() {

    constexpr unsigned int WIDTH = 1280;
    constexpr unsigned int HEIGHT = 720;

    // Request OpenGL 3.3 Core Profile.
    sf::ContextSettings settings;

    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.attributeFlags =
        sf::ContextSettings::Attribute::Core;

    // Create the OpenGL window.
    sf::Window window(
        sf::VideoMode({WIDTH, HEIGHT}),
        "Rigid Body - 3D Simulation",
        sf::Style::Default,
        sf::State::Windowed,
        settings
    );

    if (!window.setActive(true)) {
        std::cerr << "Failed to activate OpenGL context\n";
        return 1;
    }
    window.setFramerateLimit(60);

    // Initialize GLEW.
    if (!InitializeOpenGL()) {
        return 1;
    }

    PrintOpenGLInformation();

    // Initial viewport.
    glViewport(0, 0, WIDTH, HEIGHT);

    // --------------------------------------------------
    // Application loop
    // --------------------------------------------------

    while (window.isOpen()) {

        // Handle events.
        while (const std::optional<sf::Event> event =
                   window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Handle window resizing.
            if (const auto* resized =
                    event->getIf<sf::Event::Resized>()) {

                glViewport(
                    0,
                    0,
                    static_cast<GLsizei>(resized->size.x),
                    static_cast<GLsizei>(resized->size.y)
                );
            }
        }

        // Clear color and depth buffers.
        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        // Present the rendered frame.
        window.display();
    }

    return 0;
}
