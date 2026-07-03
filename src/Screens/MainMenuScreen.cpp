#include "MainMenuScreen.h"
#include "ScreenManager.h"
#include "Window.h"
#include "InputMouse.h"
#include "UIConstants.h"

extern ScreenManager gScreenManager;
extern Window gWindow;

void MainMenuScreen::onEnter()
{
    shader.load("Shaders/texture.vert", "Shaders/texture.frag");

    float sw = (float)gWindow.getWindowWidth();
    float sh = (float)gWindow.getWindowHeight();

    float total = UI::ButtonHeight * 4 + UI::ButtonSpacing * 3;

    float x = (sw - UI::ButtonWidth) * 0.5f;
    float y = (sh - total) * 0.5f;

    btn2D = Button(x, y, UI::ButtonWidth, UI::ButtonHeight, "2D");
    btn25D = Button(x, y + 1 * (UI::ButtonHeight + UI::ButtonSpacing), UI::ButtonWidth, UI::ButtonHeight, "2.5D");
    btn3D = Button(x, y + 2 * (UI::ButtonHeight + UI::ButtonSpacing), UI::ButtonWidth, UI::ButtonHeight, "3D");
    exitBtn = Button(x, y + 3 * (UI::ButtonHeight + UI::ButtonSpacing), UI::ButtonWidth, UI::ButtonHeight, "EXIT");

    btn2D.setTexture("Assets/2d.png");
    btn25D.setTexture("Assets/25d.png");
    btn3D.setTexture("Assets/3d.png");
    exitBtn.setTexture("Assets/exit.png");

    btn2D.setOnClick([]()
    {
        gScreenManager.setScreen(ScreenType::Game);
    });

    btn25D.setOnClick([]()
    {
        gScreenManager.setScreen(ScreenType::Game);
    });

    btn3D.setOnClick([]()
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
    float mx, my;
    InputMouse::getUIPosition(mx, my);

    bool clicked = InputMouse::isButtonPressed(0);

    btn2D.update(mx, my, clicked);
    btn25D.update(mx, my, clicked);
    btn3D.update(mx, my, clicked);
    exitBtn.update(mx, my, clicked);
}

void MainMenuScreen::render()
{
    btn2D.render(shader);
    btn25D.render(shader);
    btn3D.render(shader);
    exitBtn.render(shader);
}

void MainMenuScreen::onExit()
{
}