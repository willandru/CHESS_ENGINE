#include "ChessBoardRenderer.h"

#include "Renderer.h"
#include "Shader.h"
#include "Window.h"

extern Window gWindow;

BoardLayout ChessBoardRenderer::getLayout()
{
    BoardLayout layout;

    const float screenWidth =
        static_cast<float>(gWindow.getWindowWidth());

    const float screenHeight =
        static_cast<float>(gWindow.getWindowHeight());

    layout.boardSize = screenHeight * 0.85f;

    layout.squareSize =
        layout.boardSize / 8.0f;

    layout.x =
        (screenWidth - layout.boardSize) * 0.5f;

    layout.y =
        (screenHeight - layout.boardSize) * 0.5f;

    return layout;
}

void ChessBoardRenderer::render(Shader& shader)
{
    const BoardLayout layout = getLayout();

    constexpr float lightR = 0.93f;
    constexpr float lightG = 0.87f;
    constexpr float lightB = 0.73f;

    constexpr float darkR = 0.48f;
    constexpr float darkG = 0.59f;
    constexpr float darkB = 0.34f;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            const float x =
                layout.x + col * layout.squareSize;

            const float y =
                layout.y + row * layout.squareSize;

            const bool lightSquare =
                ((row + col) % 2 == 0);

            if (lightSquare)
            {
                Renderer::drawRect(
                    x,
                    y,
                    layout.squareSize,
                    layout.squareSize,
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
                    layout.squareSize,
                    layout.squareSize,
                    darkR,
                    darkG,
                    darkB,
                    shader
                );
            }
        }
    }
}