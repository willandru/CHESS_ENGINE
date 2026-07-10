#include "ChessPieceRenderer3D.h"

#include <iostream>



//====================================================
// CONSTRUCTOR
//====================================================

ChessPieceRenderer3D::ChessPieceRenderer3D()
{
    transform.setScale(
    {
        0.8f,
        0.8f,
        0.8f
    });
}



//====================================================
// INITIALIZE
//====================================================

bool ChessPieceRenderer3D::initialize()
{
    bool ok = true;

    ok &= pieces[0].load(
        "Assets/peon.gltf"
    );

    ok &= pieces[1].load(
        "Assets/caballo.gltf"
    );

    ok &= pieces[2].load(
        "Assets/alfil.gltf"
    );

    ok &= pieces[3].load(
        "Assets/torre.gltf"
    );

    ok &= pieces[4].load(
        "Assets/dama.gltf"
    );

    ok &= pieces[5].load(
        "Assets/rey.gltf"
    );

    if(!ok)
    {
        std::cout
            << "[ChessPieceRenderer3D] ERROR loading pieces\n";
    }
    else
    {
        std::cout
            << "[ChessPieceRenderer3D] pieces loaded\n";
    }

    return ok;
}



//====================================================
// RENDER
//====================================================

void ChessPieceRenderer3D::render(
    Renderer3D& renderer,
    Shader3D& shader,
    Camera3D& camera,
    float aspectRatio,
    Piece piece,
    uint8_t square
)
{
    if(piece == Piece::EMPTY)
        return;

    int index = getPieceIndex(piece);

    if(index < 0)
        return;

    float x;
    float z;

    squareToWorld(
        square,
        x,
        z
    );

    transform.setPosition(
    {
        x,
        0.0f,
        z
    });

    renderer.draw(
        pieces[index].getMesh(),
        transform,
        shader,
        camera,
        aspectRatio
    );
}



//====================================================
// PIECE INDEX
//====================================================

int ChessPieceRenderer3D::getPieceIndex(
    Piece piece
) const
{
    switch(piece)
    {
        case Piece::WHITE_PAWN:
        case Piece::BLACK_PAWN:
            return 0;

        case Piece::WHITE_KNIGHT:
        case Piece::BLACK_KNIGHT:
            return 1;

        case Piece::WHITE_BISHOP:
        case Piece::BLACK_BISHOP:
            return 2;

        case Piece::WHITE_ROOK:
        case Piece::BLACK_ROOK:
            return 3;

        case Piece::WHITE_QUEEN:
        case Piece::BLACK_QUEEN:
            return 4;

        case Piece::WHITE_KING:
        case Piece::BLACK_KING:
            return 5;

        default:
            return -1;
    }
}



//====================================================
// BOARD POSITION
//====================================================

void ChessPieceRenderer3D::squareToWorld(
    uint8_t square,
    float& x,
    float& z
)
{
    int row = square / 8;
    int col = square % 8;

    x =
        col
        - 4.0f
        + 0.5f;

    z =
        row
        - 4.0f
        + 0.5f;
}