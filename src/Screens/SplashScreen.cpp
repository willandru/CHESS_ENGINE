#include "SplashScreen.h"
#include "Renderer.h"

void SplashScreen::onEnter()
{
}

void SplashScreen::update(float dt)
{
    // Nada.
}

void SplashScreen::render()
{
    Renderer::setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer::beginFrame();
}

void SplashScreen::onExit()
{
}