#include "ChessPieceRenderer.h"

#include "ChessBoardRenderer.h"
#include "Renderer.h"
#include "Shader.h"

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
    for (Texture& texture : textures)
    {
        texture.destroy();
    }
}

void ChessPieceRenderer::render(
    Shader& shader,
    ChessPiece piece,
    int row,
    int col)
{
    if (piece == ChessPiece::None)
        return;

    BoardLayout layout = ChessBoardRenderer::getLayout();

    const float x =
        layout.x + col * layout.squareSize;

    const float y =
        layout.y + row * layout.squareSize;

    const int index =
        static_cast<int>(piece) - 1;

    Renderer::drawTextureRect(
        x,
        y,
        layout.squareSize,
        layout.squareSize,
        textures[index],
        shader
    );
}