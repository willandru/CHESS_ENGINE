#include "HighlightRenderer.h"

#include "ChessBoardRenderer.h"
#include "GameState.h"
#include "Renderer.h"
#include "Shader.h"

void HighlightRenderer::render(
    Shader& shader,
    uint8_t square,
    float r,
    float g,
    float b,
    float alpha)
{
    (void)alpha;

    const BoardLayout layout =
        ChessBoardRenderer::getLayout();

    const uint8_t row =
        GameState::getRow(square);

    const uint8_t col =
        GameState::getCol(square);

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
    render(
        shader,
        GameState::getSquare(4, 4),
        0.15f,
        0.85f,
        0.20f,
        0.45f
    );
}