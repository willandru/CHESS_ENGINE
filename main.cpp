#include "Window.h"
#include "Renderer.h"
#include "ScreenManager.h"
#include "GameTime.h"

Window gWindow;
ScreenManager gScreenManager;
GameTime gTime;

int main()
{
    // Ventana inicial del Splash
    if (!gWindow.init(640, 360, "CHESS ENGINE", false))
        return -1;

    // Tiempo
    gTime.init(gWindow.getTime());

    // Pantallas
    gScreenManager.init();
    gScreenManager.setScreen(ScreenType::Splash);

    // Para detectar el cambio Splash -> MainMenu
    ScreenType previousScreen = gScreenManager.getActiveScreen();

    while (!gWindow.shouldClose())
    {
        gTime.update(gWindow.getTime());

        gWindow.pollEvents();

        Renderer::setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Renderer::beginFrame();

        gScreenManager.update(gTime);

        // Si acabamos de salir del Splash,
        // cambiar la ventana a pantalla completa.
        if (previousScreen == ScreenType::Splash &&
            gScreenManager.getActiveScreen() == ScreenType::MainMenu)
        {
            gWindow.setFullscreen(true);
        }

        previousScreen = gScreenManager.getActiveScreen();

        gScreenManager.render();

        Renderer::endFrame();

        gWindow.swapBuffers();
    }

    gWindow.shutdown();

    return 0;
}