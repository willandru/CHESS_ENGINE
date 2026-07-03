#include "MainMenuScreen.h"

#include "ScreenManager.h"
#include "Window.h"
#include "InputMouse.h"
#include "UIConstants.h"

#include <iostream>

extern ScreenManager gScreenManager;
extern Window gWindow;

void MainMenuScreen::onEnter()
{
    shader.load("Shaders/basic.vert", "Shaders/basic.frag");

    // =========================
    // SCREEN SIZE (DINÁMICO)
    // =========================
    float screenWidth  = static_cast<float>(gWindow.getWindowWidth());
    float screenHeight = static_cast<float>(gWindow.getWindowHeight());

    // =========================
    // LAYOUT CALCULATION
    // =========================
    float totalHeight =
        UI::ButtonHeight +
        UI::ButtonSpacing +
        UI::ButtonHeight;

    float x = (screenWidth - UI::ButtonWidth) * 0.5f;

    float y = (screenHeight - totalHeight) * 0.5f;

    // =========================
    // BUTTONS
    // =========================
    play = Button(
        x,
        y,
        UI::ButtonWidth,
        UI::ButtonHeight,
        "PLAY"
    );

    exitBtn = Button(
        x,
        y + UI::ButtonHeight + UI::ButtonSpacing,
        UI::ButtonWidth,
        UI::ButtonHeight,
        "EXIT"
    );

    // =========================
    // EVENTS
    // =========================
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
    InputMouse::getUIPosition(mx, my);

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