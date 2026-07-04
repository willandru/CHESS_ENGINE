#include "HighlightRenderer.h"

#include "ChessBoardRenderer.h"
#include "Renderer.h"
#include "Shader.h"

void HighlightRenderer::render(
    Shader& shader,
    int row,
    int col,
    float r,
    float g,
    float b,
    float alpha)
{
    (void)alpha;

    BoardLayout layout = ChessBoardRenderer::getLayout();

    const float x =
        layout.x + col * layout.squareSize;

    const float y =
        layout.y + row * layout.squareSize;

    Renderer::drawRect(
        x,
        y,
        layout.squareSize,
        layout.squareSize,
        r,
        g,
        b,
        shader
    );
}

void HighlightRenderer::renderDebug(Shader& shader)
{
    // Resalta la casilla (4,4)
    render(
        shader,
        0,
        0,
        0.1f,
        0.8f,
        0.2f
    );
}