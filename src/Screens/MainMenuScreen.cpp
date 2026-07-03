#include "MainMenuScreen.h"

#include "ScreenManager.h"
#include "Window.h"
#include "InputMouse.h"

extern ScreenManager gScreenManager;
extern Window gWindow;

void MainMenuScreen::onEnter()
{
    shader.load("Shaders/basic.vert", "Shaders/basic.frag");

    play = Button(100, 100, 200, 50, "PLAY");
    exitBtn = Button(100, 200, 200, 50, "EXIT");

    play.setOnClick([]()
    {
        gScreenManager.setScreen(ScreenType::Game);
    });

    exitBtn.setOnClick([]()
    {
        gWindow.setShouldClose(true);
    });
}

void MainMenuScreen::update(float dt)
{
    (void)dt;

    float mx, my;
    InputMouse::getUIPosition(mx, my);  // ✔ NORMALIZADO EN INPUT

    bool clicked = InputMouse::isButtonPressed(0);

    play.update(mx, my, clicked);
    exitBtn.update(mx, my, clicked);
}

void MainMenuScreen::render()
{
    play.render(shader);
    exitBtn.render(shader);
}

void MainMenuScreen::onExit()
{
}