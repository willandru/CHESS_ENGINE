#pragma once

#include "Renderer3D.h"
#include "Shader3D.h"
#include "Camera3D.h"

#include "ChessBoardRenderer3D.h"
#include "ChessPieceRenderer3D.h"

#include <string>



class ChessRenderer3D
{
public:

    ChessRenderer3D();


    //------------------------------------------------
    // INITIALIZATION
    //------------------------------------------------

    bool initialize(
        const std::string& vertexShader,
        const std::string& fragmentShader
    );


    //------------------------------------------------
    // RENDER
    //------------------------------------------------

    void render();


    //------------------------------------------------
    // CAMERA
    //------------------------------------------------

    Camera3D& getCamera();


private:

    //------------------------------------------------
    // CORE
    //------------------------------------------------

    Renderer3D renderer;

    Shader3D shader;

    Camera3D camera;


    //------------------------------------------------
    // RENDERERS
    //------------------------------------------------

    ChessBoardRenderer3D boardRenderer;

    ChessPieceRenderer3D pieceRenderer;
};