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
    // WINDOW
    // =========================
    if (!gWindow.init(640, 360, "CHESS ENGINE", false))
        return -1;

    // centrar ventana (evita splash desplazado visualmente)
    {
        GLFWmonitor* m = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(m);

        glfwSetWindowPos(
            gWindow.getNative(),
            (mode->width - 640) / 2,
            (mode->height - 360) / 2
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

    ScreenType previousScreen = gScreenManager.getActiveScreen();

    // =========================
    // MAIN LOOP
    // =========================
    while (!gWindow.shouldClose())
    {
        // TIME
        gTime.update(gWindow.getTime());

        // EVENTS
        gWindow.pollEvents();

        // 🔥 CRÍTICO: sincronización framebuffer/UI
        glViewport(0, 0, gWindow.getWidth(), gWindow.getHeight());

        // INPUT
        InputKeyboard::update();
        InputMouse::update();

        // EXIT SHORTCUT
        if (InputKeyboard::isKeyPressed(GLFW_KEY_ESCAPE))
            gWindow.setShouldClose(true);

        // FRAME START
        Renderer::setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Renderer::beginFrame();

        // UPDATE
        gScreenManager.update(gTime);

        // SCREEN TRANSITION
        ScreenType current = gScreenManager.getActiveScreen();

        if (previousScreen == ScreenType::Splash &&
            current == ScreenType::MainMenu)
        {
            gWindow.setFullscreen(true);

            glViewport(0, 0, gWindow.getWidth(), gWindow.getHeight());
        }

        previousScreen = current;

        // RENDER
        gScreenManager.render();

        // FRAME END
        Renderer::endFrame();
        gWindow.swapBuffers();
    }

    // CLEANUP
    Renderer::shutdown();
    gWindow.shutdown();

    return 0;
}