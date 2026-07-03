#include "Window.h"
#include "Renderer.h"
#include "ScreenManager.h"
#include "GameTime.h"

Window gWindow;
ScreenManager gScreenManager;
GameTime gTime;

int main()
{
    // Crear ventana y contexto OpenGL
    if (!gWindow.init(640, 360, "CHESS ENGINE", false))
        return -1;

    // Inicializar renderer
    if (!Renderer::init())
    {
        gWindow.shutdown();
        return -1;
    }

    // Inicializar tiempo
    gTime.init(gWindow.getTime());

    // Inicializar gestor de pantallas
    gScreenManager.init();
    gScreenManager.setScreen(ScreenType::Splash);

    // Detectar transición Splash -> MainMenu
    ScreenType previousScreen = gScreenManager.getActiveScreen();

    while (!gWindow.shouldClose())
    {
        // Actualizar tiempo
        gTime.update(gWindow.getTime());

        // Eventos
        gWindow.pollEvents();

        // Comenzar frame
        Renderer::setClearColor(
            0.0f,
            0.0f,
            0.0f,
            1.0f);

        Renderer::beginFrame();

        // Actualizar pantalla activa
        gScreenManager.update(gTime);

        // Cambiar a pantalla completa al salir del Splash
        if (previousScreen == ScreenType::Splash &&
            gScreenManager.getActiveScreen() == ScreenType::MainMenu)
        {
            gWindow.setFullscreen(true);
        }

        previousScreen = gScreenManager.getActiveScreen();

        // Dibujar pantalla activa
        gScreenManager.render();

        // Finalizar frame
        Renderer::endFrame();

        // Presentar imagen
        gWindow.swapBuffers();
    }

    // Liberar recursos
    Renderer::shutdown();
    gWindow.shutdown();

    return 0;
}