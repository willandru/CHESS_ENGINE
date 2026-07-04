#include "ChessBoardRenderer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Window.h"
#include "BoardView.h"

extern Window gWindow;

void ChessBoardRenderer::render(Shader& shader)
{
    BoardView v = BoardView::compute(
        gWindow.getWindowWidth(),
        gWindow.getWindowHeight()
    );

    constexpr float light[3] = {0.93f, 0.87f, 0.73f};
    constexpr float dark[3]  = {0.48f, 0.59f, 0.34f};

    for (uint8_t r = 0; r < 8; ++r)
    for (uint8_t c = 0; c < 8; ++c)
    {
        float x = v.x + c * v.squareSize;
        float y = v.y + r * v.squareSize;

        bool isLight = ((r + c) & 1) == 0;

        const float* col = isLight ? light : dark;

        Renderer::drawRect(
            x, y,
            v.squareSize, v.squareSize,
            col[0], col[1], col[2],
            shader
        );
    }
}