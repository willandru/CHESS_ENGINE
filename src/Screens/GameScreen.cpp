#include "GameScreen.h"

#include "ScreenManager.h"
#include "Window.h"
#include "InputMouse.h"
#include "UIConstants.h"

extern ScreenManager gScreenManager;
extern Window gWindow;

void GameScreen::onEnter()
{
    shader.load("Shaders/texture.vert", "Shaders/texture.frag");

    float sw = (float)gWindow.getWindowWidth();
    float sh = (float)gWindow.getWindowHeight();

    const float smallWidth = UI::ButtonWidth * 0.5f;

    const float y = sh - UI::ButtonHeight - UI::ButtonSpacing;

    const float backX = UI::ButtonSpacing;

    const float stopX = (sw - (smallWidth * 2.0f + UI::ButtonSpacing)) * 0.5f;

    const float startX = stopX + smallWidth + UI::ButtonSpacing;

    back = Button(
        backX,
        y,
        UI::ButtonWidth,
        UI::ButtonHeight,
        "BACK"
    );

    stop = Button(
        stopX,
        y,
        smallWidth,
        UI::ButtonHeight,
        "STOP"
    );

    start = Button(
        startX,
        y,
        smallWidth,
        UI::ButtonHeight,
        "START"
    );

    back.setTexture("Assets/back.png");
    stop.setTexture("Assets/stop.png");
    start.setTexture("Assets/start.png");

    back.setOnClick([]()
    {
        gScreenManager.setScreen(ScreenType::MainMenu);
    });

    stop.setOnClick([]()
    {
        // TODO
    });

    start.setOnClick([]()
    {
        // TODO
    });
}

void GameScreen::update(float dt)
{
    (void)dt;

    float mx, my;
    InputMouse::getUIPosition(mx, my);

    bool clicked = InputMouse::isButtonPressed(0);

    back.update(mx, my, clicked);
    stop.update(mx, my, clicked);
    start.update(mx, my, clicked);
}

void GameScreen::render()
{
    back.render(shader);
    stop.render(shader);
    start.render(shader);
}

void GameScreen::onExit()
{
}