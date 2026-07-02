#include "SplashScreen.h"
#include "ScreenManager.h"
#include "Renderer.h"

extern ScreenManager gScreenManager;

void SplashScreen::onEnter() {
    t = 0.0f;
}

void SplashScreen::update(float dt) {
    t += dt;

    if (t > 1.0f) {
        gScreenManager.setScreen(ScreenType::MainMenu);
    }
}

void SplashScreen::render() {
    Renderer::setClearColor(0,0,0,1);
    Renderer::beginFrame();
}

void SplashScreen::onExit() {}