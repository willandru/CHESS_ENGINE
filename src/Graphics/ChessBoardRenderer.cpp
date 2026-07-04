#include "ChessBoardRenderer.h"

#include "Renderer.h"
#include "Shader.h"
#include "Window.h"

extern Window gWindow;

void ChessBoardRenderer::render(Shader& shader)
{
    const float screenWidth  = static_cast<float>(gWindow.getWindowWidth());
    const float screenHeight = static_cast<float>(gWindow.getWindowHeight());

    // =====================================================
    // BOARD SIZE
    // =====================================================

    const float boardSize = screenHeight * 0.85f;
    const float squareSize = boardSize / 8.0f;

    // =====================================================
    // POSITION
    // =====================================================

    const float boardX = (screenWidth - boardSize) * 0.5f;
    const float boardY = (screenHeight - boardSize) * 0.5f;

    // =====================================================
    // COLORS
    // =====================================================

    constexpr float lightR = 0.93f;
    constexpr float lightG = 0.87f;
    constexpr float lightB = 0.73f;

    constexpr float darkR = 0.48f;
    constexpr float darkG = 0.59f;
    constexpr float darkB = 0.34f;

    // =====================================================
    // DRAW
    // =====================================================

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            const float x = boardX + col * squareSize;
            const float y = boardY + row * squareSize;

            const bool lightSquare = ((row + col) % 2 == 0);

            if (lightSquare)
            {
                Renderer::drawRect(
                    x,
                    y,
                    squareSize,
                    squareSize,
                    lightR,
                    lightG,
                    lightB,
                    shader
                );
            }
            else
            {
                Renderer::drawRect(
                    x,
                    y,
                    squareSize,
                    squareSize,
                    darkR,
                    darkG,
                    darkB,
                    shader
                );
            }
        }
    }
}