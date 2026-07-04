#include "HighlightRenderer.h"
#include "Renderer.h"
#include "BoardView.h"

void HighlightRenderer::render(
    Shader& shader,
    uint8_t square,
    float r,
    float g,
    float b,
    const BoardView& view)
{
    float x, y;
    view.squareToXY(square, x, y);

    Renderer::drawRect(
        x,
        y,
        view.squareSize,
        view.squareSize,
        r,
        g,
        b,
        shader
    );
}