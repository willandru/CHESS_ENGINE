#pragma once

#include "Renderer3D.h"
#include "Shader3D.h"
#include "Camera3D.h"

#include "ChessBoardRenderer3D.h"
#include "ChessPieceRenderer3D.h"
#include "HighlightRenderer3D.h"
#include "PiecePicker3D.h"

#include <string>
#include <cstdint>

class ChessGame;

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

    void render(
        const ChessGame& game
    );

    //------------------------------------------------
    // PICKING
    //------------------------------------------------

    int pickPiece(
        const ChessGame& game,
        float mouseX,
        float mouseY
    );

    //------------------------------------------------
    // CAMERA
    //------------------------------------------------

    void updateCamera(
        const ChessGame& game
    );

    Camera3D& getCamera();

private:

    //------------------------------------------------
    // CAMERA HELPERS
    //------------------------------------------------

    void focusCameraOnSquare(
        const ChessGame& game,
        uint8_t square
    );

    //------------------------------------------------
    // CORE
    //------------------------------------------------

    Renderer3D renderer;

    //------------------------------------------------
    // SHADERS
    //------------------------------------------------

    Shader3D boardShader;
    Shader3D pieceShader;

    //------------------------------------------------
    // CAMERA
    //------------------------------------------------

    Camera3D camera;

    //------------------------------------------------
    // CAMERA FOLLOW STATE
    //------------------------------------------------

    bool followingPiece = false;

    uint8_t followedSquare = 0;

    //------------------------------------------------
    // RENDERERS
    //------------------------------------------------

    ChessBoardRenderer3D boardRenderer;
    HighlightRenderer3D highlightRenderer;
    ChessPieceRenderer3D pieceRenderer;
};