#include "Window.h"
#include "Renderer.h"
#include "ScreenManager.h"
#include "GameTime.h"

#include "InputKeyboard.h"
#include "InputMouse.h"

#include <GLFW/glfw3.h>

Window gWindow;
ScreenManager gScreenManager;
GameTime gTime;

int main()
{
    // =========================
    // CONFIG
    // =========================
    constexpr int WindowWidth  = 640;
    constexpr int WindowHeight = 360;

    // =========================
    // WINDOW
    // =========================
    if (!gWindow.init(WindowWidth, WindowHeight, "CHESS ENGINE", false))
        return -1;

    // Centrar ventana inicial
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwSetWindowPos(
            gWindow.getNative(),
            (mode->width - WindowWidth) / 2,
            (mode->height - WindowHeight) / 2
        );
    }

    // =========================
    // RENDERER
    // =========================
    if (!Renderer::init())
    {
        gWindow.shutdown();
        return -1;
    }

    // =========================
    // INPUT
    // =========================
    InputKeyboard::init(gWindow.getNative());
    InputMouse::init(gWindow.getNative());

    // =========================
    // TIME
    // =========================
    gTime.init(gWindow.getTime());

    // =========================
    // SCREENS
    // =========================
    gScreenManager.init();
    gScreenManager.setScreen(ScreenType::Splash);

    // =========================
    // MAIN LOOP
    // =========================
    while (!gWindow.shouldClose())
    {
        // Eventos
        gWindow.pollEvents();

        // Tiempo
        gTime.update(gWindow.getTime());

        // Input
        InputKeyboard::update();
        InputMouse::update();

        // Salir con ESC
        if (InputKeyboard::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            gWindow.setShouldClose(true);
        }

        // Inicio del frame
        Renderer::setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Renderer::beginFrame();

        // Actualización
        gScreenManager.update(gTime);

        // Render
        gScreenManager.render();

        // Fin del frame
        Renderer::endFrame();
        gWindow.swapBuffers();
    }

    // =========================
    // CLEANUP
    // =========================
    Renderer::shutdown();
    gWindow.shutdown();

    return 0;
}