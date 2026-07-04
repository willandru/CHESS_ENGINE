#include "GameScreen.h"

#include "ScreenManager.h"
#include "Window.h"
#include "InputMouse.h"
#include "UIConstants.h"

#include "ChessBoardRenderer.h"
#include "ChessPieceRenderer.h"
#include "HighlightRenderer.h"

extern ScreenManager gScreenManager;
extern Window gWindow;

void GameScreen::onEnter()
{
    //=========================================
    // SHADERS
    //=========================================

    shader.load(
        "Shaders/texture.vert",
        "Shaders/texture.frag"
    );

    boardShader.load(
        "Shaders/basic.vert",
        "Shaders/basic.frag"
    );

    //=========================================
    // PIECES
    //=========================================

    ChessPieceRenderer::init();

    //=========================================
    // BUTTONS
    //=========================================

    float sw = (float)gWindow.getWindowWidth();
    float sh = (float)gWindow.getWindowHeight();

    const float smallWidth = UI::ButtonWidth * 0.5f;

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

    bool clicked =
        InputMouse::isButtonPressed(0);

    back.update(mx, my, clicked);
    stop.update(mx, my, clicked);
    start.update(mx, my, clicked);
}

void GameScreen::render()
{
    //=========================================
    // TABLERO
    //=========================================

    ChessBoardRenderer::render(boardShader);

    //=========================================
    // DEBUG HIGHLIGHT
    //=========================================

    HighlightRenderer::renderDebug(boardShader);

    //=========================================
    // DEBUG PIECES
    //=========================================

    ChessPieceRenderer::render(
        shader,
        ChessPiece::BlackKing,
        0,
        4
    );

    ChessPieceRenderer::render(
        shader,
        ChessPiece::WhiteKing,
        7,
        4
    );

    ChessPieceRenderer::render(
        shader,
        ChessPiece::WhiteQueen,
        7,
        3
    );

    ChessPieceRenderer::render(
        shader,
        ChessPiece::BlackQueen,
        0,
        3
    );

    ChessPieceRenderer::render(
        shader,
        ChessPiece::WhitePawn,
        6,
        4
    );

    ChessPieceRenderer::render(
        shader,
        ChessPiece::BlackPawn,
        1,
        4
    );

    //=========================================
    // UI
    //=========================================

    back.render(shader);
    stop.render(shader);
    start.render(shader);
}

void GameScreen::onExit()
{
    ChessPieceRenderer::shutdown();
}