#pragma once

#include "ChessPieceMesh3D.h"
#include "Transform3D.h"

#include "Renderer3D.h"
#include "Shader3D.h"
#include "Camera3D.h"

#include "ChessTypes.h"

#include <array>



class ChessPieceRenderer3D
{
public:

    ChessPieceRenderer3D();

    //------------------------------------------------
    // LOAD
    //------------------------------------------------

    bool initialize();

    //------------------------------------------------
    // RENDER
    //------------------------------------------------

    void render(
        Renderer3D& renderer,
        Shader3D& shader,
        Camera3D& camera,
        float aspectRatio,
        Piece piece,
        uint8_t square
    );

private:

    //------------------------------------------------
    // MODELS
    //------------------------------------------------

    std::array<ChessPieceMesh3D,6> pieces;

    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    Transform3D transform;

    //------------------------------------------------
    // HELPERS
    //------------------------------------------------

    int getPieceIndex(
        Piece piece
    ) const;

    void squareToWorld(
        uint8_t square,
        float& x,
        float& z
    );
};