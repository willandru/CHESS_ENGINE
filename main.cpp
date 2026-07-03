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
    constexpr int WindowWidth  = 640;
    constexpr int WindowHeight = 360;

    // =========================
    // WINDOW
    // =========================
    if (!gWindow.init(WindowWidth, WindowHeight, "CHESS ENGINE", false))
        return -1;

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
        // 1. eventos OS
        gWindow.pollEvents();

        // 2. input update (orden crítico)
        InputKeyboard::update();
        InputMouse::update();

        // 3. timing
        gTime.update(gWindow.getTime());

        // 4. ESC
        if (InputKeyboard::isKeyPressed(GLFW_KEY_ESCAPE))
            gWindow.setShouldClose(true);

        // 5. render setup
        Renderer::setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Renderer::beginFrame();

        // 6. update + render
        gScreenManager.update(gTime);
        gScreenManager.render();

        // 7. swap
        gWindow.swapBuffers();
    }

    // =========================
    // CLEANUP
    // =========================
    Renderer::shutdown();
    gWindow.shutdown();

    return 0;
}