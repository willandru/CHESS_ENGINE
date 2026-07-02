#include "Window.h"
#include "Renderer.h"
#include "ScreenManager.h"
#include "GameTime.h"

Window gWindow;
ScreenManager gScreenManager;
GameTime gTime;

int main() {

    // 1. Crear ventana + contexto OpenGL
    if (!gWindow.init(1920, 1080, "CHESS ENGINE", true))
        return -1;

    // 2. Inicializar sistema de pantallas
    gScreenManager.init();
    gScreenManager.setScreen(ScreenType::Splash);

    // 3. Inicializar tiempo
    gTime.init(gWindow.getTime());

    // 4. Loop principal (game loop)
    while (!gWindow.shouldClose()) {

        float now = gWindow.getTime();
        gTime.update(now);

        gWindow.pollEvents();

        Renderer::setClearColor(0,0,0,1);
        Renderer::beginFrame();

        gScreenManager.update(gTime);
        gScreenManager.render();

        gWindow.swapBuffers();
    }

    // 5. shutdown limpio
    gWindow.shutdown();

    return 0;
}