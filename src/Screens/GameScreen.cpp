#include "GameScreen.h"

#include "ScreenManager.h"
#include "InputMouse.h"

extern ScreenManager gScreenManager;

void GameScreen::onEnter()
{
    shader.load("Shaders/basic.vert", "Shaders/basic.frag");

    back = Button(100, 100, 200, 50, "BACK");

    back.setOnClick([]()
    {
        gScreenManager.setScreen(ScreenType::MainMenu);
    });
}

void GameScreen::update(float dt)
{
    (void)dt;

    float mx, my;
    InputMouse::getUIPosition(mx, my);   // ✔ IMPORTANTE: UI SPACE UNIFICADO

    bool clicked = InputMouse::isButtonPressed(0);

    back.update(mx, my, clicked);
}

void GameScreen::render()
{
    back.render(shader);
}

void GameScreen::onExit()
{
}