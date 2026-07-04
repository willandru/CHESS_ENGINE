#include "ChessPieceRenderer.h"
#include "Renderer.h"
#include "Shader.h"
#include "BoardView.h"

Texture ChessPieceRenderer::textures[12];

bool ChessPieceRenderer::init()
{
    bool ok = true;

    ok &= textures[0].loadFromFile("Assets/peon_blanco.png");
    ok &= textures[1].loadFromFile("Assets/caballo_blanco.png");
    ok &= textures[2].loadFromFile("Assets/alfil_blanco.png");
    ok &= textures[3].loadFromFile("Assets/torre_blanca.png");
    ok &= textures[4].loadFromFile("Assets/dama_blanca.png");
    ok &= textures[5].loadFromFile("Assets/rey_blanco.png");

    ok &= textures[6].loadFromFile("Assets/peon_negro.png");
    ok &= textures[7].loadFromFile("Assets/caballo_negro.png");
    ok &= textures[8].loadFromFile("Assets/alfil_negro.png");
    ok &= textures[9].loadFromFile("Assets/torre_negra.png");
    ok &= textures[10].loadFromFile("Assets/dama_negra.png");
    ok &= textures[11].loadFromFile("Assets/rey_negro.png");

    return ok;
}

void ChessPieceRenderer::shutdown()
{
    for (auto& t : textures)
        t.destroy();
}

void ChessPieceRenderer::render(
    Shader& shader,
    Piece piece,
    uint8_t square,
    const BoardView& view)
{
    if (piece == EMPTY)
        return;

    float x, y;
    view.squareToXY(square, x, y);

    int index = static_cast<int>(piece) - 1;
    if (index < 0 || index >= 12)
        return;

    Renderer::drawTextureRect(
        x,
        y,
        view.squareSize,
        view.squareSize,
        textures[index],
        shader
    );
}