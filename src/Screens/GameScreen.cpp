#include "GameScreen.h"

#include "ScreenManager.h"
#include "Window.h"
#include "InputMouse.h"
#include "UIConstants.h"

#include "BoardView.h"
#include "ChessRenderer.h"
#include "ChessPieceRenderer.h"

extern ScreenManager gScreenManager;
extern Window gWindow;

void GameScreen::onEnter()
{
    //-----------------------------------------
    // SHADERS
    //-----------------------------------------

    shader.load(
        "Shaders/texture.vert",
        "Shaders/texture.frag"
    );

    boardShader.load(
        "Shaders/basic.vert",
        "Shaders/basic.frag"
    );

    //-----------------------------------------
    // GAME
    //-----------------------------------------

    game.reset();

    //-----------------------------------------
    // PIECES
    //-----------------------------------------

    ChessPieceRenderer::init();

    //-----------------------------------------
    // BUTTONS
    //-----------------------------------------

    const float sw = (float)gWindow.getWindowWidth();
    const float sh = (float)gWindow.getWindowHeight();

    const float smallWidth =
        UI::ButtonWidth * 0.5f;

    const float y =
        sh - UI::ButtonHeight - UI::ButtonSpacing;

    const float backX =
        UI::ButtonSpacing;

    const float stopX =
        (sw - (smallWidth * 2.0f + UI::ButtonSpacing)) * 0.5f;

    const float startX =
        stopX + smallWidth + UI::ButtonSpacing;

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

    //-----------------------------------------
    // BUTTONS
    //-----------------------------------------

    back.update(mx, my, clicked);
    stop.update(mx, my, clicked);
    start.update(mx, my, clicked);

    //-----------------------------------------
    // BOARD CLICK
    //-----------------------------------------

    if (!clicked)
        return;

    BoardView view = BoardView::compute(
        gWindow.getWindowWidth(),
        gWindow.getWindowHeight()
    );

    if (mx < view.x ||
        mx >= view.x + view.size ||
        my < view.y ||
        my >= view.y + view.size)
    {
        return;
    }

    uint8_t col =
        static_cast<uint8_t>((mx - view.x) / view.squareSize);

    uint8_t row =
        static_cast<uint8_t>((my - view.y) / view.squareSize);

    uint8_t square =
        GameState::getSquare(row, col);

    game.onSquareClicked(square);
}

void GameScreen::render()
{
    ChessRenderer::render(
        boardShader,
        shader,
        game
    );

    back.render(shader);
    stop.render(shader);
    start.render(shader);
}

void GameScreen::onExit()
{
    ChessPieceRenderer::shutdown();
}