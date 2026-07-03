#include "MainMenuScreen.h"

#include "ScreenManager.h"
#include "Window.h"
#include "InputMouse.h"

#include <GLFW/glfw3.h>

#include <iostream>

extern ScreenManager gScreenManager;
extern Window gWindow;



void MainMenuScreen::onEnter()
{

    std::cout
    << gWindow.getWindowWidth()
    << " "
    << gWindow.getWindowHeight()
    << std::endl;
    shader.load("Shaders/basic.vert", "Shaders/basic.frag");

    constexpr float buttonWidth = 220.0f;
    constexpr float buttonHeight = 55.0f;
    constexpr float spacing = 20.0f;

    float screenWidth = static_cast<float>(gWindow.getWindowWidth());
    float screenHeight = static_cast<float>(gWindow.getWindowHeight());

    float x = (screenWidth - buttonWidth) * 0.5f;

    float totalHeight =
        buttonHeight +
        spacing +
        buttonHeight;

    float y = (screenHeight - totalHeight) * 0.5f;

    play = Button(
        x,
        y,
        buttonWidth,
        buttonHeight,
        "PLAY"
    );

    exitBtn = Button(
        x,
        y + buttonHeight + spacing,
        buttonWidth,
        buttonHeight,
        "EXIT"
    );

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

    bool clicked = InputMouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT);

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