#include "ChessRenderer3D.h"

#include "ChessGame.h"
#include "GameState.h"
#include "Window.h"

#include <glm/glm.hpp>

#include <iostream>
#include <cfloat>

extern Window gWindow;



//====================================================
// CONSTRUCTOR
//====================================================

ChessRenderer3D::ChessRenderer3D()
{
}



//====================================================
// INITIALIZATION
//====================================================

bool ChessRenderer3D::initialize(
    const std::string& vertexShader,
    const std::string& fragmentShader
)
{
    //------------------------------------------------
    // BOARD SHADER
    //------------------------------------------------

    if(
        !boardShader.load(
            vertexShader,
            fragmentShader
        )
    )
    {
        return false;
    }

    //------------------------------------------------
    // PIECE SHADER
    //------------------------------------------------

    if(
        !pieceShader.load(
            "Shaders/basic_piece_3d.vert",
            "Shaders/basic_piece_3d.frag"
        )
    )
    {
        return false;
    }

    //------------------------------------------------
    // OPENGL
    //------------------------------------------------

    renderer.enableDepthTest();
    renderer.enableFaceCulling();

    //------------------------------------------------
    // LOAD PIECES
    //------------------------------------------------

    if(
        !pieceRenderer.initialize()
    )
    {
        return false;
    }

    return true;
}



//====================================================
// RENDER
//====================================================

void ChessRenderer3D::render(
    const ChessGame& game
)
{
    renderer.beginFrame(
        glm::vec4(
            0.15f,
            0.15f,
            0.18f,
            1.0f
        )
    );

    float aspectRatio =
        static_cast<float>(
            gWindow.getWindowWidth()
        )
        /
        static_cast<float>(
            gWindow.getWindowHeight()
        );

    //------------------------------------------------
    // BOARD
    //------------------------------------------------

    boardRenderer.render(
        renderer,
        boardShader,
        camera,
        aspectRatio
    );

    //------------------------------------------------
    // HIGHLIGHTS
    //------------------------------------------------

    highlightRenderer.render(
        renderer,
        boardShader,
        camera,
        aspectRatio,
        game
    );

    //------------------------------------------------
    // PIECES
    //------------------------------------------------

    const GameState& state =
        game.getGameState();

    const Piece* board =
        state.getBoard();

    for(
        uint8_t square = 0;
        square < 64;
        ++square
    )
    {
        pieceRenderer.render(
            renderer,
            pieceShader,
            camera,
            aspectRatio,
            board[square],
            square
        );
    }

    renderer.endFrame();
}


//====================================================
// PICK PIECE
//====================================================

int ChessRenderer3D::pickPiece(
    const ChessGame& game,
    float mouseX,
    float mouseY
)
{
    const GameState& state =
        game.getGameState();

    const Piece* board =
        state.getBoard();

    float bestDistance =
        FLT_MAX;

    int pickedSquare =
        -1;

    for(
        uint8_t square = 0;
        square < 64;
        ++square
    )
    {
        Piece piece =
            board[square];

        if(piece == Piece::EMPTY)
            continue;

        Transform3D transform =
            pieceRenderer.buildTransform(
                square
            );

        float distance;

        if(
            PiecePicker3D::intersectMesh(
                mouseX,
                mouseY,
                gWindow.getWindowWidth(),
                gWindow.getWindowHeight(),
                camera,
                pieceRenderer.getMesh(piece),
                transform,
                distance
            )
        )
        {
            if(distance < bestDistance)
            {
                bestDistance =
                    distance;

                pickedSquare =
                    square;
            }
        }
    }

    return pickedSquare;
}



//====================================================
// CAMERA
//====================================================

Camera3D& ChessRenderer3D::getCamera()
{
    return camera;
}