#include "GameScreen.h"

#include "ScreenManager.h"

extern ScreenManager gScreenManager;

void GameScreen::onEnter()
{
    shader.load(
        "Shaders/basic.vert",
        "Shaders/basic.frag");

    back = Button(
        100,
        100,
        200,
        50,
        "BACK");

    back.setOnClick([]()
    {
        gScreenManager.setScreen(ScreenType::MainMenu);
    });
}

void GameScreen::update(float dt)
{
    (void)dt;

    // Temporal.
    back.update(
        150,
        120,
        false);
}

void GameScreen::render()
{
    back.render(shader);
}

void GameScreen::onExit()
{
}