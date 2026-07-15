#pragma once

#include "ChessPieceMesh3D.h"
#include "Transform3D.h"
#include "Material3D.h"

#include "Renderer3D.h"
#include "Shader3D.h"
#include "Camera3D.h"

#include "ChessTypes.h"

#include <array>
#include <glm/glm.hpp>


class ChessPieceRenderer3D
{
public:

    ChessPieceRenderer3D();


    //------------------------------------------------
    // LOAD
    //------------------------------------------------

    bool initialize();



    //------------------------------------------------
    // MATERIAL
    //------------------------------------------------

    Material3D& getWhiteMaterial();

    Material3D& getBlackMaterial();



    //------------------------------------------------
    // MESH
    //------------------------------------------------

    const Mesh3D& getMesh(
        Piece piece
    ) const;



    //------------------------------------------------
    // TRANSFORM
    //------------------------------------------------

    Transform3D buildTransform(
        Piece piece,
        uint8_t square
    ) const;



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



    //------------------------------------------------
    // WORLD POSITION
    //------------------------------------------------

    glm::vec3 getWorldPosition(
        uint8_t square
    ) const;



private:


    //------------------------------------------------
    // MODELS
    //------------------------------------------------

    std::array<ChessPieceMesh3D,6> pieces;



    //------------------------------------------------
    // DEFAULT TRANSFORM
    //------------------------------------------------

    Transform3D transform;



    //------------------------------------------------
    // MATERIAL
    //------------------------------------------------

    Material3D whiteMaterial;

    Material3D blackMaterial;



    //------------------------------------------------
    // HELPERS
    //------------------------------------------------

    int getPieceIndex(
        Piece piece
    ) const;



    float getPieceYOffset(
        Piece piece
    ) const;



    void squareToWorld(
        uint8_t square,
        float& x,
        float& z
    ) const;

};