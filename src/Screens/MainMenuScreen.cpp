#include "MainMenuScreen.h"

#include "ScreenManager.h"
#include "Window.h"

extern ScreenManager gScreenManager;
extern Window gWindow;

void MainMenuScreen::onEnter()
{
    shader.load(
        "Shaders/basic.vert",
        "Shaders/basic.frag");

    play = Button(
        100,
        100,
        200,
        50,
        "PLAY");

    exit = Button(
        100,
        200,
        200,
        50,
        "EXIT");

    play.setOnClick([]()
    {
        gScreenManager.setScreen(ScreenType::Game);
    });

    exit.setOnClick([]()
    {
        gWindow.shutdown();
    });
}

void MainMenuScreen::update(float dt)
{
    (void)dt;

    // Temporal.
    // Más adelante se reemplazará por el sistema Input.
    play.update(
        150,
        120,
        false);

    exit.update(
        150,
        220,
        false);
}

void MainMenuScreen::render()
{
    play.render(shader);
    exit.render(shader);
}

void MainMenuScreen::onExit()
{
}