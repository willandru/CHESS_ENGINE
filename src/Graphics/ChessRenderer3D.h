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



    bool initialize(
        const std::string& vertexShader,
        const std::string& fragmentShader
    );



    void render(
        const ChessGame& game,
        Camera3D& camera
    );



    int pickPiece(
        const ChessGame& game,
        Camera3D& camera,
        float mouseX,
        float mouseY
    );



private:


    Renderer3D renderer;


    Shader3D boardShader;

    Shader3D pieceShader;



    ChessBoardRenderer3D boardRenderer;

    HighlightRenderer3D highlightRenderer;

    ChessPieceRenderer3D pieceRenderer;

};